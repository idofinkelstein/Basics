/***********************
File name: radix_sort_test.c
Author: Ido Finkelstein
Reviewer: Anna Poryadkov
Date: 20/7/2020
************************/

#include <stdio.h> /* printf */

#include "radix_sort.h"

void CountingSortTest(void);
void RAdixSortTest(void);

int main()
{
	CountingSortTest();
	RAdixSortTest();

	return 0;
}

void CountingSortTest(void)
{
	uint arr[] = {3, 5, 10, 9, 4, 6, 3, 11, 3, 4, 3, 12, 7,
				  44, 2, 32, 23, 19, 20, 8, 11, 3, 14, 13, 76};
	size_t size = sizeof(arr) / sizeof(int);
	size_t i = 0;

	puts("\n*** testing counting sort ***");
	puts("unsorted:");

	for (i = 0; i < size; ++i)
	{
		printf("%u, ", arr[i]);
	}

	puts("");

	CountingSort(arr, size, 2, 76);

	puts("sorted:");
	
	for (i = 0; i < size; ++i)
	{
		printf("%u, ", arr[i]);
	}

	puts("");
}

void RAdixSortTest(void)
{
	uint arr[] = {3, 5, 10, 9, 4, 6, 3, 11, 3, 4, 3, 12, 7,
				  44, 2, 32, 23, 19, 20, 8, 11, 3, 14, 13, 76};
	size_t size = sizeof(arr) / sizeof(int);
	size_t i = 0;

	puts("\n*** testing radix sort ***");
	puts("unsorted:");

	for (i = 0; i < size; ++i)
	{
		printf("%u, ", arr[i]);
	}

	puts("");

	RadixBitsSort(arr, size, 11);
	
	puts("sorted:");

	for (i = 0; i < size; ++i)
	{
		printf("%u, ", arr[i]);
	}

	puts("");
}
