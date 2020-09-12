#define _DEFAULT_SOURCE
/******************************************************************************
* File name: ex3.c
* Developer: Ido Finkelstein
* Reviewer:
*******************************************************************************/

#include <stdio.h>		/* puts 									*/
#include <semaphore.h>	/* sem_wait, sem_post, sem_init 			*/
#include <pthread.h>	/* pthread_create, pthread_join, mutex_init */
#include <stdlib.h>		/* malloc, free 							*/
#include <unistd.h>

#include "slist.h"


typedef struct thread_info
{
	slist_t* slist;
	pthread_mutex_t mutex;
	sem_t sem;
}thread_info_t;

/*----------------------------- Function declarations ------------------------*/
thread_info_t *PCCreateThreadInfo(void);
void *Producer(void *data);
void *Consumer(void *data);


int main(void)
{
	thread_info_t *thread_info = NULL;
	pthread_t *thr_arr = NULL;
	int num_of_prod = 2;
	int num_of_cons = 2;
	int num_of_threads = num_of_prod + num_of_cons;
	int i = 0;
	int status = 0;

	thr_arr = (pthread_t *)malloc(sizeof(pthread_t) * num_of_threads);
    if(NULL == thr_arr)
    {
        return (1);
    }

	thread_info = PCCreateThreadInfo();

	for (i = 0;  i < num_of_prod && !status; ++i)
	{
		status = pthread_create(thr_arr + i, NULL, Producer, thread_info);
	}

	for (i = 0;  i < num_of_cons && !status; ++i)
	{
		status = pthread_create(thr_arr + num_of_prod + i,
							    NULL,
							    Consumer,
							    thread_info);
	}

	if (0 != status)
	{
		exit(EXIT_FAILURE);
	}

	for (i = 0;  i < num_of_threads; ++i)
	{
		pthread_join(*(thr_arr + i), NULL);
	}

	free(thread_info);
	free(thr_arr);
    return (0);
}
/*---------------------------------------------------------------------------*/
thread_info_t *PCCreateThreadInfo(void)
{
	thread_info_t *thread_info = NULL;
	slist_t *slist = NULL;

    thread_info = (thread_info_t*)malloc(sizeof(thread_info_t));
    if(NULL == thread_info)
    {
        return (NULL);
    }

    slist = SListCreate();
    if(NULL == slist)
    {
		free(thread_info);
        return (NULL);
    }

	if (0 != pthread_mutex_init(&thread_info->mutex, NULL))
	{
		free(thread_info);
		SListDestroy(slist);
        return (NULL);
	}

	if (0 != sem_init(&thread_info->sem, 0, 0))
	{
		free(thread_info);
		SListDestroy(slist);
        return (NULL);
	}

	thread_info->slist = slist;

	return (thread_info);
}
/*---------------------------------------------------------------------------*/
void *Producer(void *data)
{
	thread_info_t *thread_info = (thread_info_t *)data;
	slist_t *slist = thread_info->slist;	

	while (1)
	{
		pthread_mutex_lock(&thread_info->mutex); /* lock other producers */
		if (SListIterIsEqual(SListEnd(slist),
							 SListInsert(slist,
										 SListEnd(slist),
										 "item")))
		{
			exit(EXIT_FAILURE);
		}
		puts("Produced");
		sleep(1);
		sem_post(&thread_info->sem);
		pthread_mutex_unlock(&thread_info->mutex); /* unlock other producers */
	}

	return (NULL);
}
/*---------------------------------------------------------------------------*/
void *Consumer(void *data)
{
	thread_info_t *thread_info = (thread_info_t *)data;
	slist_t *slist = thread_info->slist;
	
	while (1)
	{
		sem_wait(&thread_info->sem);
		SListRemove(slist, SListBegin(slist));
		puts("Consumed");
	}

	return (NULL);
}

