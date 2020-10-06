#define _DEFAULT_SOURCE
/******************************************************************************
* File name: ex5.c
* Developer: Matan Yankovich
* Reviewer:
*******************************************************************************/

#include <stdio.h>		/* puts 									*/
#include <semaphore.h>	/* sem_wait, sem_post, sem_init 			*/
#include <pthread.h>	/* pthread_create, pthread_join, mutex_init */
#include <stdlib.h>		/* malloc, free, rand 						*/
#include <unistd.h>

#include "queue.h"

static volatile int ready_consumers = 0;
static volatile int num_of_consumers = 4;
static volatile int message_counter = 0;

typedef struct thread_info
{
	pthread_mutex_t   mutex;
	pthread_cond_t  con_var;
	sem_t 			    sem;
	queue_t 		 *queue;
}thread_info_t;
/****************************   DECLARATIONS   *******************************/
thread_info_t *PCCreateThreadInfo(void);
void *Producer(void *data);
void *Consumer(void *data);
/********************************  MAIN  *************************************/

int main()
{

	pthread_attr_t attr;
	pthread_t thread[5];
	thread_info_t *thread_info = NULL;

	thread_info = PCCreateThreadInfo();

	pthread_attr_init (&attr);
	pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
/*
	pthread_create (thread + 0, &attr, &Producer, thread_info);
	pthread_create (thread + 1, &attr, &Consumer, thread_info);
	pthread_create (thread + 2, &attr, &Consumer, thread_info);
	pthread_create (thread + 3, &attr, &Consumer, thread_info);
	pthread_create (thread + 4, &attr, &Consumer, thread_info);
	pthread_attr_destroy (&attr);
*/
	pthread_create (thread + 1, NULL, &Consumer, thread_info);
	pthread_create (thread + 2, NULL, &Consumer, thread_info);
	pthread_create (thread + 3, NULL, &Consumer, thread_info);
	pthread_create (thread + 4, NULL, &Consumer, thread_info);
	pthread_create (thread + 0, NULL, &Producer, thread_info);



	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);
	pthread_join(thread[3], NULL);
	pthread_join(thread[4], NULL);


	QDestroy(thread_info->queue);
	sem_destroy(&thread_info->sem);
	pthread_mutex_destroy(&thread_info->mutex);
	pthread_cond_destroy(&thread_info->con_var);

	

	return (0);
}
/*---------------------------------------------------------------------------*/
void *Producer(void *data)
{
	thread_info_t *thread_info = (thread_info_t *)data;

	while (1)
	{
		
		/* make a mesagge and store it  */
		if (0 != QEnqueue(thread_info->queue, "massage"))
		{
			puts("Error: QEnqueue failed!");
		}
		/*printf("Producer: produced message %d\n", message_counter);*/
		sem_wait(&thread_info->sem);	
		pthread_cond_broadcast(&thread_info->con_var);
		

		/* block producer if the last consumer is not ready */
		pthread_mutex_lock(&thread_info->mutex);
		printf("Producer: broadcast message %d\n", message_counter++);
		pthread_mutex_unlock(&thread_info->mutex); /* unlock producers */
		QDequeue(thread_info->queue);
	}

	return (NULL);
}
/*
		flag = 1;
		read = 0;

		flag = 0;
		sleep(1);
*/
/*---------------------------------------------------------------------------*/
void *Consumer(void *data)
{
	thread_info_t *thread_info = (thread_info_t *)data;

	while (1)
	{
		pthread_mutex_lock(&thread_info->mutex); /* lock consumers */
		

		printf("Consumer '%ld' is ready for broadcast %d.\n",
			   pthread_self(), message_counter);

		
		
		if (ready_consumers != num_of_consumers)
		{
			++ready_consumers;
			pthread_cond_wait(&thread_info->con_var, &thread_info->mutex);
		}
		

		if (ready_consumers == num_of_consumers)
		{
			ready_consumers = 0;
			sem_post(&thread_info->sem);
		}
		

		QPeek(thread_info->queue);
/*		printf("Consumer '%ld' consumed message %d.\n",
			   pthread_self(), message_counter);*/
		pthread_mutex_unlock(&thread_info->mutex); /* unlock consumers */

	}

	return (NULL);
}
/*		while (ready_consumers < num_of_consumers)
		{
		}

		while (!is_all_consumers_ready)
		{
		}
*/
/*---------------------------------------------------------------------------*/
thread_info_t *PCCreateThreadInfo(void)
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
