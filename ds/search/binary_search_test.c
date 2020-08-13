#include <stdio.h>

#include "binary_search.h"

void TestCase1(void);

int main()
{
	TestCase1();

	return 0;
}

void TestCase1(void)
{
	int arr[] = {-200, -175, -160, -76, -75, -45, -40, -39, -20, -15, -11, -7,
				 -1, 0, 2, 4, 12, 13, 16, 22, 23, 30, 34, 35, 36, 40, 44, 46, 
				 50, 51, 52, 55, 57, 61, 63, 76, 80, 82, 88, 100, 104, 108, 111,
				 112, 121, 122, 124, 145, 200, 232, 242, 252, 260, 270, 280, 300};
	size_t size = sizeof(arr) / sizeof(int);

	printf("%d\n", BinarySearch(arr, size, 12));
	printf("%d\n", BinarySearch(arr, size, -200));
	printf("%d\n", BinarySearch(arr, size, 300));
	printf("%d\n", BinarySearch(arr, size, 81));
	printf("%d\n", BinarySearch(arr, size, -201));
	printf("%d\n", BinarySearch(arr, size, 301));

	puts("");	

	printf("%d\n", BinarySearchRecursive(arr, size, 12));
	printf("%d\n", BinarySearchRecursive(arr, size, -200));
	printf("%d\n", BinarySearchRecursive(arr, size, 300));
	printf("%d\n", BinarySearchRecursive(arr, size, 81));
	printf("%d\n", BinarySearchRecursive(arr, size, -201));
	printf("%d\n", BinarySearchRecursive(arr, size, 301));
}
