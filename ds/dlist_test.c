/***********************
File name: dlist_test.c
Author: Ido Finkelstein
Reviewer: Janna Torbilo
Date: 19/6/2020
************************/

#include <stdio.h> /* printf */

#include "dlist.h"

/* utility functions declaration */
int ChangeValue(void *data, void *param);
int IsMatch(const void *data, void *param);

/* test functions declaration */
void scenario1Test(void);
void scenario2Test(void);

int main()
{
	dlist_t *list = DListCreate();
	dlist_iter_t iter = NULL;
	dlist_is_match_func_t is_match = IsMatch;

	iter = DListInsert(list, DListEnd(list), "testing succeeded\0");

	if (iter == DListEnd(list))
	{
		printf("failed to create new node.\n");
	}
	else
	{
		printf("%s\n", (char*)DListGetData(iter));
	}

	printf("emptiness = %d\n", DListIsEmpty(list));

	DListRemove(iter);

	iter = NULL;

	printf("emptiness = %d\n", DListIsEmpty(list));

	DListPushFront(list, "testing push to front\0");

	DListPushBack(list, "testing push to back\0");

	printf("size = %ld\n", DListSize(list));

	DListFind(DListBegin(list), DListEnd(list), is_match, "t");

	printf("%s\n", (char*)DListPopFront(list));

	printf("%s\n", (char*)DListPopBack(list));

	DListDestroy(list);

/*---------------------------------------------------------------------------*/

	scenario1Test();
	scenario2Test();

	return 0;
}

/* tests ForEach */
void scenario1Test(void)
{
	dlist_t *list = DListCreate();
	dlist_do_action_func_t action = ChangeValue;
	dlist_iter_t curr = NULL;	
	
	float x1 = 12.3;
	float x2 = 27.04;
	float x3 = 32.23;
	float x4 = 47.113;
	float x5 = 50.09;
	int x = 20;

	DListInsert(list, DListEnd(list), &x1);	
	DListInsert(list, DListBegin(list), &x2);
	DListInsert(list, DListBegin(list), &x3);	
	DListInsert(list, DListBegin(list), &x4);	
	DListInsert(list, DListBegin(list), &x5);

	DListForEach(DListBegin(list), DListEnd(list), action, &x);

	curr = DListBegin(list);	

	while (curr != DListEnd(list))
	{
		printf("%f ", *(float*)DListGetData(curr));
		curr = DListNext(curr);
	}

	puts("");

	DListDestroy(list);
}


/* function to pass to ForEach */
int ChangeValue(void *data, void *param)
{
	if (NULL == data)
	{
		return 0;
	}

	*(float*)data = *(float*)data + *(int*)param;

	return 1;
}

/* function to pass to Find */
int IsMatch(const void *data, void *param)
{
	if (*(char*)data == *(char*)param)
	{
		puts("there is a match");
		return 1;
	}

	puts("there isn't match");
	return 0; 
}

/* tests iterator manipulations, pop & push in a row and Splice */
void scenario2Test(void)
{
	dlist_t *src = DListCreate();
	dlist_t *dest = DListCreate();
	dlist_iter_t from = NULL;
	dlist_iter_t to = NULL;
	dlist_iter_t where = NULL;
	int range[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	size_t size = sizeof(range) / sizeof(int);
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		DListPushFront(src, &range[i]);
	}

	DListPushFront(dest, &range[0]);
	DListPushFront(dest, &range[9]);

	from = DListNext(DListBegin(src));
	to = DListPrev(DListEnd(src));
	where = DListPrev(DListEnd(dest));

	DListSplice(from, to, where);

	for (i = 0; i < size; ++i)
	{
		printf("%d ", *(int*)DListPopBack(dest));
	}

	puts("");

	while (!DListIsEmpty(src))
	{
		printf("%d ", *(int*)DListPopBack(src));
	}

	puts("");

	DListDestroy(src);
	DListDestroy(dest);
}
