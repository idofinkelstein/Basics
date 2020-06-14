/*********************
File name: slist_test.c
Author: Ido Finkelstein
Reviewer: Rita Lempert
Date: 13/6/2020
**********************/

#include <stdio.h> /* printf */

#include "slist.h"

#define LIST_SIZE 30
/*
typedef struct slist_node* slist_iter_t;  
typedef struct slist slist_t; 
*/

/* function declarations */
int SListInsertAfterTest(slist_t *slist, slist_iter_t where, void *data);
slist_iter_t SlistNextTest(const slist_iter_t iter, size_t times);
int SListInsertTest(slist_t *slist, slist_iter_t where, void *data);
int IsMatch(void *data, void *param);
int ChangeValue(void *data, void *param);

void Scenario1Test(void);
void Scenario2Test(void);
void Scenario3Test(void);
void Scenario4Test(void);
void Scenario5Test(void);
void scenario6Test(void);
void scenario7Test(void);
void scenario8Test(void);
void scenario9Test(void);
void scenario10Test(void);
void scenario11Test(void);

int main()
{
	slist_is_match_func_t is_match = IsMatch;	
	slist_t *list = SListCreate();
	slist_iter_t util = NULL;

	/* testing API functions */
	printf("%d\n", SListIterIsEqual(SListBegin(list), SListEnd(list)));

	printf("%d\n", SListIsEmpty(list));

	printf("SIZE = %ld\n", SListCount(list));

	util = SListInsert(list, SListEnd(list), "111");

	printf("SIZE = %ld\n", SListCount(list));

	printf("%d\n", SListIterIsEqual(SListBegin(list), SListEnd(list)));

	printf("%d\n", SListIterIsEqual(util, SListEnd(list)));

	util = SListInsertAfter(list, SListBegin(list), "333");

	SlistSetData(util, "444");

	SListFind(SListBegin(list), SListEnd(list), is_match, "444");

	printf("SIZE = %ld\n", SListCount(list));

	printf("%d\n", SListIsEmpty(list));

	SListDestroy(list);

/*-----------------------------------------------------------------------------*/

	/* testing scenarios */
	Scenario1Test();
	Scenario2Test();
	Scenario3Test();
	Scenario4Test();
	Scenario5Test();
	scenario6Test();
	scenario7Test();
	scenario8Test();
	scenario9Test();
	scenario10Test();
	scenario11Test();

	return 0;
}

/* function to InsertAfter in loop and to check return pointer with
   IsEqual */
int SListInsertAfterTest(slist_t *slist, slist_iter_t where, void *data)
{
	size_t i = 0;
	
	slist_iter_t util = NULL;

	for (i = 0; i < LIST_SIZE; ++i)
	{
		util = SListInsertAfter(slist, where, data);
		
		if (SListIterIsEqual(util, SListEnd(slist)))
			{
				return (SListIterIsEqual(util, SListEnd(slist)));
			}
	}

	return (SListIterIsEqual(util, SListEnd(slist)));
}


/* function to Insert in loop and to check return pointer with
   IsEqual */
int SListInsertTest(slist_t *slist, slist_iter_t where, void *data)
{
	size_t i = 0;
	slist_iter_t util = NULL;

	for (i = 0; i < LIST_SIZE; ++i)
	{
		util = SListInsert(slist, where, data);

		if (SListIterIsEqual(util, SListEnd(slist)))
			{
				return (SListIterIsEqual(util, SListEnd(slist)));
			}
	}

	return (SListIterIsEqual(util, SListEnd(slist)));
}

/* function to increment node multiple times */
slist_iter_t SlistNextTest(const slist_iter_t iter, size_t times)
{
	size_t i = 0;
	slist_iter_t util = iter;

	for (i = 0; i < times; ++i)
	{
		util = SlistNext(util);
	}

	return (util);
}

