#include "TaskQueue.h"
#include <iostream>
#include <string.h>
#include <string>
#include <unistd.h>
using namespace std;
//任务队列构造函数,只用初始化锁
template<class T>
TaskQueue<T>::TaskQueue(/* args */)
{
    pthread_mutex_init(&mutex, NULL);
}
template<class T>
TaskQueue<T>::~TaskQueue()
{
    pthread_mutex_destroy(&mutex);
}
template<class T>
void TaskQueue<T>::addTask(Task t)
{
    pthread_mutex_lock(&mutex);
    taskQ.push(t);
    pthread_mutex_unlock(&mutex);
}
template<class T>
void TaskQueue<T>::addTask(callback f, void *arg)
{
    pthread_mutex_lock(&mutex);
    taskQ.push(Task(f, arg));
    pthread_mutex_unlock(&mutex);
}
template<class T>
Task TaskQueue<T>::getTask()
{
    Task temp;
    pthread_mutex_lock(&mutex);
    if (taskQ.size() > 0)
    {
        temp = taskQ.front();
        taskQ.pop();
    }
    pthread_mutex_unlock(&mutex);
    return temp;
}
//线程池构造函数
template<class T>
ThreadPool<T>::ThreadPool(int min, int max)
{

    do
    {
        taskQue = new TaskQueue<T>;
        //初始化任务队列及线程id组
        if (taskQue == nullptr)
        {
            cout << "申请taskque失败" << endl;
            break;
        }
        
        threadIDs = new pthread_t[max];
        if (threadIDs == nullptr)
        {
            cout << "申请threadID内存失败" << endl;
            break;
        }
        bzero(threadIDs, sizeof(threadIDs));
        //初始化线程池变量
        miniNum = min;
        maxNum = max;
        busyNum = 0;
        liveNum = min;
        exitNum = 0;
        //初始化锁
        if (pthread_mutex_init(&mutexPool, NULL) && pthread_cond_init(&notEmpty, NULL))
        {
            cout << "mutex初始化失败" << endl;
            break;
        }
        shutdown = false;
        //按照最低标准创建线程
        pthread_create(&managerID, NULL, manager, NULL);
        for (int i = 0; i < min; i++)
        {
            pthread_create(&threadIDs[i], NULL, worker, this);
        }
        return;
    } while (0);
    //初始化失败,释放资源
    if (threadIDs)
        delete[] threadIDs;
    if (taskQue)
        delete taskQue;
}

template<class T>
ThreadPool<T>::~ThreadPool()
{
    //关闭线程池
    shutdown = true;
    //等待管理线程退出
    pthread_join(managerID, NULL);
    //解除所有阻塞
    for (int i = 0; i < liveNum; i++)
    {
        pthread_cond_signal(&notEmpty);
    }
    //释放资源
    if (taskQue)
    {
        delete taskQue;
    }
    if (threadIDs)
    {
        delete threadIDs;
    }
    pthread_mutex_destroy(&mutexPool);
    pthread_cond_destroy(&notEmpty);
}
template<class T>
void *ThreadPool<T>::worker(void *arg)
{
    //将传递进来的指针转化为
    ThreadPool *pool = static_cast<ThreadPool *>(arg);
    while (true)
    {

        pthread_mutex_lock(&pool->mutexPool);
        //任务队列里没有任务时,阻塞线程
        while (pool->taskQue->taskNUM() == 0 && !pool->shutdown)
        {
            //拿到锁的线程在此阻塞,并且在函数内部将锁释放,因此更多的线程将在此阻塞
            //线程解除阻塞后判断是否是线程退出,否则进入下一个循环获取队列任务
            pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);

            if (pool->exitNum > 0)
            {
                pool->exitNum--;
                if (pool->liveNum > pool->miniNum)
                {
                    pool->liveNum--;
                    pthread_mutex_unlock(&pool->mutexPool);
                    pool->threadExit();
                }
            }
        }
        //线程池关闭时,退出线程
        if (pool->shutdown)
        {
            pthread_mutex_unlock(&pool->mutexPool);
            pool->threadExit();
        }
        //获取任务并执行
        Task task = pool->taskQue->getTask();
        pool->busyNum++;
        pthread_mutex_unlock(&pool->mutexPool);
        task.func(task.arg);
        //执行完毕释放资源
        delete task.arg;
        task.arg = nullptr;
        cout << "线程" << pthread_self() << "停止" << endl;
        pthread_mutex_lock(&pool->mutexPool);
        pool->busyNum--;//忙线程减少
        pthread_mutex_unlock(&pool->mutexPool);
    }
    return nullptr;
}
template<class T>
void ThreadPool<T>::threadExit()
{
    //可以在此处定义日志写入
    pthread_t tid = pthread_self();
    for (int i = 0; i < maxNum; i++)
    {
        if (threadIDs[i] == tid)
        {
            threadIDs[i] = 0;
            cout << "线程" << tid << "退出" << endl;
            break;
        }
    }
    pthread_exit(NULL);
}
template<class T>
void *ThreadPool<T>::manager(void *arg)
{
    ThreadPool *pool = static_cast<ThreadPool *>(arg);
    //线程未关闭时
    while (!pool->shutdown)
    {
        //每3秒轮询一次,防止占用太多cpu资源
        sleep(3);
        //锁内获取线程池状态,忽略在几个时钟周期内发生的状态变化
        pthread_mutex_lock(&pool->mutexPool);
        int queSize = pool->taskQue->taskNUM();
        int liveNum = pool->liveNum;
        int busyNum = pool->busyNum;
        pthread_mutex_unlock(&pool->mutexPool);
        // 任务队列任务较多,可以创建更多线程来服务
        if (queSize > liveNum && liveNum < pool->maxNum)
        {
            pthread_mutex_lock(&pool->mutexPool);
            //计数,进行批量操作,threadIDs[i] == 0表示线程未激活
            int counter = 0;
            for (int i = 0; i < pool->maxNum && counter < NUM && pool->liveNum < pool->maxNum; i++)
            {
                if (pool->threadIDs[i] == 0)
                {
                    pthread_create(&pool->threadIDs[i], NULL, worker, pool);
                    counter++;
                    pool->liveNum++;
                }
            }
            pthread_mutex_unlock(&pool->mutexPool);
        }
        //线程较多,释放线程
        if (busyNum < liveNum && liveNum > pool->miniNum)
        {
            pthread_mutex_lock(&pool->mutexPool);
            pool->exitNum = NUM;
            pthread_mutex_unlock(&pool->mutexPool);
            for (int i = 0; i < NUM; i++)
            {
                pthread_cond_signal(&pool->notEmpty);
            }
        }
    }
    return nullptr;
}
template<class T>
void ThreadPool<T>::AddTask(Task t)
{
    if (shutdown)
    {
        return;
    }
    taskQue->addTask(t);
    pthread_cond_signal(&notEmpty);
}
template<class T>
int ThreadPool<T>::getBusyNum()
{
    pthread_mutex_lock(&mutexPool);
    int busy_num = busyNum;
    pthread_mutex_unlock(&mutexPool);
    return busy_num;
}
template<class T>
int ThreadPool<T>::getLiveNum()
{
    pthread_mutex_lock(&mutexPool);
    int alive_num = liveNum;
    pthread_mutex_unlock(&mutexPool);
    return alive_num;
}
