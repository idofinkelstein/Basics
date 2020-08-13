/*********************
File name: bubble_sort.c
Author: Ido Finkelstein
Reviewer: Shiran Hodeda
Data: 17/7/2020
**********************/

#include <stdbool.h> /* true, false */

#include "sort.h"

void SwapBytes(char *byte1, char *byte2, size_t n_bytes);

void BubbleSort(void *base, size_t nmemb , size_t size,
                  sort_cmp_func_t cmp,
                  void *arg)
{
	size_t i = 0;
	size_t j = 0;
	void *curr = base;
	void *start = base;
	void *next = NULL;
	int is_sorted = false; /* this boolian tells when to stop sorting */

	for (i = 0; (i < nmemb - 1) && !is_sorted; ++i)
	{
		is_sorted = true;

		/* this loop compares adjacent cells and swaps if needed. */
		for (j = 0; j < nmemb - i - 1; ++j)
		{
			next = (char*)curr + size;

			if (0 < cmp(curr, next, arg))
			{	
					SwapBytes(curr, next, size);
					is_sorted = false;		
			}

			curr  = (char*)curr + size;
		}

		curr = start;
	}
}

