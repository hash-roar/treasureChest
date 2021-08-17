#pragma once
#include <queue>
#include <pthread.h>
//定义函数指针数据类型
using callback = void (*)(void *);
//定义任务队列元素.防止释放堆内存时释放不干净,用模板
template <class T>
struct Task
{
    Task()
    {
        func = nullptr;
        arg = nullptr;
    }
    Task(callback f, void *arg)
    {
        this->func = f;
        this->arg = (T *)arg;
    }
    callback func;
    T *arg;
};
typedef struct Task Task;
//定义任务队列,核心为stl的队列
template<class T>
class TaskQueue
{
private:
    /* data */
    //定义任务队列
    std::queue<Task<T>> taskQ;
    //互斥锁,任何访问临界区的操作都加锁,为了方便管理只用一把锁
    //用多把锁可以提示效率
    pthread_mutex_t mutex;

public:
    TaskQueue(/* args */);
    ~TaskQueue();
    //添加任务
    void addTask(Task<T> t);
    void addTask(callback f, void *arg);
    //获取任务
    Task<T> getTask();
    //获取任务数量
    inline size_t taskNUM()
    {
        pthread_mutex_lock(&mutex);
        return taskQ.size();
        pthread_mutex_unlock(&mutex);
    };
};
//为了释放堆内存不得不嵌套多重模板
//也可以定义释放指针的函数
template<class T>
class ThreadPool
{
private:
    /* data */
    TaskQueue<T> *taskQue;
    pthread_t managerID;//管理者线程,用于增加或则销毁线程
    pthread_t *threadIDs;//工作线程,任务队列有任务时取出任务并执行
    int miniNum;//最小线程数
    int maxNum;//最大线程数
    int busyNum;//忙线程数
    int liveNum;//活着的线程数
    int exitNum;//退出的线程数
    pthread_mutex_t mutexPool;//互斥锁
    pthread_cond_t notEmpty;//条件变量,用于阻塞工作线程

    bool shutdown;
    static void *worker(void *arg);//工作线程函数
    static void *manager(void *arg);//管理线程函数
    void threadExit();//线程退出
    static const int NUM = 2;//一次操作的线程数

public:
//对外接口
    ThreadPool(int min, int num);
    ~ThreadPool();
    void AddTask(Task<T> t);
    int getBusyNum();//获取忙线程数
    int getLiveNum();
};
