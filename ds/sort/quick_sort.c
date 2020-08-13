/*****************************
File Name: quick_sort.c
Author: Ido Finkelstein
reviewer: Janna T
Date: 10/8/2020
******************************/

#include "sort.h"

void SwapBytes(char *byte1, char *byte2, size_t n_bytes);

static size_t Partition(void *base, 
			   long left, 
			   long right, 
			   size_t size, 
			   sort_cmp_func_t cmp);

static void Sort(void *base, 
		  long left,
		  long right, 
		  size_t size,
		  sort_cmp_func_t cmp);

int QSort(void *base, 
		  size_t nmemb, 
		  size_t size,
		  sort_cmp_func_t cmp)
{
	Sort(base, 0, nmemb - 1, size, cmp);

	return 0;
}

static size_t Partition(void *base, 
			     long left, 
			     long right, 
			     size_t size, 
			     sort_cmp_func_t cmp)
{
	void *pivot = (char*)base + right * size;
	long pi = left;
	long i = 0;

	/* searches for pivot's new position */
	for (i = pi; i < right; ++i)
	{
		if (0 < cmp(pivot, (char*)base + i * size, NULL))
		{
			SwapBytes((char*)base + (pi * size), (char*)base + (i * size), size);
			++pi;		
		}
	}

	SwapBytes(pivot, (char*)base + (pi * size), size);

	return (pi);
}

static void Sort(void *base, 
		  long left,
		  long right, 
		  size_t size,
		  sort_cmp_func_t cmp)
{
	long pi = 0;
	
	if (right <= left)
	{
		return;
	}
		
	pi = Partition(base, left, right, size, cmp);

	Sort(base, left, pi - 1, size, cmp);
	Sort(base,  pi + 1 , right, size, cmp);
}
