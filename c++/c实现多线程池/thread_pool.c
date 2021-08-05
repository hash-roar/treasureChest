#include "thread_pool.h"
#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>
typedef struct Task
{
	void (*function)(void* arg);
	void* arg;
} Task;
const NUMBER = 2;
struct thread_pool
{
	Task* taskQ;
	int queueCapacity;
	int queuesize;
	int queueFront;
	int queueRear;

	pthread_t manageID;
	pthread_t* threadIDs;
	int minNum;
	int maxNum;
	int busyNum;//忙线程
	int liveNum;//存活线程
	int exitNum;//销毁线程数
	pthread_mutex_t mutexPool;
	pthread_mutex_t mutextBusy;
	pthread_cond_t notFull;
	pthread_cond_t notEmpty;
	int shutdown;
};
int thread_pool_destory(thread_pool* pool)
{
	if (pool == NULL) {
		return -1;
	}
	pool->shutdown = 1;
	pthread_join(pool->manageID, NULL);
	for (int i = 0; i < pool->liveNum; i++) {
		pthread_cond_signal(&pool->notEmpty);
	}
	if (pool && pool->threadIDs) free(pool->threadIDs);
	if (pool && pool->taskQ) free(pool->taskQ);
	if (pool) free(pool);
	pthread_mutex_destroy(&pool->mutexPool);
	pthread_mutex_destroy(&pool->mutextBusy);
	pthread_cond_destroy(&pool->notEmpty);
	pthread_cond_destroy(&pool->notFull);

	return 0;
}
thread_pool* thread_pool_create(int min,int max, int queuesize){
	thread_pool* pool = (thread_pool*)malloc(sizeof(thread_pool));
	do
	{
		
		if (pool == NULL)
		{
			printf("malloc fail!");
			break;
		}
		pool->threadIDs = (pthread_t*)malloc(sizeof(pthread_t) * max);
		if (pool->threadIDs == NULL)
		{
			printf("malloc fail");
			break;
		}

		memset(pool->threadIDs, 0, sizeof(pthread_t) * max);
		pool->minNum = min;
		pool->maxNum = max;
		pool->busyNum = 0;
		pool->liveNum = min;
		pool->exitNum = 0;
		if (pthread_mutex_init(&pool->mutexPool, NULL) != 0 || pthread_mutex_init(&pool->mutextBusy, NULL) != 0 ||
			pthread_cond_init(&pool->notEmpty, NULL) != 0 ||
			pthread_cond_init(&pool->notFull, NULL) != 0) {
			printf("init fial\n");
		}
		//task init
		pool->taskQ = (Task *)malloc(sizeof(Task) * queuesize);
		pool->queueCapacity = queuesize;
		pool->queuesize = 0;
		pool->queueFront = 0;
		pool->queueRear = 0;
		pool->shutdown = 0;
		//创建线程
		pthread_create(&pool->manageID, NULL, manage, NULL);
		for (int i = 0; i < min; i++)
		{
			pthread_create(&pool->threadIDs[i], NULL, work, NULL);
		}

		return pool;
	} while (0);
	//资源释放
	if (pool&&pool->threadIDs) free(pool->threadIDs);
	if (pool&&pool->taskQ) free(pool->taskQ);
	if (pool) free(pool);
		return NULL;
}
void* work(void* arg)
{
	thread_pool* pool = (thread_pool*)arg;
	while (1)
	{
		pthread_mutex_lock(&pool->mutexPool);
		while (pool->queuesize == 0 && !pool->shutdown)
		{
			pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);
			if (pool->exitNum > 0)
			{
				pool->exitNum--;
				if (pool->liveNum > pool->minNum) {
					pool->liveNum--;
					pthread_mutex_unlock(&pool->mutexPool);
					threadExit(pool);
				}
				
			}
		}
		//is close
		if (pool->shutdown) {
			pthread_mutex_unlock(&pool->mutexPool);
			threadExit(pool);
		}
		//begin work
		Task task;
		task.function = pool->taskQ[pool->queueFront].function;
		task.arg = pool->taskQ[pool->queueFront].arg;
		//移动queueFront,循环队列
		pool->queueFront = (pool->queueFront + 1) % pool->queueCapacity;
		pool->queuesize--;
		pthread_mutex_lock(&pool->mutextBusy);
		pool->busyNum++;
		pthread_mutex_unlock(&pool->mutextBusy);
		task.function(task.arg);
		free(task.arg);
		task.arg = NULL;
		pthread_mutex_unlock(&pool->mutexPool);
		pool->busyNum--;
		pthread_mutex_unlock(&pool->mutextBusy);
		task.function(task.arg);
	}
}
void threadExit(thread_pool* pool)
{
	pthread_t tid = pthread_self();
	for (int i = 0; i < pool->maxNum; ++i)
	{
		if (pool->threadIDs[i] == tid) {
			pool->threadIDs[i] = 0;
			break;
		}
	}
	pthread_exit(NULL);
}
void* manage(void* arg) {
	thread_pool* pool = (thread_pool*)arg;
	while (!pool->shutdown)
	{
		sleep(3);
		//取出线程池任务数量和当前进程数量
		pthread_mutex_lock(&pool->mutexPool);
		int queueSize = pool->queuesize;
		int liveNum = pool->liveNum;
		pthread_mutex_unlock(&pool->mutexPool);
		pthread_mutex_lock(&pool->mutextBusy);
		int busyNum = pool->busyNum;
		pthread_mutex_unlock(&pool->mutextBusy);

		if (queueSize > liveNum && liveNum < pool->maxNum)
		{
			pthread_mutex_lock(&pool->mutexPool);
			int counter = 0;
			for (int i = 0; i < pool->maxNum &&counter <NUMBER&& pool->liveNum<pool->maxNum; i++) {
				if (pool->threadIDs[i] == 0) {
					pthread_create(&pool->threadIDs[i], NULL, work, NULL);
					counter++;
					pool->liveNum++;
			}
			}
			pthread_mutex_unlock(&pool->mutexPool);
		}
		//
		if (busyNum * 2 < liveNum && liveNum < pool->maxNum) {
			pthread_mutex_lock(&pool->mutexPool);
			pool->exitNum = NUMBER;
			pthread_mutex_unlock(&pool->mutexPool);

			for (int i = 0; i < NUMBER; i++)
			{
				pthread_cond_signal(&pool->notEmpty);
			}

		}
	}
}
void thread_pool_add_ev(thread_pool* pool, void (*func)(void*), void* arg)
{
	pthread_mutex_lock(&pool->mutexPool);
	while (pool->queuesize == pool->queueCapacity && !pool->shutdown)
	{
		pthread_cond_wait(&pool->notFull, &pool->mutexPool);
	}
	if (pool->shutdown) {
		pthread_mutex_unlock(&pool->mutexPool);
		return;
	}
	pool->taskQ[pool->queueRear].function = func;
	pool->taskQ[pool->queueRear].arg = arg;
	pool->queueRear = (pool->queueRear + 1) % pool->queueCapacity;
	pool->queuesize++;
	pthread_cond_signal(&pool->notEmpty);
	pthread_mutex_unlock(&pool->mutexPool);
}