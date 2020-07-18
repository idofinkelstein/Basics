/*********************
File name: insertion_sort.c
Author: Ido Finkelstein
Reviewer: Shiran Hodeda
Data: 17/7/2020
**********************/

#include "sort.h"

static void SwapBytes(char *byte1, char *byte2, size_t n_bytes);

void InsertionSort(void *base, size_t nmemb, size_t size,
                  sort_cmp_func_t cmp,
                  void *arg)
{
	size_t i = 0;
	void *curr = base;
	void *prev = curr;

	for (i = 0; i < nmemb - 1; ++i)
	{
		curr = (char*)base + (i + 1)* size;
		prev = (char*)curr - size;

		/* this loop checks where to place to current element in 
		   sorted sub array. */
		while(0 < cmp(prev, curr, arg) &&  prev > base)
		{
			SwapBytes(prev, curr, size);
			curr = prev;
			prev = (char*)prev - size;			
		}

		/* this condition completes the process for the arr[0]. */ 
		if(0 < cmp(prev, curr, arg))
		{
			SwapBytes(prev, (char*)prev + size, size);
		}	
	}
}

static void SwapBytes(char *byte1, char *byte2, size_t n_bytes)
{
	char temp = 0;

	while (n_bytes)
	{
		temp = *byte1; 
   	 	*byte1++ = *byte2;
    	*byte2++ = temp;

		--n_bytes;
	}
}
