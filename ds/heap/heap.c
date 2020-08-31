/*******************************
File name: heap.c
Author: Ido Finkelstein
Reviewer: Gal Shvinkelstein
Date: 13/8/2020
********************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h>
#ifdef NDEBUG
 /* printf */
#endif
#include <stdio.h>
#include "heap.h"
#include "vector.h"
#include "heapify.h"

/* Utility function declaration */
static size_t FindIndex(heap_t *heap,
					    void *data,
						heap_is_match_func_t is_match,
						void *param);


struct heap
{
	heap_cmp_func_t cmp;
	void *param;
	vector_t *vector;
};

/*------------------------------------------------------------------------------------------*/

heap_t *HeapCreate(heap_cmp_func_t cmp, void *param)
{
	heap_t *heap = NULL;
	heap = (heap_t*)malloc(sizeof(heap_t));
	
	if (NULL == heap)
	{
		return (NULL);
	}

	heap->vector = VectorCreate(1);

	if (NULL == heap->vector)
	{
		free(heap);
		return (NULL);
	}
	
	heap->param = param;
	heap->cmp = cmp;

	return (heap);
}

/*------------------------------------------------------------------------------------------*/

void HeapDestroy(heap_t *heap)
{
	assert(heap);

	VectorDestroy(heap->vector);
	free(heap);

	heap = NULL;
}

/*------------------------------------------------------------------------------------------*/

void *HeapPeek(heap_t *heap)
{
	assert(heap);

	if (HeapIsEmpty(heap))
	{
		return (NULL);
	}

	return (VectorGetElement(heap->vector, 0));
}

/*------------------------------------------------------------------------------------------*/

size_t HeapSize(heap_t *heap)
{
	assert(heap);

	return (VectorSize(heap->vector));
}
int HeapIsEmpty(heap_t *heap)
{
	assert(heap);

	return (0 == HeapSize(heap));
}

int HeapPush(heap_t *heap, void *data)
{
	void **arr = NULL;
	int status = 0;

	assert(heap);
	
	status = VectorPushBack(heap->vector, data);
	
	if (!status) /* 0 is success */
	{
		/* realloc func could change the address of arr, so the assignment
		   comes after VectorPushBack */
		arr = VectorGetArray(heap->vector); 
		
		HeapifyUp(arr,
				  HeapSize(heap),
				  HeapSize(heap) - 1, 
				  sizeof(void*),
				  heap->cmp, heap->param);
	}
	
	return (status);	
}

/*------------------------------------------------------------------------------------------*/

void *HeapPop(heap_t *heap)
{
	void **arr = NULL;
	void *data = NULL;

	assert(heap);

	arr = VectorGetArray(heap->vector);
	data = HeapPeek(heap);

	arr[0]  = arr[HeapSize(heap) - 1];
	
	VectorPopBack(heap->vector);
	
	/* realloc func could change the address of arr, so the assignment
	   comes once more after VectorPushBack */
	arr = VectorGetArray(heap->vector);

	if (!HeapIsEmpty(heap))
	{
		HeapifyDown(arr,
				    HeapSize(heap),
				    0, 
				    sizeof(void*),
				    heap->cmp, heap->param);
	}

	return (data);
}

/*------------------------------------------------------------------------------------------*/

void *HeapRemove(heap_t *heap, void *data, heap_is_match_func_t is_match, void *param)
{
	size_t index = 0;
	size_t parent = 0;
	void *matched_data = NULL;
	void **arr = NULL;
	
	assert(heap);
	/* finds index of desired data and checks if it's valid and saves data */
	index = FindIndex(heap, data, is_match, param);

	if (index == HeapSize(heap))
	{
		return (NULL);
	}

	arr = VectorGetArray(heap->vector);
	matched_data = arr[index];
	/* 2. run-over with last element & remove last element */
	arr[index] = arr[HeapSize(heap) - 1];
	HeapPop(heap);
	parent = (index - 1) / 2;

	/* checks the direction of heapify */
	/* bubbles the data to its place */
	if (0 < heap->cmp(&arr[index], &arr[parent], param))
	{
		HeapifyUp(arr,
			      HeapSize(heap),
 			      index,
 			      sizeof(void*),     
                  heap->cmp,
			      param);
	}
	else
	{
		HeapifyDown(arr,
			    	HeapSize(heap),
 			    	index,
 			    	sizeof(void*),     
                	heap->cmp,
			    	param);
	}

	return (matched_data);
}

/*------------------------------------------------------------------------------------------*/

/*--------------------------------------Utility functions-----------------------------------*/

static size_t FindIndex(heap_t *heap,
					    void *data, 
						heap_is_match_func_t is_match, 
						void *param)
{
	void **arr = NULL;
	size_t i = 0;

	arr = VectorGetArray(heap->vector);

	for (i = 0; i < HeapSize(heap) && !is_match(arr[i], data, param); ++i)
	{
		;
	}
		
	return (i);
}

/*-------------------------------------------------------------------------------------------*/


/*---------------------------------------Debug functions-------------------------------------*/

#ifdef NDEBUG

void Print(heap_t *heap)
{
	size_t i = 0;
	void **arr = VectorGetArray(heap->vector);

	for (i = 0; i < HeapSize(heap); ++i)
	{
		printf("%d(%ld), ", *(int*)arr[i], i);
	}

	puts("");
}

int IsMaxHeap(heap_t *heap)
{
	size_t i = 0;
	void **arr = VectorGetArray(heap->vector);

	/* checks if son is greater than dad for all elements in heap */
	for (i = 0; i < HeapSize(heap) - 1 ; ++i)
	{
		if(*(int*)arr[HeapSize(heap) - i - 1] > *(int*)arr[((HeapSize(heap) - i - 1) - 1) / 2])
		{
			return 0;
		}		
	}

	return 1;
}

int IsMinHeap(heap_t *heap)
{
	size_t i = 0;
	void **arr = VectorGetArray(heap->vector);

	/* checks if son is smaller than dad for all elements in heap */
	for (i = 0; i < HeapSize(heap) - 1 ; ++i)
	{
		if(*(int*)arr[HeapSize(heap) - i - 1] < *(int*)arr[((HeapSize(heap) - i - 1) - 1) / 2])
		{
			return 0;
		}		
	}

	return 1;
}

#endif

