/*****************************
File Name: quick_sort.c
Author: Ido Finkelstein
reviewer: Janna T
Date: 10/8/2020
******************************/

#include "sort.h"

void SwapBytes(char *byte1, char *byte2, size_t n_bytes);

size_t Partion(void *base, 
			   long left, 
			   long right, 
			   size_t size, 
			   sort_cmp_func_t cmp);

void Sort(void *base, 
		  long left,
		  long right, 
		  size_t size,
		  sort_cmp_func_t cmp);

void QSort(void *base, 
		   size_t nmemb, 
		   size_t size,
		   sort_cmp_func_t cmp)
{
	Sort(base, 0, nmemb - 1, size, cmp);
}

size_t Partion(void *base, 
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

	return pi;
}

void Sort(void *base, 
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
		
	pi = Partion(base, left, right, size, cmp);

	Sort(base, left, pi - 1, size, cmp);
	Sort(base,  pi + 1 , right, size, cmp);
}
