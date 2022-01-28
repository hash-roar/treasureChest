###

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

	void* callback(void *arg)
	{
	    for (int i = 0; i < 5; i++)
	    {
	        printf("子线程:i=%d\n", i);
	    }
	    printf("son thredL:%ld\n", pthread_self());
	    return NULL;
	}
	int main()
	
	{
	    pthread_t tid;
	    pthread_create(&tid, NULL, callback, NULL);
	    for (int i = 0; i < 5; i++)
	
	    {
	
	        printf("main thread i=%d\n", i);
	    }
	   
	    printf("main:%ld\n", pthread_self());
	     sleep(3);
	    return 0;
	}
	gcc hello.c  -lthread   -o app

### 线程创建

### 线程退出

### 线程回收
pthread_jion阻塞直到子线程退出
	为了使线程退出后可以传递参数,可以在主线程类申请空间,穿地址到子线程里
	
			void *callback(void *arg)
		{
		    for (int i = 0; i < 5; i++)
		    {
		        printf("子线程:i=%d\n", i);
		    }
		    printf("son thredL:%ld\n", pthread_self());
		    struct Test *t = (struct Test *)arg;
		    t->age = 10;
		    t->num = 12;
		    pthread_exit(t);
		    return NULL;
		}
		int main()
		
		{
		    pthread_t tid;
		    struct Test t;
		    pthread_create(&tid, NULL, callback, &t);
		    printf("main:%ld\n", pthread_self());
		    void *ptr;
		    pthread_join(tid, &ptr);
		    printf("num:%d, age:%d \n", t.num,t.age);
		    return 0;
		}
	
	###线程分离
	主线程不必阻塞等着回收子线程资源,子线程被内核回收
	
	### 线程取消
	
		pthread_cancel()
	
	### 线程id比较
	
		int pthread_equal()
		
	
	## 线程同步
	保护共享资源(锁)
	
	### 互斥锁
	只有一个线程能使用锁(加锁的才能解锁)
	
	int number;
	pthread_mutex_t mutex;
	void *callback(void *arg)
	{
	    printf("子线程:%ld\n", pthread_self());
	    for (int i = 0; i < 10; i++)
	    {
	        pthread_mutex_lock(&mutex);
	            printf("number%ld,,,:%d\n", pthread_self(), number++);
	        usleep(10);
	        pthread_mutex_unlock(&mutex);
	    }
	    pthread_exit(NULL);
	    return NULL;
	}
	int main()
	
	{
	    pthread_t tid1, tid2;
	    struct Test t;
	    pthread_mutex_init(&mutex,NULL);
	    pthread_create(&tid1, NULL, callback, &t);
	    pthread_create(&tid2, NULL, callback, &t);
	    printf("main:%ld\n", pthread_self());
	    pthread_mutex_destroy(&mutex);
	    pthread_exit(NULL);
	    return 0;
	}

### 死锁

	1.加锁后忘记解锁
	2.函数退出导致无法解锁
	3.重复加锁,导致一直阻塞
	4.多个共享资源加锁,互相阻塞

### 读写锁
锁定读和锁定写

pthread_rwlock_t 读写锁


### 条件变量
对生产者消费者模型使用
pthread_cond_t 保存了阻塞的线程id

五个消费者线程,五个生产者线程,用链表表示仓库

	static int num = 0;
	struct Node
	{
	    int value;
	    struct Node *next;
	};
	struct Node *head = NULL;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
	void *produce(void *arg)
	{
	    while (1)
	    {
	        /* code */
	        pthread_mutex_lock(&mutex);
	        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
	        newNode->value = rand() % 100;
	        newNode->next = head;
	        head = newNode;
	        printf("produce,,,id:%ld,,number:%d\n", pthread_self(), newNode->value);
	        pthread_mutex_unlock(&mutex);
	        pthread_cond_broadcast(&cond);
	        sleep(rand() % 3);
	    }
	    return NULL;
	}
	void *consume(void *arg)
	{
	    while (1)
	    {
	        pthread_mutex_lock(&mutex);
	        while (head ==NULL)
	        {
	            pthread_cond_wait(&cond,&mutex);
	        }
	        
	        struct Node *node = head;
	        printf("consumer,,,id:%ld,,number:%d\n", pthread_self(), node->value);
	        head = head->next;
	        free(node);
	        pthread_mutex_unlock(&mutex);
	        sleep(rand() % 3);
	    }
	    return NULL;
	}
	
	int main()
	
	{
	    pthread_mutex_init(&mutex, NULL);
	    pthread_cond_init(&cond, NULL);
	
	    pthread_t consumer[5], producer[5];
	    for (int i = 0; i < 5; i++)
	    {
	        pthread_create(&consumer[i], NULL, consume, NULL);
	    }
	    for (int i = 0; i < 5; i++)
	    {
	        pthread_create(&producer[i], NULL, produce, NULL);
	    }
	    for (int i = 0; i < 5; i++)
	    {
	        pthread_join(consumer[i],NULL);
	        pthread_join(producer[i],NULL);
	    }
	    
	    pthread_mutex_destroy(&mutex);
	    pthread_cond_destroy(&cond);
	    return 0;
	}

### 信号量

	