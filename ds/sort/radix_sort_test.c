#include <stdio.h>

#include "radix_sort.h"

int main()
{
	uint arr[] = {3, 5, 10, 9, 4, 6/*, 3, 11, 3, 4, 3, 12, 7*/};
	size_t size = sizeof(arr) / sizeof(int);
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		printf("%u, ", arr[i]);
	}

	puts("");


	/*CountingSort(arr, size, 3, 12);*/
	RadixBitsSort(arr, size, 3);
	
	for (i = 0; i < size; ++i)
	{
		printf("%u, ", arr[i]);
	}

	puts("");


	return 0;
}