/* tests multiple insertions and shifting a pointer */
void Scenario1Test(void)
{
	slist_t *list = SListCreate();
	slist_iter_t util = NULL;

	printf("%d\n", SListIterIsEqual(SListBegin(list), SListEnd(list)));/**/

	printf("%d\n", SListIsEmpty(list));

	util = SListInsert(list, SListEnd(list), "111");

	SListInsertAfterTest(list, SListBegin(list), "333");

	util = SlistNextTest(util , 7);

	printf("%s\n", (char*)SListGetData(util));

	SlistSetData(util, "444");

	printf("%s\n", (char*)SListGetData(util));

	printf("SIZE = %ld\n", SListCount(list));

	printf("%d\n", SListIsEmpty(list));

	util = SListBegin(list);

	util = SlistNext(util);

	printf("is util = tail: %d\n", SListIterIsEqual(util, SListEnd(list)));

	printf("%d\n", SListIterIsEqual(util, SListEnd(list)));

	SListDestroy(list);

}
/* tests utility functions of insertion (before & after) */
void Scenario2Test(void)
{
	slist_t *list = SListCreate();
	slist_iter_t util = NULL;

	util = SListInsert(list, SListEnd(list), "111");

	SListInsertAfterTest(list, SListBegin(list), "333");

	util = SlistNextTest(util , 7);

	SListInsertTest(list, util, "333");

	printf("%d\n", SListIterIsEqual(SListBegin(list), SListEnd(list)));

	printf("SIZE = %ld\n", SListCount(list));

	SListDestroy(list);
}

/* tests insert functions and if head and tail pointers are in 
   their original place */
void Scenario3Test(void)
{
	
	slist_t *list = SListCreate();
	slist_iter_t util = NULL;

	util = SListInsert(list, SListEnd(list), "111");
	
	SListInsertTest(list, SListEnd(list), "333");
	SListInsertAfterTest(list, SListBegin(list), "333");
	SListInsertTest(list, SListEnd(list), "333");
	
	printf("SIZE = %ld\n", SListCount(list));

	util = SListBegin(list);

	while(util !=  NULL)
	{
		printf("%d ", SListIterIsEqual(util, SListEnd(list)));
		util = SlistNext(util);
	}
	puts("");

	SListDestroy(list);
}

/* testing remove from middle sevral times and whether the return
   pointer is the right one (pointing to tail)*/
void Scenario4Test(void)
{
	slist_t *list = SListCreate();
	slist_iter_t util = NULL;
	slist_iter_t temp  = SListBegin(list);

	util = SListInsert(list, SListEnd(list), "111");
	
	SListInsertTest(list, SListEnd(list), "333");

	printf("SIZE = %ld\n", SListCount(list));

	util = SListBegin(list);

	printf("%d\n", SListIterIsEqual(temp, SListBegin(list)));

	util = SlistNextTest(util , 7);

	util = SListRemove(list, util);
	util = SListRemove(list, util);
	util = SListRemove(list, util);
	util = SListRemove(list, util);
	util = SListRemove(list, util);
	util = SListRemove(list, util);
	util = SListRemove(list, util);

	printf("SIZE = %ld\n", SListCount(list));

	while(util !=  NULL)
	{
		printf("%d ", SListIterIsEqual(util, SListEnd(list)));
		util = SlistNext(util);
	}
	puts("");

	util = SListRemove(list, SListEnd(list));
	util = SListRemove(list, SListEnd(list));

	SListDestroy(list);
}

/* tests remove from 1-element list */
void Scenario5Test(void)
{
	
	slist_t *list = SListCreate();
	slist_iter_t util = NULL;

	printf("SIZE = %ld\n", SListCount(list));

	util = SListInsert(list, SListEnd(list), "111");

	printf("SIZE = %ld\n", SListCount(list));

	util = SListBegin(list);

	util = SListRemove(list, util);
	util = SListRemove(list, util);
	
	printf("SIZE = %ld\n", SListCount(list));

	SListDestroy(list);
}


/* tests SetData and GetData */
void scenario6Test(void)
{
	slist_t *list = SListCreate();
	slist_iter_t util = NULL;
	int x1 = 1;
	int x2 = 2;
	int x3 = 3;
	int x4 = 4;
	int x5 = 5;
	float x = 6.6;

	util = SListInsert(list, SListEnd(list), &x1);	
	util = SListInsert(list, SListBegin(list), &x2);
	util = SListInsert(list, SListBegin(list), &x3);	
	util = SListInsert(list, SListBegin(list), &x4);	
	util = SListInsert(list, SListBegin(list), &x5);


	while (util != SListEnd(list))
	{
		printf("%d ", *(int*)SListGetData(util));
		util = SlistNext(util);
	}

	puts("");
	
	util = SListBegin(list);	

	while (util != SListEnd(list))
	{
		SlistSetData(util, &x);
		util = SlistNext(util);
	}

	util = SListBegin(list);	

	while (util != SListEnd(list))
	{
		printf("%f ", *(float*)SListGetData(util));
		util = SlistNext(util);
	}

	puts("");

	SListDestroy(list);
}

