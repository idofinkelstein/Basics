/***********************
File name: pqueue.c
Author: Ido Finkelstein
Reviewer: Inbal Elmalech
Date: 26/6/2020
************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h>

#include "sorted_list.h"
#include "pqueue.h"

struct pqueue
{
    sorted_list_t *sorted_list;
};

pqueue_t *PQCreate(pqueue_is_before_func_t is_before)
{
	pqueue_t *pq = (pqueue_t*)malloc(sizeof(pqueue_t));

	if (NULL == pq)
	{
		return NULL;
	}

	pq->sorted_list = SortedListCreate(is_before);

	if (NULL == pq->sorted_list)
	{
		free(pq);
		pq = NULL;

		return (NULL);
	}

	return (pq);
}

void PQDestroy(pqueue_t *pqueue)
{
	assert(pqueue);

	SortedListDestroy(pqueue->sorted_list);

	free(pqueue);

	pqueue = NULL; 
}

size_t PQSize(const pqueue_t *pqueue)
{
	assert(pqueue);

	return (SortedListSize(pqueue->sorted_list));
}

int PQIsEmpty(const pqueue_t *pqueue)
{
	assert(pqueue);

	return (SortedListIsEmpty(pqueue->sorted_list));
}

int PQEnpqueue(pqueue_t *pqueue, void *data)
{
	assert(pqueue);

	return (SortedListIterIsEqual(SortedListInsert(pqueue->sorted_list, data),
								  SortedListEnd(pqueue->sorted_list)));
}

void *PQDequeue(pqueue_t *pqueue)
{
	void *data = SortedListGetData(SortedListBegin(pqueue->sorted_list));

	assert(pqueue);

	SortedListRemove(SortedListBegin(pqueue->sorted_list));

	return (data);
}

void *PQPeek(const pqueue_t *pqueue)
{
	assert(pqueue);

	return (SortedListGetData(SortedListBegin(pqueue->sorted_list)));
}

void PQClear(pqueue_t *pqueue)
{
	assert(pqueue);

	while (!PQIsEmpty(pqueue))
	{
		PQDequeue(pqueue);
	}
}

void *PQErase(pqueue_t *pqueue, pqueue_is_match_func_t is_match, void *param)
{
	sorted_list_iter_t sorted_iter = SortedListBegin(pqueue->sorted_list);

	void *data = SortedListGetData(sorted_iter);

	assert(pqueue);

	/* As long as sorted_iter didn't reach end of pqueue, and there is no match
	   to the data within it, sorted_iter is incremented and data is saved */
	while (!SortedListIterIsEqual(sorted_iter,
		   						  SortedListEnd(pqueue->sorted_list)) &&
		   !is_match(SortedListGetData(sorted_iter),param))
	{
		sorted_iter = SortedListNext(sorted_iter);

		data = SortedListGetData(sorted_iter);
	}
	
	/* Returns NULL in case of sorted_iter has reached end of pqueue */
	if (SortedListIterIsEqual(sorted_iter,
		   					  SortedListEnd(pqueue->sorted_list)))
	{
		return (NULL);
	}

	/* If there is a match - sorted_iter is removed and the data is returned */
	SortedListRemove(sorted_iter);

	return (data);
}
