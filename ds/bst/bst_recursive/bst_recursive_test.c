/********************************
File name: bst_test.c
Author: Ido Finkelstein
Reviewer: Ori Komemie
Date: 24/7/2020
*********************************/

#include <stdio.h> /* printf */

#include "bst.h"

/* utility function declarations */
int CompareInt(const void *data1, const void *data2, void *param);
int ChangeValue(void *data, void *param);

/* test function declarations */
void TestCase1(void);
void TestCase2(void);
void TestCase3(void);
void TestCase4(void);
void TestCase5(void);

int main()
{
	
	/**/TestCase2();
	TestCase3();
	TestCase4();
	TestCase5();
	TestCase1();

	return 0;
}

int CompareInt(const void *data1, const void *data2, void *param)
{
	(void)param;

	return (*(int*)data1 - *(int*)data2);
}

void TestCase1(void)
{
	bst_t *tree = NULL;
	void *param = NULL;
	bst_iter_t iter1 = {NULL};
	bst_iter_t iter2 = {NULL};
	bst_iter_t iter3 = {NULL};
	bst_iter_t iter4 = {NULL};
	bst_iter_t iter5 = {NULL};
	bst_iter_t iter6 = {NULL};
	bst_iter_t util = {NULL};
	int arr[] = {1, 2, 4, 3, 5, 6, 8, 7, 9, 11, 10, 13, -1};
	int x = 5;

	tree = BSTCreate(CompareInt, param);

	printf("size = %ld\n", BSTSize(tree));	

	iter1 = BSTInsert(tree, &arr[3]); /* 3 */

	printf("size = %ld\n", BSTSize(tree));	

	iter2 = BSTInsert(tree, &arr[0]); /* 1 */
	iter3 = BSTInsert(tree, &arr[5]); /* 6 */
	iter4 = BSTInsert(tree, &arr[4]); /* 5 */
	iter5 = BSTInsert(tree, &arr[9]); /* 11 */
	iter6 = BSTInsert(tree, &arr[1]); /* 2 */
	util = BSTInsert(tree, &x);

	if (util.node != BSTEnd(tree).node)
	{
		puts("inserted!");
	}
	else
	{
		puts("not inserted!");
	}


	printf("size = %ld\n", BSTSize(tree));

	printf("find = %d\n", *(int*)BSTGetData(BSTFind(tree, &arr[4])));

	printf("%d\n", *(int*)BSTGetData(iter1));
	printf("%d\n", *(int*)BSTGetData(iter2));
	printf("%d\n", *(int*)BSTGetData(iter3));
	printf("%d\n", *(int*)BSTGetData(iter4));
	printf("%d\n", *(int*)BSTGetData(iter5));
	printf("%d\n", *(int*)BSTGetData(iter6));

	puts("");

	printf("%d\n", *(int*)BSTGetData(iter2));
	iter2 = BSTNext(iter2);
	printf("%d\n", *(int*)BSTGetData(iter2));
	iter2 = BSTNext(iter2);
	printf("%d\n", *(int*)BSTGetData(iter2));
	iter2 = BSTNext(iter2);
	printf("%d\n", *(int*)BSTGetData(iter2));
	iter2 = BSTNext(iter2);
	printf("%d\n", *(int*)BSTGetData(iter2));
	iter2 = BSTNext(iter2);
	printf("%d\n", *(int*)BSTGetData(iter2));

	puts("");

	printf("find = %d\n", *(int*)BSTGetData(BSTFind(tree, &arr[9])));

	util = BSTFind(tree, &arr[10]);

	if (util.node != BSTEnd(tree).node)
	{
		printf("find = %d\n", *(int*)BSTGetData(util));
	}
	else
	{
		puts("not found!");
	}

	util = BSTFind(tree, &arr[12]);

	if (util.node != BSTEnd(tree).node)
	{
		printf("find = %d\n", *(int*)BSTGetData(util));
	}
	else
	{
		puts("not found!");
	}

	printf("%d\n", *(int*)BSTGetData(iter5));
	iter5 = BSTPrev(iter5);
	printf("%d\n", *(int*)BSTGetData(iter5));
	iter5 = BSTPrev(iter5);
	printf("%d\n", *(int*)BSTGetData(iter5));
	iter5 = BSTPrev(iter5);
	printf("%d\n", *(int*)BSTGetData(iter5));
	iter5 = BSTPrev(iter5);
	printf("%d\n", *(int*)BSTGetData(iter5));
	iter5 = BSTPrev(iter5);
	printf("%d\n", *(int*)BSTGetData(iter5));
	iter5 = BSTPrev(iter5);
	printf("%d\n", *(int*)BSTGetData(iter5));
	

	BSTDestroy(tree);
}