/* tests ForEach */
void scenario7Test(void)
{
	slist_t *list = SListCreate();
	slist_do_action_func_t action = ChangeValue;
	slist_iter_t util = NULL;	
	
	float x1 = 12.3;
	float x2 = 27.04;
	float x3 = 32.23;
	float x4 = 47.113;
	float x5 = 50.09;
	int x = 20;

	SListInsert(list, SListEnd(list), &x1);	
	SListInsert(list, SListBegin(list), &x2);
	SListInsert(list, SListBegin(list), &x3);	
	SListInsert(list, SListBegin(list), &x4);	
	SListInsert(list, SListBegin(list), &x5);

	SListForEach(SListBegin(list), SListEnd(list), action, &x);

	util = SListBegin(list);	

	while (util != SListEnd(list))
	{
		printf("%f ", *(float*)SListGetData(util));
		util = SlistNext(util);
	}

	puts("");

	SListDestroy(list);
}


/* tests insert before somewhere in the middle of the list */
void scenario8Test(void)
{
	slist_t *list = SListCreate();
	slist_iter_t util = NULL;
	int x1 = 1;
	int x2 = 2;
	int x3 = 3;
	int x4 = 4;
	int x5 = 5;

	util = SListInsert(list, SListEnd(list), &x5);	
	util = SListInsert(list, util, &x4);
	util = SListInsert(list, util, &x3);	
	util = SListInsert(list, util, &x2);	
	util = SListInsert(list, util, &x1);

	util = SListBegin(list);
	printf("%d\n", SListIterIsEqual(util, SListBegin(list)));

	while (util != SListEnd(list))
	{
		printf("%d ", *(int*)SListGetData(util));
		util = SlistNext(util);
	}

	puts("");

	printf("%d\n", SListIterIsEqual(util, SListEnd(list)));
	
	SListDestroy(list);
}

/* tests if tail still points to the end after insert before
   multiple times to the end */
void scenario9Test(void)
{
	slist_t *list = SListCreate();
	slist_iter_t util = NULL;
	int x1 = 1;

	util = SListInsert(list, SListEnd(list), &x1);
	util = SListInsert(list, SListEnd(list), &x1);
	util = SListInsert(list, SListEnd(list), &x1);
	util = SListInsert(list, SListEnd(list), &x1);

	util = SListBegin(list);
	util = SlistNextTest(util, 4); /* increment 4 times to tail's position */

	printf("%d\n", SListIterIsEqual(util, SListEnd(list)));
	
	SListDestroy(list);
}

/* tests remove */
void scenario10Test(void)
{
	slist_t *list = SListCreate();
	slist_iter_t util = NULL;
	int x1 = 1;
	int x2 = 2;
	int x3 = 3;
	int x4 = 4;
	int x5 = 5;

	util = SListInsert(list, SListEnd(list), &x5);	
	util = SListInsert(list, util, &x4);
	util = SListInsert(list, util, &x3);	
	util = SListInsert(list, util, &x2);	
	util = SListInsert(list, util, &x1);

	util = SListBegin(list);
	printf("%d\n", SListIterIsEqual(util, SListBegin(list)));

	util = SlistNextTest(util, 3);
	util = SListRemove(list, util);
	util = SListBegin(list);

	while (util != SListEnd(list))
	{
		printf("%d ", *(int*)SListGetData(util));
		util = SlistNext(util);
	}

	puts("");

	printf("%d\n", SListIterIsEqual(util, SListEnd(list)));
	
	SListDestroy(list);
}

/* tests location in the list of return pointer after 
   remove */
void scenario11Test(void)
{
	
	slist_t *list = SListCreate();
	slist_iter_t util = NULL;
	slist_iter_t temp = NULL;

	util = SListInsert(list, SListEnd(list), "111");
	util = SListInsert(list, SListEnd(list), "111");
	temp = SListBegin(list);

	printf("%d\n", SListIterIsEqual(util, temp));
	temp = SlistNext(temp);
	printf("%d\n", SListIterIsEqual(util, temp));
	temp = SlistNext(temp);
	printf("%d\n", SListIterIsEqual(util, temp));

	puts("");
	util = SListRemove(list, util);

	temp = SListBegin(list);

	printf("%d\n", SListIterIsEqual(util, temp));
	temp = SlistNext(temp);
	printf("%d\n", SListIterIsEqual(util, temp));

	util = SListRemove(list, util);
	util = SListRemove(list, util);

	SListDestroy(list);
}

/* function to pass to Find */
int IsMatch(void *data, void *param)
{
	if (*(char*)data == *(char*)param)
	{
		puts("there is a match");
		return 1;
	}

	puts("there isn't match");
	return 0; 
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
