/*********************
File name: queue.c
Author: Ido Finkelstein
Reviewer: Rita Lempert
Date: 13/6/2020
**********************/

#include <stdlib.h> /* malloc, free, size_t */
#include <assert.h>

#include "slist.h"
#include "queue.h"

enum status
{
	SUCCESS = 0,
	FAILURE
};

struct queue
{
    slist_t *slist;
};

queue_t *QCreate(void)
{
	queue_t *queue = (queue_t*)malloc(sizeof(queue_t));
	
	if (NULL == queue)
	{
		return (NULL);
	}
	
	queue->slist = SListCreate();

	if (NULL == queue->slist)
	{
		free(queue);
		queue = NULL;

		return (NULL);		
	}

	return (queue);
}

void QDestroy(queue_t *queue)
{
	assert(queue);

	SListDestroy(queue->slist);
	free(queue);

	queue = NULL;
}

size_t QSize(const queue_t *queue)
{
	assert(queue);

	return (SListCount(queue->slist));
}

int QIsEmpty(const queue_t *queue)
{
	assert(queue);

	return (SListIsEmpty(queue->slist));
}

int QEnqueue(queue_t *queue, void *data)
{
	assert(queue);

	if (SListInsert(queue->slist, SListEnd(queue->slist), data) ==
	    SListEnd(queue->slist))
	{
		return (FAILURE);
	}

	return SUCCESS;
}

void QDequeue(queue_t *queue)
{
	assert(queue);

	SListRemove(queue->slist, SListBegin(queue->slist));
}

void *QPeek(const queue_t *queue)
{
	assert(queue);

	return (SListGetData(SListBegin(queue->slist)));
}

void QAppend(queue_t *dest, queue_t *src)
{
	assert(dest);
	assert(src);

	SListAppend(dest->slist, src->slist);
}