void TestCase2(void)
{
	bst_t *tree = NULL;
	void *param = NULL;
	bst_iter_t iter1 = {NULL};
	bst_iter_t iter2 = {NULL};
	bst_iter_t iter3 = {NULL};
	bst_iter_t iter4 = {NULL};
	bst_iter_t iter5 = {NULL};
	bst_iter_t iter6 = {NULL};
	bst_iter_t util = {NULL};
	int arr[] = {1, 2, 4, 3, 5, 6, 8, 7, 9, 11, 10, 13, -1};
	int x = 5;
	bst_iter_t begin = {NULL};
	bst_iter_t end = {NULL};

	tree = BSTCreate(CompareInt, param);

	printf("size = %ld\n", BSTSize(tree));

	iter1 = BSTInsert(tree, &arr[3]); /* 3 */
	iter2 = BSTInsert(tree, &arr[0]); /* 1 */
	iter3 = BSTInsert(tree, &arr[5]); /* 6 */

	printf("size = %ld\n", BSTSize(tree));

	iter4 = BSTInsert(tree, &arr[4]); /* 5 */

	printf("size = %ld\n", BSTSize(tree));	

	iter5 = BSTInsert(tree, &arr[9]); /* 11 */
	iter6 = BSTInsert(tree, &arr[1]); /* 2 */

	printf("size = %ld\n", BSTSize(tree));

	begin = BSTBegin(tree);
	end = BSTEnd(tree);

	BSTForEach(begin, end, ChangeValue, &x);

	printf("%d\n", *(int*)BSTGetData(iter1));
	printf("%d\n", *(int*)BSTGetData(iter2));
	printf("%d\n", *(int*)BSTGetData(iter3));
	printf("%d\n", *(int*)BSTGetData(iter4));
	printf("%d\n", *(int*)BSTGetData(iter5));
	printf("%d\n", *(int*)BSTGetData(iter6));

	puts("");

	for (util = begin; !BSTIterIsEqual(util, end); util = BSTNext(util))
	{
		printf("%d\n", *(int*)BSTGetData(util));
	}

	BSTDestroy(tree);
}

void TestCase3(void)
{
	bst_t *tree = NULL;
	void *param = NULL;
	bst_iter_t iter1 = {NULL};
	bst_iter_t iter5 = {NULL};
	bst_iter_t util = {NULL};
	int arr[] = {1, 2, 4, 3, 5, 6, 8, 7, 9, 11, 10, 13, -1};
	bst_iter_t begin = {NULL};
	bst_iter_t end = {NULL};

	tree = BSTCreate(CompareInt, param);

	BSTInsert(tree, &arr[3]); /* 3 */
	BSTInsert(tree, &arr[0]); /* 1 */
	BSTInsert(tree, &arr[5]); /* 6 */
	BSTInsert(tree, &arr[4]); /* 5 */
	iter1 = BSTInsert(tree, &arr[9]); /* 11 */
	iter5 = BSTInsert(tree, &arr[1]); /* 2 */

	begin = BSTBegin(tree);
	end = BSTEnd(tree);

	for (util = begin; !BSTIterIsEqual(util, end); util = BSTNext(util))
	{
		printf("%d\n", *(int*)BSTGetData(util));
	}

	puts("");

	BSTRemove(iter1);

	begin = BSTBegin(tree);
	end = BSTEnd(tree);

	for (util = begin; !BSTIterIsEqual(util, end); util = BSTNext(util))
	{
		printf("%d\n", *(int*)BSTGetData(util));
	}

	puts("");

	BSTRemove(iter5);

	begin = BSTBegin(tree);
	end = BSTEnd(tree);

	for (util = begin; !BSTIterIsEqual(util, end); util = BSTNext(util))
	{
		printf("%d\n", *(int*)BSTGetData(util));
	}

	puts("");

	BSTDestroy(tree);
}

