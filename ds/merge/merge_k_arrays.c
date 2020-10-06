#include <stdio.h>
#include <stdlib.h>

#define MAX 0x0FFFFFFF

int Compare(const void *data1, const void *data2, void *param);

typedef struct arr_info
{
	int *arr;
	size_t size;
	size_t index;

}arr_info_t;

void *MergeKArrays(arr_info_t *arr_of_arr, size_t num_of_arrs)
{
	int *merged = NULL;
	size_t merged_arr_size = 0;
	size_t num_of_index = 0;
	size_t i = 0;
	size_t j = 0;
	
	for (i = 0; i < num_of_arrs; ++i)
	{
		merged_arr_size += (arr_of_arr + i)->size;
	}

	merged = (int*)malloc(sizeof(int) * merged_arr_size);
	if (merged == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < merged_arr_size; ++i)
	{
		int elem = MAX;	
	
		for(j = 0; j < num_of_arrs; ++j)
		{
			if ((arr_of_arr + j)->index < (arr_of_arr + j)->size &&
				 0 < Compare(&elem, &(arr_of_arr + j)->arr[(arr_of_arr + j)->index], NULL))
			{
				elem = (arr_of_arr + j)->arr[(arr_of_arr + j)->index];
				num_of_index = j;
			}

		}

		merged[i] = elem;
		++(arr_of_arr + num_of_index)->index;
	}

	return (merged);
}

int main()
{
	int arr1[] = {1, 3, 4, 5, 5};
	int arr2[] = {0, 2, 2, 3};
	int arr3[] = {2, 2, 4, 5, 6, 7, 8, 10, 11, 23};
	int *merged = NULL;
	size_t size1 = sizeof(arr1) / sizeof(int);
	size_t size2 = sizeof(arr2) / sizeof(int);
	size_t size3 = sizeof(arr3) / sizeof(int);
	size_t num_of_arrs = 3;
	size_t i = 0;
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


	merged = MergeKArrays(arr_of_arr, num_of_arrs);

	for (i = 0; i < size1 + size2 + size3; ++i)
	{
		printf("%d, ", merged[i]);
	}
	puts("");

	free(arr_of_arr);
	free(merged);

	return 0;
}

int Compare(const void *data1, const void *data2, void *param)
{
	(void)param;

	return (*(int*)data1 - *(int*)data2 );
}
