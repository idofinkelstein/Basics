#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

int CompareMin(const void *data1, const void *data2, void *param);

typedef struct arr_info
{
	int *arr;
	size_t size;
	size_t index;
	size_t arr_num;
}arr_info_t;

void *MergeKArrays(arr_info_t *arr_of_arr, size_t num_of_arrs)
{
	heap_t *heap = HeapCreate(CompareMin, NULL);
	int *merged = NULL;
	size_t merged_arr_size = 0;
	size_t i = 0;
	size_t j = 0;
	
	for (i = 0; i < num_of_arrs; ++i)
	{
		merged_arr_size += (arr_of_arr + i)->size;
	}

	merged = (int*)malloc(sizeof(int) * merged_arr_size);
	if (merged == NULL)
	{
		HeapDestroy(heap);
		return (NULL);
	}

	for (i = 0; i < merged_arr_size; ++i)
	{
		while(HeapSize(heap) < num_of_arrs)
		{
			if ((arr_of_arr + j)->index < (arr_of_arr + j)->size)
			{
				HeapPush(heap, &(arr_of_arr + j)->arr[(arr_of_arr + j)->index]);
			}
			++j;
		}

		merged[i] = HeapPop(heap);
	}

	HeapDestroy(heap);

	return (merged);
}

int main()
{
	int arr1[] = {1, 3, 4, 5, 5};
	int arr2[] = {0, 3, 5, 6};
	int arr3[] = {2, 2, 4, 5, 6, 7, 8, 10};
	size_t size1 = sizeof(arr1) / sizeof(int);
	size_t size2 = sizeof(arr2) / sizeof(int);
	size_t size3 = sizeof(arr3) / sizeof(int);
	size_t num_of_arrs = 3;
	arr_info_t *arr_of_arr = NULL;

	arr_of_arr = (arr_info_t*)malloc(3 * sizeof(arr_info_t));
	if (arr_of_arr == NULL)
	{
		return 1;
	}

	(arr_of_arr + 0)->arr = arr1;
	(arr_of_arr + 1)->arr = arr2;
	(arr_of_arr + 2)->arr = arr3;
	(arr_of_arr + 0)->size = size1;
	(arr_of_arr + 1)->size = size2;
	(arr_of_arr + 2)->size = size3;
	(arr_of_arr + 0)->index = 0;
	(arr_of_arr + 1)->index = 0;
	(arr_of_arr + 2)->index = 0;
	(arr_of_arr + 0)->arr_num = 0;
	(arr_of_arr + 1)->arr_num = 1;
	(arr_of_arr + 2)->arr_num = 2;


	MergeKArrays(arr_of_arr, num_of_arrs);

	free(arr_of_arr);

	return 0;
}

int CompareMin(const void *data1, const void *data2, void *param)
{
	(void)param;

	return (*(int*)data2 - *(int*)data1);
}
