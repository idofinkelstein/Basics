/*********************
File name: sort_test.c
Author: Ido Finkelstein
Reviewer: Shiran Hodeda
Data: 17/7/2020
**********************/

#include <stdio.h>   /* printf, puts */
#include <stdlib.h>  /* malloc, free */
#include <strings.h> /* strcasecmp   */
#include <time.h>    /* time		 */

#include "sort.h"

/* compare function declarations */
int Compare(const void *data1, const void *data2, void *param);
int DoubleCompare(const void *data1, const void *data2, void *param);
int StrCaseCmpWrapper(const void *data1, const void *data2, void *param);
int StrCaseCmpWrapper2(const void *data1, const void *data2, void *param);

/* test function declarations */
void BubbleSortTest(void);
void InsertionSortTest(void);
void SelectionSortTest(void);
void StringSelectionSortingTest(void);
void StringBubbleSortingTest(void);
void StringInsertionSortingTest(void);
void Test(void);

int main()
{
	BubbleSortTest();
	InsertionSortTest();
	SelectionSortTest();
	StringSelectionSortingTest();
	StringInsertionSortingTest();
	StringBubbleSortingTest();
	Test();
	
	return 0;
}

void BubbleSortTest(void)
{
	clock_t begin;
	clock_t end; 
    double time_spent;
	int arr[] = {4 , 23, 1, 65, 4, 2, -6, 0, 41, 34, -345, 35, -76};
	size_t size = sizeof(arr) / sizeof(int);
	double arr2[10000] = {0};
	size_t size2 = sizeof(arr2) / sizeof(double);
	size_t i = 0;

	puts("\n*** BubbleSortTest ***");

	BubbleSort(arr, size, sizeof(int) , Compare, NULL);

	for (i = 0; i < size; ++i)
	{
		printf("%d, ", arr[i]);
	}

	puts("");

	for (i = 0; i < size2; ++i)
	{
		arr2[i] = (double)rand() / 100;
	}

	puts("");

	begin = clock();
	BubbleSort(arr2, size2 , sizeof(double) , DoubleCompare, NULL);
	end = clock();

	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time taken to sort array of size 10k with bubble sort is: %f\n",
			time_spent);

	for (i = 0; i < size2 / 100; ++i)
	{

		printf("%.2f, ", arr2[i]);
	}

	puts("");
}

void InsertionSortTest(void)
{
	clock_t begin;
	clock_t end; 
    double time_spent;
	int arr[] = {4 , 23, 1, 65, 4, 2, -6, 0, 41, 34, -345, 35, -76};
	size_t size = sizeof(arr) / sizeof(int);
	int arr2[10000] = {0};
	size_t size2 = sizeof(arr2) / sizeof(int);
	size_t i = 0;

	puts("\n*** InsertionSortTest ***");

	InsertionSort(arr, size, sizeof(int) , Compare, NULL);	

	for (i = 0; i < size; ++i)
	{
		printf("%d, ", arr[i]);
	}

	puts("");

	for (i = 0; i < size2; ++i)
	{
		arr2[i] = -(rand() % 5000);
	}

	puts("");

	begin = clock();
	InsertionSort(arr2, size2 , sizeof(int) , Compare, NULL);
	end = clock();

	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time taken to sort array of size 10k with insertion sort is: %f\n",
			time_spent);

	for (i = 0; i < size2 / 100; ++i)
	{

		printf("%d, ", arr2[i]);
	}

	puts("");
}

void SelectionSortTest(void)
{
	clock_t begin;
	clock_t end; 
    double time_spent;
	int arr[] = {4 , 23, 1, 65, 4, 2, -6, 0, 41, 34, -345, 35, -76};
	size_t size = sizeof(arr) / sizeof(int);
	int arr2[10000] = {0};
	size_t size2 = sizeof(arr2) / sizeof(int);
	size_t i = 0;

	puts("\n*** SelectionSortTest ***");

	SelectionSort(arr, size, sizeof(int) , Compare, NULL);

	for (i = 0; i < size; ++i)
	{
		printf("%d, ", arr[i]);
	}

	puts("");

	for (i = 0; i < size2; ++i)
	{
		arr2[i] = -(rand() % 5000);
	}

	puts("");

	begin = clock();
	SelectionSort(arr2, size2 , sizeof(int) , Compare, NULL);
	end = clock();

	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time taken to sort array of size 10k with selection sort is: %f\n",
			time_spent);

	for (i = 0; i < size2 / 100; ++i)
	{

		printf("%d, ", arr2[i]);
	}

	puts("");
}

