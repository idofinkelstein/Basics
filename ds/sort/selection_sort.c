/*********************
File name: selection_sort.c
Author: Ido Finkelstein
Reviewer: Shiran Hodeda
Data: 17/7/2020
**********************/

#include "sort.h"

void SwapBytes(char *byte1, char *byte2, size_t n_bytes);

void SelectionSort(void *base, size_t nmemb, size_t size,
                  sort_cmp_func_t cmp,
                  void *arg)
{
	size_t i = 0;
	size_t j = 0;
	void *curr = base;
	void *min_position = base;

	for (i = 0; i < nmemb - 1; ++i)
	{
		curr = (char*)base + size;

		for (j = 0; j < nmemb - i - 1; ++j)
		{
			/* obtains the position of the min value. */
			if (0 < cmp(min_position, curr, arg))
			{
				min_position = curr;				
			}

			curr = (char*)curr + size;
		}

		SwapBytes(base, min_position, size);
		base = (char*)base + size;
		min_position = base;
	}
}

