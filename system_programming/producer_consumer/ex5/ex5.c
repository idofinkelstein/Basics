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

typedef struct thread_info
{
	pthread_mutex_t prod_mutex;
	pthread_mutex_t cons_mutex;
	sem_t sem_full;
	sem_t sem_empty;
	fsq_t *fsq;
}thread_info_t;
/****************************   DECLARATIONS   *******************************/
thread_info_t *PCCreateThreadInfo(size_t fsq_capacity);
void *Producer(void *data);
void *Consumer(void *data);
/********************************  MAIN  *************************************/
int main(void)
{
	thread_info_t *thread_info = NULL;
	pthread_t *thr_arr = NULL;
	size_t fsq_capacity = 10;
	int num_of_prod = 2;
	int num_of_cons = 2;
	int num_of_threads = num_of_prod + num_of_cons;
	int i = 0;

	thr_arr = (pthread_t *)malloc(sizeof(pthread_t) * num_of_threads);
    if(NULL == thr_arr)
    {
        return (1);
    }

	thread_info = PCCreateThreadInfo(fsq_capacity);

	for (i = 0;  i < num_of_prod; ++i)
	{
		pthread_create(thr_arr + i, NULL, Producer, thread_info);
	}

	for (i = 0;  i < num_of_cons; ++i)
	{
		pthread_create(thr_arr + num_of_prod + i, NULL, Consumer, thread_info);
	}

	for (i = 0;  i < num_of_threads; ++i)
	{
		pthread_join(*(thr_arr + i), NULL);
	}

	free(thr_arr);
	FSQDestroy(thread_info->fsq);
	pthread_mutex_destroy(&thread_info->prod_mutex);
	pthread_mutex_destroy(&thread_info->cons_mutex);
	sem_destroy(&thread_info->sem_empty);
	sem_destroy(&thread_info->sem_full);
	free(thread_info);

    return (0);
}
/*---------------------------------------------------------------------------*/
thread_info_t *PCCreateThreadInfo(size_t fsq_capacity)
{
	thread_info_t *thread_info = NULL;
	fsq_t *fsq = NULL;

    thread_info = (thread_info_t*)malloc(sizeof(thread_info_t));
    if(NULL == thread_info)
    {
        return (NULL);
    }

    fsq = FSQCreate(fsq_capacity);
    if(NULL == fsq)
    {
		free(thread_info);
        return (NULL);
    }
	thread_info->fsq = fsq;

	if (0 != pthread_mutex_init(&thread_info->prod_mutex, NULL))
	{
		free(thread_info);
		FSQDestroy(fsq);
        return (NULL);
	}

	if (0 != pthread_mutex_init(&thread_info->cons_mutex, NULL))
	{
		free(thread_info);
		FSQDestroy(fsq);
        return (NULL);
	}

	if (0 != sem_init(&thread_info->sem_full, 0, 0))
	{
		free(thread_info);
		FSQDestroy(fsq);
        return (NULL);
	}

	if (0 != sem_init(&thread_info->sem_empty, 0, fsq_capacity))
	{
		free(thread_info);
		FSQDestroy(fsq);
        return (NULL);
	}

	return (thread_info);
}
/*---------------------------------------------------------------------------*/
void *Producer(void *data)
{
	thread_info_t *thread_info = (thread_info_t *)data;
	fsq_t *fsq = thread_info->fsq;

	while (1)
	{
		sem_wait(&thread_info->sem_empty);		

		pthread_mutex_lock(&thread_info->prod_mutex); /* lock producers */

		if (0 != FSQWrite(fsq, rand()))
		{
			puts("The Queue is full");
		}
		puts("Produced");
		sem_post(&thread_info->sem_full);
		pthread_mutex_unlock(&thread_info->prod_mutex); /* unlock producers */
		sleep(1);
	}

	return (NULL);
}
/*---------------------------------------------------------------------------*/
void *Consumer(void *data)
{
	thread_info_t *thread_info = (thread_info_t *)data;
	fsq_t *fsq = thread_info->fsq;

	while (1)
	{
		sem_wait(&thread_info->sem_full);
		pthread_mutex_lock(&thread_info->cons_mutex); /* lock consumers */

		FSQRead(fsq);
		puts("Consumed");
		sem_post(&thread_info->sem_empty);

		pthread_mutex_unlock(&thread_info->cons_mutex); /* lock consumers */
	}

	return (NULL);
}
/*---------------------------------------------------------------------------*/
