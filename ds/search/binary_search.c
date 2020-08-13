#include "binary_search.h"

int Search(int arr[], size_t begin, size_t end, int value);

int BinarySearch(int arr[], size_t size, int value)
{
	size_t begin = 0;
	size_t end = size - 1;
	size_t middle = (begin + end) / 2;

	while ((long)begin <= (long)end)
	{
		middle = (begin + end) / 2;

		if (arr[middle] == value)
		{
			return (middle);
		}
		else if (arr[middle] > value)
		{
			end = middle - 1;
		}
		else
		{
			begin = middle + 1;
		}
	}

	return -1;
}

int BinarySearchRecursive(int arr[], size_t size, int value)
{
	size_t begin = 0;
	size_t end = size - 1;
	
	return (Search(arr, begin, end, value));
}

int Search(int arr[], size_t begin, size_t end, int value)
{
	size_t middle = (begin + end) / 2;

	if((long)begin > (long)end)
	{
		return -1;
	}
	else if (arr[middle] > value)
	{
		return (Search(arr, begin, middle - 1, value));		
	}
	else if (arr[middle] < value) 
	{
		return (Search(arr, middle + 1, end, value));		
	}
	
	return (middle);
}
