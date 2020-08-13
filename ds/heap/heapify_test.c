
#include <stdio.h>
#include <stdlib.h> /* rand, srand */

#include "heapify.h"

int Compare(const void *data1, const void *data2, void *param);
static void SetRandArray(int *arr, size_t size, size_t end_of_range);

int main()
{
	size_t size = 20;
	int arr[32] = {0};
	size_t i = 0;


	SetRandArray(arr, size, 32);
	
	
	for (i = 0; i < size; ++i)
	{
		printf("%d, ", arr[i]);
	}
	
	puts("\n");

	for (i = 0; i < size; ++i)
	{
		HeapifyUp(arr, size, size - 1 - i, sizeof(int), Compare, NULL);
	}

	for (i = 0; i < size; ++i)
	{
		printf("%d, ", arr[i]);
	}
	puts("");

	return 0;
}

/* compares integers */
int Compare(const void *data1, const void *data2, void *param)
{
	(void)param;

	return (*(int*)data1 - *(int*)data2);
}

static void SetRandArray(int *arr, size_t size, size_t end_of_range)
{
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		arr[i] = 1+ rand() % end_of_range;
	}
}

