/**************************
File name: heap_sort.c
Author: Ido Finlelstein
Data: 14/8/2020
***************************/

#include "heap.h"
#include "heapify.h"

void SwapBytes(char *byte1, char *byte2, size_t n_bytes);

int HeapSort(void *arr, size_t nmemb, size_t size, heap_cmp_func_t cmp, void *arg)
{
	size_t i = 0;
	long new_nmemb = (long)nmemb;

	for (i = 0; i < nmemb; ++i)
	{
		HeapifyUp(arr, nmemb, i, size, cmp, arg);
	}

	for (i = 0; i < nmemb - 1; ++i)
	{
		SwapBytes(arr, (char*)arr + (nmemb - i - 1) * size, size);
		HeapifyDown(arr, --new_nmemb, 0, size, cmp, arg);
	}

	return 0;
}
