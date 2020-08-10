/*****************************
File Name: merge_sort.c
Author: Ido Finkelstein
reviewer: Janna T
Date: 10/8/2020
******************************/

#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */

#ifdef NDEBUG
#include <stdio.h> /* printf */
#endif

#include "sort.h"

#define MALLOC_FAILED -1

void Merge(void *a,
		   void *l,
		   void *r,
		   size_t size_l,
		   size_t size_r,
 		   sort_cmp_func_t cmp,
 		   size_t size);

int MergeSort(void *arr_to_sort, 
			 size_t num_elements, 
			 size_t size,
             sort_cmp_func_t cmp,
             void *arg)
{
	size_t middle = num_elements / 2;
	size_t size_l = num_elements / 2;
	size_t size_r = num_elements - size_l;
	void *l = NULL;
	void *r = NULL;
	char *start_a = (char*)arr_to_sort;

	if (2 > num_elements)
	{
		return 0;
	}

	l = malloc(size_l * size);
	
	if (NULL == l)
	{
		return (MALLOC_FAILED);
	}

	r = malloc(size_r * size);

	if (NULL == r)
	{
		free(l);
		return (MALLOC_FAILED);
	}
	
	/* copies left half to l and copies right half to r */
	memcpy(l, start_a, size * size_l);			
	memcpy(r, start_a + (middle * size), size_r * size);
	
	/* splits each one of them recursively */
	MergeSort(l, size_l, size, cmp, arg);	
	MergeSort(r, size_r, size, cmp, arg);
	
	/* combines them after sorting to the input array */
	Merge(start_a, l, r, size_l, size_r, cmp, size);

	free(l);
	free(r);
	
	return 0;
}

void Merge(void *a,
		   void *l,
		   void *r,
		   size_t size_l,
		   size_t size_r,
 		   sort_cmp_func_t cmp,
 		   size_t size)
{
	size_t i_l = 0;
	size_t i_r = 0;
	size_t i_a = 0;
	char *start_l = (char*)l;
	char *start_r = (char*)r;
	char *start_a = (char*)a;

	/* merges l & r to input array */
	while (i_l < size_l && i_r < size_r)
	{
		if (0 < cmp(start_l + i_l * size, start_r + i_r * size, NULL))
		{
			memcpy(start_a + i_a * size, start_r + i_r * size, size);
			++i_r;		
		}
		else
		{
			memcpy(start_a + i_a * size, start_l + i_l * size, size);	
			++i_l;
		}	

		++i_a;
	}
	
	/* if there are some leftovers, copies them to input array */
	while (i_l < size_l)
	{
		memcpy(start_a + i_a * size, start_l + i_l * size, size);

		++i_l;
		++i_a;
	}

	while (i_r < size_r)
	{
		memcpy(start_a + i_a * size, start_r + i_r * size, size);

		++i_r;	
		++i_a;
	}	

} 
