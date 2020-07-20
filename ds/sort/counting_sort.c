/***********************
File name: counting_sort.c
Author: Ido Finkelstein
Reviewer: Rita Lampert
Date: 19/7/2020
************************/

#include <stdlib.h> /* calloc, free */

#define MALLOC_FAILED -1
#define SECCESS 0

int CountingSort(int *arr, size_t size, int min, int max, int *result)
{
	size_t i = 0;
	long range = max - min + 1;
	int *count_arr = (int*)calloc(range, sizeof(int));
	int shift = min;

	if (NULL == count_arr)
	{
		return (MALLOC_FAILED);
	}
	
	for (i = 0; i < size; ++i)
	{
		++count_arr[arr[i] - shift]; 
	}

	for (i = 1; i < (size_t)range; ++i)
	{
		count_arr[i] += count_arr[i - 1];
	}

	for (i = 0; i < size; ++i)
	{	
		/* goes to arr[i] starting in the last cell, takes its value, this
		   value after shifting will be index to the count_arr, the value
		   of count_arr after subtruting 1 will be the index in the result 
		   array that will contain the value of arr[i]. */ 
		result[count_arr[arr[size - i - 1] - shift] - 1] = arr[size - i - 1];

		--count_arr[arr[size - i - 1] - shift];
	}
	
	free(count_arr);

	return (SECCESS);
}
