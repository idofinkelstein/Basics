/********************************
File name: avl_test.c
Author: Ido Finkelstein
Reviewer: Guy Chen
Date: 1/8/2020
*********************************/

#include <stdio.h>

#include "avl.h"

int Compare(const void *data1, const void *data2, void *param);
int ChangeValue(void *data, void *param);
int PrintTree(void *data, void *param);

void TestCase1(void);
void TestCase2(void);
void TestCase3(void);
void TestCase4(void);

int main()
{
	TestCase1();
	TestCase2();
	TestCase3();
	TestCase4();

	return 0;
}

void TestCase1(void)
{
	avl_t *avl = AVLCreate(Compare, NULL);
			  /* 0   1  2  3  4  5   6   7   8   9  10 */
	int arr[] = {0, 1, 2, 3, 0, 66, 43, 36, 37, 3, 7, 38};
	size_t size = sizeof(arr) / sizeof(int);
	size_t i = 0;
	int x = 3;

	for (i = 0; i < size; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}

	printf("size = %ld\n", AVLSize(avl));

	if (AVLFind(avl, &arr[5]))
	{
		puts("found!");
	}
	else
	{
		puts("not found!");	
	}

	AVLInsert(avl, &x);
	if (AVLFind(avl, &x))
	{
		puts("found!");
	}
	else
	{
		puts("not found!");	
	}

	AVLFind(avl, &arr[1]);

	AVLForEach(avl, ChangeValue, &x);
	AVLForEach(avl, PrintTree, NULL);

	AVLDestroy(avl);
}

void TestCase2(void)
{
	avl_t *avl = AVLCreate(Compare, NULL);
			  /* 0   1  2  3  4  5   6   7   8   9  10 */
	int arr[] = {0, 1, 2, 3, 0, 66, 43, 36, 37, 3, 7, 38};
	size_t size = sizeof(arr) / sizeof(int);
	size_t i = 0;
	int x1 = 36;
	int x2 = 66;
	int x3 = 37;

	for (i = 0; i < size; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}

	printf("size = %ld\n", AVLSize(avl));

	AVLForEach(avl, PrintTree, NULL);

	AVLRemove(avl, &x1);
	AVLRemove(avl, &x2);
	AVLRemove(avl, &x3);

	printf("size = %ld\n", AVLSize(avl));
	AVLForEach(avl, PrintTree, NULL);
	

	AVLDestroy(avl);
}

void TestCase3(void)
{
	avl_t *avl = AVLCreate(Compare, NULL);
			  /* 0  1  2  3  4   5   6   7   8   9  10  11  12 13  14  15  16  17  18 */
	int arr[] = {0, 1, 2, 3, 17, 66, 43, 36, 37, 3, 30, 38, 4, 5, 11, 12, 13, 43, 49};
	size_t size = sizeof(arr) / sizeof(int);
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}

	printf("size = %ld\n", AVLSize(avl));

	printf("is balance? = %d\n", IsBalanced(avl));

	AVLForEach(avl, PrintTree, NULL);

	AVLRemove(avl, &arr[4]);
	AVLRemove(avl, &arr[2]);
	AVLRemove(avl, &arr[1]);
	AVLRemove(avl, &arr[3]);
	AVLRemove(avl, &arr[0]);
	AVLRemove(avl, &arr[7]);
	AVLRemove(avl, &arr[10]);
	AVLRemove(avl, &arr[11]);
	AVLRemove(avl, &arr[12]);

	/* testing debug function (not in the API)*/
	printf("balance = %d\n", IsBalanced(avl));

	printf("size = %ld\n", AVLSize(avl));

	AVLForEach(avl, PrintTree, NULL);
	

	AVLDestroy(avl);
}

void TestCase4(void)
{
	avl_t *avl = AVLCreate(Compare, NULL);
			  /* 0  1  2  3  4   5   6   7   8   9  10  11  12 13  14  15  16  17  18 */
	int arr[] = {0, 1, 2, 3, 17, 66, 43, 36, 37, 3, 30, 38, 4, 5, 11, 12, 13, 43, 49};
	size_t size = sizeof(arr) / sizeof(int);
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		AVLInsert(avl, &arr[i]);
	}
	
	/* testing debug functions (not in the API) */
	puts("in order traversl:");
	ChooseTraversalOrder(avl, 1);

	puts("pre order traversl:");
	ChooseTraversalOrder(avl, 2);

	puts("post order traversl:");
	ChooseTraversalOrder(avl, 3);	


	AVLDestroy(avl);
}

int Compare(const void *data1, const void *data2, void *param)
{
	(void)param;

	return (*(int*)data1 - *(int*)data2);
}

/* function to pass to ForEach */
int ChangeValue(void *data, void *param)
{
	if (NULL == data)
	{
		return 1;
	}

	*(int*)data = *(int*)data + *(int*)param;

	return 0;
}

int PrintTree(void *data, void *param)
{
	(void)param;
	printf("%d\n", *(int*)data);

	return 0;
}