void TestCase4(void)
{
	bst_t *tree = NULL;
	void *param = NULL;
	bst_iter_t util = {NULL};
	int arr[] = {1, 2, 4, 3, 5, 6, 8, 7, 9, 11, 10, 13, -1};
	bst_iter_t begin = {NULL};
	bst_iter_t end = {NULL};

	tree = BSTCreate(CompareInt, param);

	BSTInsert(tree, &arr[3]); /* 3 */
	BSTInsert(tree, &arr[1]); /* 2 */
	BSTInsert(tree, &arr[0]); /* 1 */
	BSTInsert(tree, &arr[7]); /* 7 */
	BSTInsert(tree, &arr[12]); /* -1 */
	BSTInsert(tree, &arr[4]); /* 5 */
	BSTInsert(tree, &arr[11]); /* 13 */
	BSTInsert(tree, &arr[8]); /* 9 */
	BSTInsert(tree, &arr[9]); /* 11 */
	BSTInsert(tree, &arr[10]); /* 10 */
	BSTInsert(tree, &arr[6]); /* 8 */
	BSTInsert(tree, &arr[5]); /* 6 */
	BSTInsert(tree, &arr[2]); /* 4 */

	begin = BSTBegin(tree);
	end = BSTEnd(tree);

	printf("size = %ld\n", BSTSize(tree));	

	for (util = begin; !BSTIterIsEqual(util, end); util = BSTNext(util))
	{
		printf("%d\n", *(int*)BSTGetData(util));
	}

	puts("");

	while (!BSTIsEmpty(tree))
	{	
		BSTRemove(BSTBegin(tree));
	}

	printf("size = %ld\n", BSTSize(tree));	

	BSTInsert(tree, &arr[3]); /* 3 */
	BSTInsert(tree, &arr[1]); /* 2 */
	BSTInsert(tree, &arr[0]); /* 1 */
	BSTInsert(tree, &arr[7]); /* 7 */
	BSTInsert(tree, &arr[12]); /* -1 */
	BSTInsert(tree, &arr[4]); /* 5 */
	BSTInsert(tree, &arr[11]); /* 13 */
	BSTInsert(tree, &arr[8]); /* 9 */
	BSTInsert(tree, &arr[9]); /* 11 */
	BSTInsert(tree, &arr[10]); /* 10 */
	BSTInsert(tree, &arr[6]); /* 8 */
	BSTInsert(tree, &arr[5]); /* 6 */
	BSTInsert(tree, &arr[2]); /* 4 */
	
	begin = BSTBegin(tree);
	end = BSTEnd(tree);

	printf("size = %ld\n", BSTSize(tree));	

	for (util = begin; !BSTIterIsEqual(util, end); util = BSTNext(util))
	{
		printf("%d\n", *(int*)BSTGetData(util));
	}

	puts("");

	BSTDestroy(tree);
}

void TestCase5(void)
{
	bst_t *tree = NULL;
	void *param = NULL;
	bst_iter_t util = {NULL};
	int x = 5;

	tree = BSTCreate(CompareInt, param);

	printf("size = %ld\n", BSTSize(tree));	

	util = BSTInsert(tree, &x);

	printf("size = %ld\n", BSTSize(tree));	

	BSTRemove(util);

	printf("size = %ld\n", BSTSize(tree));	

	util = BSTInsert(tree, &x);

	printf("size = %ld\n", BSTSize(tree));	

	BSTRemove(util);

	printf("size = %ld\n", BSTSize(tree));	

	util = BSTInsert(tree, &x);

	printf("size = %ld\n", BSTSize(tree));	

	BSTDestroy(tree);
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
