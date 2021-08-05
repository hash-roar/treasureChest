#pragma once

typedef  struct thread_pool thread_pool;

//创建线程池


thread_pool* thread_pool_create(int min, int max, int queuesize);


//销毁线程池


//线程池添加任务
void thread_pool_add_ev(thread_pool* pool, void (*func)(void*), void* arg);

void* work(void* arg);
void* manage(void* arg);
void threadExit(thread_pool * pool);
//获取工作线程个数
int thread_pool_busyNum(thread_pool* pool)
{
	pthread_mutex_lock(&pool->mutextBusy);
	int busyNum = pool->busyNum;
	pthread_mutex_unlock(&pool->mutextBusy);
	return busyNum;
}


//获取活着线程个数

int thread_pool_aliveNum(thread_pool* pool)
{
	pthread_mutex_lock(&pool->mutexPool);
	int liveNum = pool->liveNum;
	pthread_mutex_unlock(&pool->mutexPool);
	return liveNum;
}