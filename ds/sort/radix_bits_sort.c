#include <stdlib.h>
#include <stdio.h>
#include <string.h>



#include "radix_sort.h"

#define MALLOC_FAILED 1
#define SUCCESS 0

void CountingSortHelper(uint *arr, 
					    uint *buffer, 
					    size_t size, 
					    uint *count_arr,
					    size_t range,					
					    uint to_mask,
						uint chank,
					    uint min);

int RadixBitsSort(uint *arr, size_t size, size_t num_of_bits)
{
	uint range = 1 << num_of_bits;
	unsigned *count_arr = (unsigned*)calloc(range, sizeof(unsigned));
	unsigned *buffer = (unsigned*)calloc(size, sizeof(unsigned));
	size_t i = 0;
	uint mask = (uint)((1ul << num_of_bits) - 1);
	uint min = 0;
	uint chank = 0;

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
		printf("mask = %u\n", mask);

		if (!(i & 1))
		{
			CountingSortHelper(arr, buffer, size, count_arr, range, mask, chank, min);
		}
		else
		{
			CountingSortHelper(buffer, arr, size, count_arr, range, mask, chank, min);
		}/**/
		
		mask <<= num_of_bits;
		
		++i;
		printf("chank = %u\n", chank);
		chank += num_of_bits;
	
	}

	printf("i = %ld\n", i);
	
	printf("range = %u\n",range);

	if (i & 1)	
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
	
	uint to_mask = ~0;

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
						uint chank,
					    uint min)
{
	size_t i = 0;
	uint to_place = 0;
	uint place = 0;
	unsigned shift = min;

	for (i = 0; i < size; ++i)
	{
		++count_arr[((arr[i] & to_mask) >> chank) - shift]; 
	}

	for (i = 1; i < range; ++i)
	{
		count_arr[i] += count_arr[i - 1];
	}

	for (i = 0; i < size; ++i)
	{	
		/* goes to arr[i] starting in the last cell, takes its value, this
		   value after shifting will be index to the count_arr, the value
		   of count_arr after subtruting 1 will be the index in the result 
		   array that will contain the value of arr[i].  

		*/
		
			to_place = arr[size - i - 1];

			place = count_arr[((to_place & to_mask) >> chank)- shift];

			buffer[place - 1] = to_place;

			--count_arr[((to_place & to_mask) >> chank)- shift];
	}

	for (i = 0; i < range; ++i)
	{
		count_arr[i] = 0;
	}


}
