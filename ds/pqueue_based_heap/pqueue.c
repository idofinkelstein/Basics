/***********************
File name: pqueue.c
Author: Ido Finkelstein
Reviewer: Inbal Elmalech
Date: 26/6/2020
************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h>

#include "heap.h"
#include "pqueue.h"

struct pqueue
{
	void *param;
    heap_t *heap;
	pqueue_cmp_func_t compare;
};

pqueue_t *PQCreate(pqueue_cmp_func_t cmpare, void *param)
{
	pqueue_t *pq = (pqueue_t*)malloc(sizeof(pqueue_t));

	if (NULL == pq)
	{
		return NULL;
	}

	pq->heap = HeapCreate(cmpare, pq);

	if (NULL == pq->heap)
	{
		free(pq);
		pq = NULL;

		return (NULL);
	}

	pq->param = param;
	pq->compare = cmpare;

	return (pq);
}

void PQDestroy(pqueue_t *pqueue)
{
	assert(pqueue);

	HeapDestroy(pqueue->heap);

	free(pqueue);

	pqueue = NULL; 
}

size_t PQSize(const pqueue_t *pqueue)
{
	assert(pqueue);

	return (HeapSize(pqueue->heap));
}

int PQIsEmpty(const pqueue_t *pqueue)
{
	assert(pqueue);

	return (HeapIsEmpty(pqueue->heap));
}

int PQEnqueue(pqueue_t *pqueue, void *data)
{
	assert(pqueue);

	return (HeapPush(pqueue->heap, data));
}

void *PQDequeue(pqueue_t *pqueue)
{
	assert(pqueue);

	return (HeapPop(pqueue->heap));
}

void *PQPeek(const pqueue_t *pqueue)
{
	assert(pqueue);

	return (HeapPeek(pqueue->heap));
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
	assert(pqueue);

	return (HeapRemove(pqueue->heap, param, is_match, param));
}



