#define _DEFAULT_SOURCE
/******************************************************************************
* File name: ex5.c
* Developer: Ido Finkelstein
* Reviewer:
*******************************************************************************/

#include <stdio.h>		/* puts 									*/
#include <semaphore.h>	/* sem_wait, sem_post, sem_init 			*/
#include <pthread.h>	/* pthread_create, pthread_join, mutex_init */
#include <stdlib.h>		/* malloc, free, rand 						*/
#include <unistd.h>

#include "fsq.h"

int flag = 0;

typedef struct thread_info
{
	pthread_mutex_t   mutex;
	pthread_cond_t  con_var;
	sem_t 			    sem;
	queue_t 		 *queue;
}thread_info_t;
/****************************   DECLARATIONS   *******************************/
thread_info_t *PCCreateThreadInfo(size_t fsq_capacity);
void *Producer(void *data);
void *Consumer(void *data);
/********************************  MAIN  *************************************/

int main()
{
	pthread_attr_t attr;
	pthread_t thread[5];
	thread_info_t *thread_info = NULL;

	thread_info = PCCreateThreadInfo(fsq_capacity);

	pthread_attr_init (&attr);
	pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);

	pthread_create (&thread, &attr, &Producer, thread_info);
	pthread_create (&thread, &attr, &Consumer, thread_info);
	pthread_create (&thread, &attr, &Consumer, thread_info);
	pthread_create (&thread, &attr, &Consumer, thread_info);
	pthread_create (&thread, &attr, &Consumer, thread_info);
	pthread_attr_destroy (&attr);

	return 0;
}
void *Producer(void *data)
{
	thread_info_t *thread_info = (thread_info_t *)data;
	queue_t *queue = thread_info->queue;

	while (1)
	{
		sem_wait(&thread_info->sem);		
		pthread_mutex_lock(&thread_info->mutex); /* lock producers */

		QEnqueue(queue, "massage");
		flag = 1;
		read = 0;
		pthread_cond_broadcast(con_var);
		
		pthread_mutex_unlock(&thread_info->mutex); /* unlock producers */

		flag = 0;
		sleep(1);
	}

	return (NULL);
}
/*---------------------------------------------------------------------------*/
void *Consumer(void *data)
{
	thread_info_t *thread_info = (thread_info_t *)data;
	queue_t *queue = thread_info->queue;

	while (1)
	{
		pthread_mutex_lock(&thread_info->mutex); /* lock consumers */

		while (!flag)
		{
			pthread_cond_wait(&con_var, &mutex);
		}

		++read;
		
		QPeeq(thread_info->queue);
		
		if (read == 4)
		{
			sem_post(&thread_info->sem);
		}

		pthread_mutex_unlock(&thread_info->mutex); /* lock consumers */
	}

	return (NULL);
}
/*---------------------------------------------------------------------------*/
thread_info_t *PCCreateThreadInfo(size_t fsq_capacity)
{
	thread_info_t *thread_info = NULL;
	queue_t *queue= NULL;

    thread_info = (thread_info_t*)malloc(sizeof(thread_info_t));
    if(NULL == thread_info)
    {
        return (NULL);
    }

    queue = QCreate();
    if(NULL == queue)
    {
		free(thread_info);
        return (NULL);
    }
	thread_info->queue = queue;

	if (0 != pthread_mutex_init(&thread_info->mutex, NULL))
	{
		free(thread_info);
		QDestroy(queue);
        return (NULL);
	}

	
	if (0 != sem_init(&thread_info->sem, 0, 1))
	{
		free(thread_info);
		QDestroy(queue);
        return (NULL);
	}

	if (0 != pthread_cond_init(&thread_info->con_var, NULL))
	{
		free(thread_info);
		QDestroy(queue);
        return (NULL);
	}

	return (thread_info);
}
/*---------------------------------------------------------------------------*/