void StringInsertionSortingTest(void)
{
	size_t i = 0;
	char **str_arr = malloc(sizeof(char*) * 5);
	char *str1 = "hello";
	char *str2 = "bye";
	char *str3 = "ido";
	char *str4 = "Dog";
	char *str5 = "Cat";

	*(str_arr + 0) = str1;
	*(str_arr + 1) = str2;
	*(str_arr + 2) = str3;
	*(str_arr + 3) = str4;
	*(str_arr + 4) = str5;

	puts("\n*** InsertionSortTest for array of char pointers ***");
	
	InsertionSort(&str_arr[0], 5, sizeof(void*), StrCaseCmpWrapper, NULL);

	for (i = 0; i < 5; ++i)
	{

		printf("%s, ", str_arr[i]);
	}

	puts("");

	free(str_arr);
}

void StringSelectionSortingTest(void)
{
	size_t i = 0;
	char **str_arr = malloc(sizeof(char*) * 5);
	char *str1 = "hello";
	char *str2 = "bye";
	char *str3 = "ido";
	char *str4 = "Dog";
	char *str5 = "Cat";

	*(str_arr + 0) = str1;
	*(str_arr + 1) = str2;
	*(str_arr + 2) = str3;
	*(str_arr + 3) = str4;
	*(str_arr + 4) = str5;

	puts("\n*** SelectionSortTest for array of char pointers ***");	

	SelectionSort(&str_arr[0], 5, sizeof(void*), StrCaseCmpWrapper, NULL);

	for (i = 0; i < 5; ++i)
	{

		printf("%s, ", str_arr[i]);
	}

	puts("");

	free(str_arr);
}

void StringBubbleSortingTest(void)
{
	size_t i = 0;
	char **str_arr = malloc(sizeof(char*) * 5);
	char *str1 = "hello";
	char *str2 = "bye";
	char *str3 = "ido";
	char *str4 = "dog";
	char *str5 = "cat";

	*(str_arr + 0) = str1;
	*(str_arr + 1) = str2;
	*(str_arr + 2) = str3;
	*(str_arr + 3) = str4;
	*(str_arr + 4) = str5;

	puts("\n*** BubbleSortTest for array of char pointers ***");
	
	BubbleSort(str_arr, 5, sizeof(void*), StrCaseCmpWrapper, NULL);

	for (i = 0; i < 5; ++i)
	{
		printf("%s, ", str_arr[i]);
	}

	puts("");

	free(str_arr);
}

void Test(void)
{
	size_t i = 0;
	char sports[5][15] = 
	{
		"golf",
		"hockey",
		"football",
		"cricket",
		"shooting"
	};

	puts("\n*** BubbleSortTest for array of strings ***");

	BubbleSort(sports, 5, 15, StrCaseCmpWrapper2, NULL);

	for (i = 0; i < 5; ++i)
	{
		printf("%s, ", sports[i]);
	}

	puts("");
}

/* compares integers */
int Compare(const void *data1, const void *data2, void *param)
{
	(void)param;

	if (*(int*)data1 > *(int*)data2)
	{
		return 1;
	}
	else if (*(int*)data1 == *(int*)data2)
	{
		return 0;
	}

	return -1;
}

/* compares doubles */
int DoubleCompare(const void *data1, const void *data2, void *param)
{
	(void)param;

	if (*(double*)data1 > *(double*)data2)
	{
		return 1;
	}
	else if (*(double*)data1 == *(double*)data2)
	{
		return 0;
	}

	return -1;
}

/* compares array of pointers to char (char**) */
int StrCaseCmpWrapper(const void *data1, const void *data2, void *param)
{
	(void)param;
	
	return (strcasecmp(*(const char**)data1, *(const char**)data2));
}

/* compares array of strings (char[][]) */
int StrCaseCmpWrapper2(const void *data1, const void *data2, void *param)
{
	(void)param;

	return (strcasecmp((const char*)data1, (const char*)data2));	
}
