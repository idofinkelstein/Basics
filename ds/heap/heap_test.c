/*******************************
File name: heap_test.c
Author: Ido Finkelstein
Reviewer: Gal Shvinkelstein
Date: 13/8/2020
********************************/

#include <stdio.h> /* printf */
#include <assert.h>

#include "heap.h"

/* Utility functions declaration */
int CompareMax(const void *data1, const void *data2, void *param);
int CompareMin(const void *data1, const void *data2, void *param);
int IsMatch(const void *data1, const void *data2, void *param);

/* Test functions declaration */
void TestCase1(void); 
void TestCase2(void);

int main()
{
	TestCase1(); /* test max heap */
	TestCase2(); /* test min heap */

	return 0;
}

void TestCase1(void)
{
	void *param = NULL;
	heap_t *heap = HeapCreate(CompareMax, param);
	int arr[] = {-200, -175, -160, -76, -75, -45, -40, -39, -20, -15, -11, -7,
				 -1, 0, 2, 4, 12, 13, 16, 22, 23, 30, 34, 35, 36, 40, 44, 46, 
				 50, 51, 52, 55, 57, 61, 63, 76, 80, 82, 88, 100, 104, 108, 111,
				 112, 121, 122, 124, 145, 200, 232, 242, 252, 260, 270, 280, 300};
	size_t size = sizeof(arr) / sizeof(int);
	size_t i = 0;

	printf("is empty? %d\n", HeapIsEmpty(heap));
	printf("size = %ld\n", HeapSize(heap));

	for(i = 0; i < size; ++i)
	{
		HeapPush(heap, &arr[i]);
	}

	printf("size = %ld\n", HeapSize(heap));
	printf("size = %ld\n", size);

#ifdef NDEBUG
	Print(heap);
	printf("is max heap? %d\n", IsMaxHeap(heap));
#endif

	printf("removed data = %d\n", *(int*)HeapRemove(heap, &arr[7], IsMatch, param));

#ifdef NDEBUG
	Print(heap);
	printf("is max heap? %d\n", IsMaxHeap(heap));
#endif

	HeapDestroy(heap);
}

void TestCase2(void)
{
	void *param = NULL;
	heap_t *heap = HeapCreate(CompareMin, param);
	int arr[] = {-200, -175, -160, -76, -75, -45, -40, -39, -20, -15, -11, -7,
				 -1, 0, 2, 4, 12, 13, 16, 22, 23, 30, 34, 35, 36, 40, 44, 46, 
				 50, 51, 52, 55, 57, 61, 63, 76, 80, 82, 88, 100, 104, 108, 111,
				 112, 121, 122, 124, 145, 200, 232, 242, 252, 260, 270, 280, 300};
	size_t size = sizeof(arr) / sizeof(int);
	size_t i = 0;

	printf("is empty? %d\n", HeapIsEmpty(heap));
	printf("size = %ld\n", HeapSize(heap));

	for(i = 0; i < size; ++i)
	{
		HeapPush(heap, &arr[i]);
	}

	printf("size = %ld\n", HeapSize(heap));
	printf("size = %ld\n", size);

#ifdef NDEBUG
	Print(heap);
	printf("is min heap? %d\n", IsMinHeap(heap));
#endif

	printf("removed data = %d\n", *(int*)HeapRemove(heap, &arr[7], IsMatch, param));

#ifdef NDEBUG
	Print(heap);
	printf("is min heap? %d\n", IsMinHeap(heap));
#endif

	HeapDestroy(heap);
}

/* compares integers */
int CompareMax(const void *data1, const void *data2, void *param)
{
	(void)param;

	return (*(int*)data1 - *(int*)data2);
}

int CompareMin(const void *data1, const void *data2, void *param)
{
	(void)param;

	return (*(int*)data2 - *(int*)data1);
}

int IsMatch(const void *data1, const void *data2, void *param)
{
	(void)param;

	return (*(int*)data1 == *(int*)data2);
}
