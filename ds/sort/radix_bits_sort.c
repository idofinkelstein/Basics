/***********************
File name: radix_bits_sort.c
Author: Ido Finkelstein
Reviewer: Anna Poryadkov
Date: 20/7/2020
************************/

#include <stdlib.h> /* calloc, free */
#include <string.h> /* memcpy       */

#include "radix_sort.h"

#define MALLOC_FAILED 1
#define SUCCESS 0

void CountingSortHelper(uint *arr, 
					    uint *buffer, 
					    size_t size, 
					    uint *count_arr,
					    size_t range,					
					    uint to_mask,
						uint chunk,
					    uint min);

int RadixBitsSort(uint *arr, size_t size, size_t num_of_bits)
{
	uint range = 1 << num_of_bits;
	unsigned *count_arr = (unsigned*)calloc(range, sizeof(unsigned));
	unsigned *buffer = (unsigned*)calloc(size, sizeof(unsigned));
	size_t i = 0;
	uint mask = (uint)((1ul << num_of_bits) - 1);
	uint min = 0; /* unrelevant in this function */
	uint chunk = 0;

	if (NULL == count_arr)
	{
		return (MALLOC_FAILED);
	}
	
	if (NULL == buffer)
	{
		free(count_arr);

		return (MALLOC_FAILED);
	}

	while (mask)
	{
		if (!(i & 0x1)) /* if even */
		{
			CountingSortHelper(arr, buffer, size, count_arr, 
							   range, mask, chunk, min);
		}
		else
		{
			CountingSortHelper(buffer, arr, size, count_arr, 
							   range, mask, chunk, min);
		}
		
		mask <<= num_of_bits;
		
		chunk += num_of_bits;

		++i;
	}

	if (i & 0x1) /* if odd */
	{
		memcpy(arr, buffer, size * sizeof(uint));
	}

	free(count_arr);
	free(buffer);

	return (SUCCESS);
}

int CountingSort(uint *arr, size_t size, uint min, uint max)
{
	size_t range = max - min + 1;
	uint *count_arr = (unsigned*)calloc(range, sizeof(unsigned));
	uint *result_arr = (unsigned*)calloc(size, sizeof(unsigned));
	uint to_mask = ~0x0; /* constant value in this function */

	if (NULL == count_arr)
	{
		return (MALLOC_FAILED);
	}

	if (NULL == result_arr)
	{
		free(count_arr);

		return (MALLOC_FAILED);
	}

	CountingSortHelper(arr, result_arr, size, count_arr, range, to_mask, 0, min);

	memcpy(arr, result_arr, size * sizeof(uint));

	free(count_arr);
	free(result_arr);

	return (SUCCESS);
}

void CountingSortHelper(uint *arr, 
					    uint *buffer, 
					    size_t size, 
					    uint *count_arr,
					    size_t range,					
					    uint to_mask,
						uint chunk,
					    uint min)
{
	size_t i = 0;
	uint to_place = 0;
	uint place = 0;
	unsigned shift = min;

	for (i = 0; i < size; ++i)
	{
		++count_arr[((arr[i] & to_mask) >> chunk) - shift]; 
	}

	for (i = 1; i < range; ++i)
	{
		count_arr[i] += count_arr[i - 1];
	}

	for (i = 0; i < size; ++i)
	{			
		to_place = arr[size - i - 1];

		place = count_arr[((to_place & to_mask) >> chunk)- shift];

		buffer[place - 1] = to_place;

		--count_arr[((to_place & to_mask) >> chunk)- shift];
	}

	for (i = 0; i < range; ++i)
	{
		count_arr[i] = 0;
	}

}
