/*******************************
File name: heapify.c
Author: Ido Finkelstein
Reviewer: Gal Shvinkelstein
Date: 13/8/2020
********************************/

#include "heapify.h"
#include <stdio.h>

void SwapBytes(char *byte1, char *byte2, size_t n_bytes);
static void *Max(void *data1, void *data2, heapify_cmp_func_t cmp, void *arg);

void HeapifyUp(void *base,
			   size_t nmemb,
 			   size_t index,
 			   size_t elem_size,     
               heapify_cmp_func_t cmp,
			   void *param)
{
	long parent = (((long)index - 1) / 2);
	
	if (0 >= index)
	{
	
		return;
	}
	else if (0 < cmp((char*)base + index * elem_size,  /* current node */
					 (char*)base + parent * elem_size, /* parent node  */
 					  param))
	{
		SwapBytes((char*)base + parent * elem_size, 
				  (char*)base + index * elem_size,
				   elem_size);

		HeapifyUp(base, nmemb, parent, elem_size, cmp, param);
	}
	
}

/*------------------------------------------------------------------------------------------*/

void HeapifyDown(void *base, 
				 size_t nmemb, 
				 size_t index, 
				 size_t elem_size,     
                 heapify_cmp_func_t cmp, 
				 void *param)
{
	size_t left = (index * 2 + 1) * elem_size;
	size_t right = (index * 2 + 2) * elem_size;
	void *node_to_swap = NULL;
	size_t new_index = 0;

	/* has no children */
	if (left / elem_size > nmemb - 1)
	{
		return;
	}
	/* has two children */
	else if (right / elem_size <= nmemb - 1)
	{
		node_to_swap = Max((char*)base + left, (char*)base + right, cmp, param);
		new_index = ((char*)node_to_swap - (char*)base) / elem_size;
	}
	/* has one child */
	else
	{
		node_to_swap = (char*)base + left;
		new_index = left;
	}
	
	/* bubbles up */
	if (0 < cmp(node_to_swap, (char*)base + index * elem_size, param))
	{
		SwapBytes(node_to_swap, (char*)base + index * elem_size, elem_size);
		HeapifyDown(base, nmemb, new_index, elem_size, cmp, param);
	}
}

/*------------------------------------------------------------------------------------------*/

/*--------------------------------------Utility functions-----------------------------------*/

static void *Max(void *data1, void *data2, heapify_cmp_func_t cmp, void *arg)
{
	if (0 < cmp(data1, data2, arg))
	{
		return (data1);
	}

	return (data2);
}
