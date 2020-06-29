/***********************
File name: sorted_list_test.c
Author: Ido Finkelstein
Reviewer: Tal Kornblum
Date: 24/6/2020
************************/

#include <stdio.h> 	 /* printf 		*/
#include <stdbool.h> /* true, false */
#include "sorted_list.h"

#define SUCCESS 0
#define FAILURE 1

/* utility function declarations */
int IsBefore(const void *data1, const void *data2, void *param);
int ChangeValue(void *data, void *param);
int IsMatch(const void *data, void *param);
int IsBeforeFloat(const void *data1, const void *data2, void *param);

/* test case function declarations */
void Scenario1Test(void);
void Scenario2Test(void);
void Scenario3Test(void);
void Scenario4Test(void);
void Scenario5Test(void);
void Scenario6Test(void);
void Scenario7Test(void);
void Scenario8Test(void);
void Scenario9Test(void);

int main()
{
	sorted_list_iter_t iter;
	void *param = NULL;
	sorted_list_is_before_func_t is_before = IsBefore;
	sorted_list_t *list = SortedListCreate(is_before, param);
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	

	printf("emptiness = %d\n", SortedListIsEmpty(list));

	iter = SortedListInsert(list, &arr[4]);

	iter = SortedListInsert(list, &arr[3]);

	printf("%d\n", SortedListIterIsEqual(iter, SortedListEnd(list)));

	printf("%d\n", *(int*)SortedListGetData(iter));

	iter = SortedListNext(iter);

	printf("%d\n", SortedListIterIsEqual(iter, SortedListEnd(list)));

	SortedListDestroy(list);

/******************************************************************************/

	Scenario1Test();
	Scenario2Test();
	Scenario3Test();
	Scenario4Test();
	Scenario5Test();
	Scenario6Test();
	Scenario7Test();
	Scenario8Test();
	Scenario9Test();

	return 0;
}

/* tests Insert */
void Scenario1Test(void)
{
	sorted_list_iter_t iter;
	void *param = NULL;
	sorted_list_is_before_func_t is_before = IsBefore;
	sorted_list_t *list = SortedListCreate(is_before, param);
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	printf("test scenario1: case: pops front & back and remove in the middle\n");

	SortedListInsert(list, &arr[4]);
	SortedListInsert(list, &arr[1]);
	SortedListInsert(list, &arr[3]);
	SortedListInsert(list, &arr[10]);
	SortedListInsert(list, &arr[5]);
	SortedListInsert(list, &arr[9]);
	SortedListInsert(list, &arr[2]);
	SortedListInsert(list, &arr[7]);
	SortedListInsert(list, &arr[6]);
	SortedListInsert(list, &arr[8]);

	printf("size = %ld\n", SortedListSize(list));

	iter = SortedListBegin(list);

	while (!SortedListIterIsEqual(iter, SortedListEnd(list)))
	{
		printf("%d ", *(int*)SortedListGetData(iter));

		iter = SortedListNext(iter);
	}

	puts("");

	iter = SortedListBegin(list);

	iter = SortedListNext(iter);
	iter = SortedListNext(iter);
	iter = SortedListNext(iter);
	iter = SortedListNext(iter);

	SortedListRemove(iter); /* this supposed to remove 5 */

	SortedListPopFront(list); /* 1 */
	SortedListPopBack(list); /* 10 */

	iter = SortedListBegin(list);

	while (!SortedListIterIsEqual(iter, SortedListEnd(list)))
	{
		printf("%d ", *(int*)SortedListGetData(iter));

		iter = SortedListNext(iter);
	}

	puts("");

	printf("size = %ld\n", SortedListSize(list));

	SortedListDestroy(list);
}

/* tests Find */
void Scenario2Test(void)
{
	sorted_list_iter_t iter;
	void *param = NULL;
	sorted_list_is_before_func_t is_before = IsBeforeFloat;
	sorted_list_t *list = SortedListCreate(is_before, param);
	float arr[] = {0, 1, 2, 3, 4.9, 5, 5.5, 5.1, 5.01, 9, 10};
	float to_find = 5.1;

	printf("test scenario2: case: Find - 2 numbers out of bound, 1 in the middle"
		   " and 2 at the edges.\n");

	SortedListInsert(list, &arr[4]);
	SortedListInsert(list, &arr[1]);
	SortedListInsert(list, &arr[3]);
	SortedListInsert(list, &arr[10]);
	SortedListInsert(list, &arr[5]);
	SortedListInsert(list, &arr[9]);
	SortedListInsert(list, &arr[2]);
	SortedListInsert(list, &arr[7]);
	SortedListInsert(list, &arr[6]);
	SortedListInsert(list, &arr[8]);
	SortedListInsert(list, &arr[0]);

	iter = SortedListFind(list, SortedListBegin(list), SortedListEnd(list), &to_find);

	if (!SortedListIterIsEqual(iter, SortedListEnd(list)))
	{
		printf("%.1f\n", *(float*)SortedListGetData(iter));
	}

	to_find = -0.5;
	iter = SortedListFind(list, SortedListBegin(list), SortedListEnd(list), &to_find);

	if (!SortedListIterIsEqual(iter, SortedListEnd(list)))
	{
		printf("%.1f\n", *(float*)SortedListGetData(iter));
	}

	to_find = 0;
	iter = SortedListFind(list, SortedListBegin(list), SortedListEnd(list), &to_find);

	if (!SortedListIterIsEqual(iter, SortedListEnd(list)))
	{
		printf("%.1f\n", *(float*)SortedListGetData(iter));
	}

	to_find = 10;
	iter = SortedListFind(list, SortedListBegin(list), SortedListEnd(list), &to_find);

	if (!SortedListIterIsEqual(iter, SortedListEnd(list)))
	{
		printf("%.1f\n", *(float*)SortedListGetData(iter));
	}

	to_find = 12.12;
	iter = SortedListFind(list, SortedListBegin(list), SortedListEnd(list), &to_find);

	if (!SortedListIterIsEqual(iter, SortedListEnd(list)))
	{
		printf("%.1f\n", *(float*)SortedListGetData(iter));
	}

	SortedListDestroy(list);
}

/* tests for each */
void Scenario3Test(void)
{
	sorted_list_iter_t iter;
	void *param = NULL;
	sorted_list_is_before_func_t is_before = IsBefore;
	sorted_list_do_action_func_t do_action = ChangeValue;
	sorted_list_t *list = SortedListCreate(is_before, param);
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int x = 5;
	
	printf("test scenario3: case: ForEach - adds 5 to every node\n");

	SortedListInsert(list, &arr[4]);
	SortedListInsert(list, &arr[1]);
	SortedListInsert(list, &arr[3]);
	SortedListInsert(list, &arr[10]);
	SortedListInsert(list, &arr[5]);
	SortedListInsert(list, &arr[9]);
	SortedListInsert(list, &arr[2]);
	SortedListInsert(list, &arr[7]);
	SortedListInsert(list, &arr[6]);
	SortedListInsert(list, &arr[8]);

	SortedListForEach(SortedListBegin(list), SortedListEnd(list), do_action, &x);

	iter = SortedListBegin(list);

	while (!SortedListIterIsEqual(iter, SortedListEnd(list)))
	{
		printf("%d ", *(int*)SortedListGetData(iter));

		iter = SortedListNext(iter);
	}

	puts("");

	SortedListDestroy(list);
}

/* test scenario4: case: FindIf (1, 5, 10) */
void Scenario4Test(void)
{
	sorted_list_iter_t iter;
	void *param = NULL;
	sorted_list_is_before_func_t is_before = IsBefore;
	sorted_list_is_match_func_t is_match = IsMatch;
	sorted_list_t *list = SortedListCreate(is_before, param);
	int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	printf("test scenario4: case: FindIf (1, 5, 10)\n");

	SortedListInsert(list, &arr[4]);
	SortedListInsert(list, &arr[1]);
	SortedListInsert(list, &arr[3]);
	SortedListInsert(list, &arr[10]);
	SortedListInsert(list, &arr[5]);
	SortedListInsert(list, &arr[9]);
	SortedListInsert(list, &arr[2]);
	SortedListInsert(list, &arr[7]);
	SortedListInsert(list, &arr[6]);
	SortedListInsert(list, &arr[8]);

	iter = SortedListFindIf(SortedListBegin(list), SortedListEnd(list), is_match, &arr[1]);

	if (NULL != iter.internal_iter)
	{
		printf("%d\n", *(int*)SortedListGetData(iter));
	}
	
	iter = SortedListFindIf(SortedListBegin(list), SortedListEnd(list), is_match, &arr[5]);

	if (NULL != iter.internal_iter)
	{
		printf("%d\n", *(int*)SortedListGetData(iter));
	}

	iter = SortedListFindIf(SortedListBegin(list), SortedListEnd(list), is_match, &arr[10]);

	if (NULL != iter.internal_iter)
	{
		printf("%d\n", *(int*)SortedListGetData(iter));
	}

	SortedListDestroy(list);
}

/* test scenario5: case: Merge - 2 identical length lists */
void Scenario5Test(void)
{
	void *param = NULL;
	sorted_list_is_before_func_t is_before = IsBefore;
	sorted_list_t *dest_list = SortedListCreate(is_before, param);
	sorted_list_t *src_list = SortedListCreate(is_before, param);
	sorted_list_iter_t iter;
	int dest[] = {-6, 2, 4, 5, 7, 12, 14, 15, 20, 22, 50};
	int src[] = {-5, 1, 3, 6, 8, 9, 10, 20, 24, 52, 53};

	printf("test scenario5: case: Merge - 2 identical length lists\n");

	SortedListInsert(dest_list, &dest[4]);
	SortedListInsert(dest_list, &dest[1]);
	SortedListInsert(dest_list, &dest[3]);
	SortedListInsert(dest_list, &dest[10]);
	SortedListInsert(dest_list, &dest[5]);
	SortedListInsert(dest_list, &dest[9]);
	SortedListInsert(dest_list, &dest[2]);
	SortedListInsert(dest_list, &dest[7]);
	SortedListInsert(dest_list, &dest[6]);
	SortedListInsert(dest_list, &dest[8]);
	SortedListInsert(dest_list, &dest[0]);

	SortedListInsert(src_list, &src[4]);
	SortedListInsert(src_list, &src[1]);
	SortedListInsert(src_list, &src[3]);
	SortedListInsert(src_list, &src[10]);
	SortedListInsert(src_list, &src[5]);
	SortedListInsert(src_list, &src[9]);
	SortedListInsert(src_list, &src[2]);
	SortedListInsert(src_list, &src[7]);
	SortedListInsert(src_list, &src[6]);
	SortedListInsert(src_list, &src[8]);
	SortedListInsert(src_list, &src[0]);

	SortedListMerge(dest_list, src_list);

	iter = SortedListBegin(dest_list);

	while (!SortedListIterIsEqual(iter, SortedListEnd(dest_list)))
	{
		printf("%d ", *(int*)SortedListGetData(iter));

		iter = SortedListNext(iter);
	}

	puts("");
	
	SortedListDestroy(dest_list);
	SortedListDestroy(src_list);
}

/* test scenario6: case: Merge - dest is an empty list */
void Scenario6Test(void)
{
	void *param = NULL;
	sorted_list_is_before_func_t is_before = IsBefore;
	sorted_list_t *dest_list = SortedListCreate(is_before, param);
	sorted_list_t *src_list = SortedListCreate(is_before, param);
	sorted_list_iter_t iter;
	int src[] = {-5, 1, 3, 6, 8, 9, 10, 20, 24, 52, 53};

	printf("test scenario6: case: Merge - dest is an empty list\n");

	SortedListInsert(src_list, &src[4]);
	SortedListInsert(src_list, &src[1]);
	SortedListInsert(src_list, &src[3]);
	SortedListInsert(src_list, &src[10]);
	SortedListInsert(src_list, &src[5]);
	SortedListInsert(src_list, &src[9]);
	SortedListInsert(src_list, &src[2]);
	SortedListInsert(src_list, &src[7]);
	SortedListInsert(src_list, &src[6]);
	SortedListInsert(src_list, &src[8]);
	SortedListInsert(src_list, &src[0]);

	SortedListMerge(dest_list, src_list);

	iter = SortedListBegin(dest_list);

	while (!SortedListIterIsEqual(iter, SortedListEnd(dest_list)))
	{
		printf("%d ", *(int*)SortedListGetData(iter));

		iter = SortedListNext(iter);
	}

	puts("");
	
	SortedListDestroy(dest_list);
	SortedListDestroy(src_list);
}

/* test scenario7: case: Merge - src is an empty list */
void Scenario7Test(void)
{
	void *param = NULL;
	sorted_list_is_before_func_t is_before = IsBefore;
	sorted_list_t *dest_list = SortedListCreate(is_before, param);
	sorted_list_t *src_list = SortedListCreate(is_before, param);
	sorted_list_iter_t iter;
	int dest[] = {-6, 2, 4, 5, 7, 12, 14, 15, 20, 22, 50};

	printf("test scenario7: case: Merge - src is an empty list\n");

	SortedListInsert(dest_list, &dest[4]);
	SortedListInsert(dest_list, &dest[1]);
	SortedListInsert(dest_list, &dest[3]);
	SortedListInsert(dest_list, &dest[10]);
	SortedListInsert(dest_list, &dest[5]);
	SortedListInsert(dest_list, &dest[9]);
	SortedListInsert(dest_list, &dest[2]);
	SortedListInsert(dest_list, &dest[7]);
	SortedListInsert(dest_list, &dest[6]);
	SortedListInsert(dest_list, &dest[8]);
	SortedListInsert(dest_list, &dest[0]);

	
	SortedListMerge(dest_list, src_list);

	iter = SortedListBegin(dest_list);

	while (!SortedListIterIsEqual(iter, SortedListEnd(dest_list)))
	{
		printf("%d ", *(int*)SortedListGetData(iter));

		iter = SortedListNext(iter);
	}

	puts("");

	SortedListDestroy(dest_list);
	SortedListDestroy(src_list);
}
/* test scenario8: case: Merge - both lists are empty */
void Scenario8Test(void)
{
	void *param = NULL;
	sorted_list_is_before_func_t is_before = IsBefore;
	sorted_list_t *dest_list = SortedListCreate(is_before, param);
	sorted_list_t *src_list = SortedListCreate(is_before, param);
	
	printf("test scenario8: case: Merge - both lists are empty\n");

	SortedListMerge(dest_list, src_list);

	puts("");
	
	SortedListDestroy(dest_list);
	SortedListDestroy(src_list);
}

/* test scenario5: case: Merge - 2 floating point lists with different size */
void Scenario9Test(void)
{
	void *param = NULL;
	sorted_list_is_before_func_t is_before = IsBeforeFloat;
	sorted_list_t *dest_list = SortedListCreate(is_before, param);
	sorted_list_t *src_list = SortedListCreate(is_before, param);
	sorted_list_iter_t iter;
	float dest[] = {-6, 2, 4, 5, 1, 12, 12.543, 345.15, 20.11, 22.11, 50.1};
	float src[] = {0.4, 1.45, 65.63, 2, 1.6, 0.58, -34.9, -111.10, -111.20, 24,
				   52, 53, 1, 2, 2, 2, 76.2, 11.5};

	printf("test scenario5: case: Merge - 2 floating point lists with different size\n");

	SortedListInsert(dest_list, &dest[4]);
	SortedListInsert(dest_list, &dest[1]);
	SortedListInsert(dest_list, &dest[3]);
	SortedListInsert(dest_list, &dest[10]);
	SortedListInsert(dest_list, &dest[5]);
	SortedListInsert(dest_list, &dest[9]);
	SortedListInsert(dest_list, &dest[2]);
	SortedListInsert(dest_list, &dest[7]);
	SortedListInsert(dest_list, &dest[6]);
	SortedListInsert(dest_list, &dest[8]);
	SortedListInsert(dest_list, &dest[0]);

	SortedListInsert(src_list, &src[4]);
	SortedListInsert(src_list, &src[1]);
	SortedListInsert(src_list, &src[3]);
	SortedListInsert(src_list, &src[10]);
	SortedListInsert(src_list, &src[5]);
	SortedListInsert(src_list, &src[9]);
	SortedListInsert(src_list, &src[2]);
	SortedListInsert(src_list, &src[7]);
	SortedListInsert(src_list, &src[6]);
	SortedListInsert(src_list, &src[8]);
	SortedListInsert(src_list, &src[0]);
	SortedListInsert(src_list, &src[11]);
	SortedListInsert(src_list, &src[15]);
	SortedListInsert(src_list, &src[12]);
	SortedListInsert(src_list, &src[14]);
	SortedListInsert(src_list, &src[13]);
	SortedListInsert(src_list, &src[16]);
	SortedListInsert(src_list, &src[17]);

	SortedListMerge(dest_list, src_list);

	iter = SortedListBegin(dest_list);

	while (!SortedListIterIsEqual(iter, SortedListEnd(dest_list)))
	{
		printf("%.3f ", *(float*)SortedListGetData(iter));

		iter = SortedListNext(iter);
	}

	puts("");
	
	SortedListDestroy(dest_list);
	SortedListDestroy(src_list);
}

/* function to pass to ForEach */
int ChangeValue(void *data, void *param)
{
	if (NULL == data)
	{
		return FAILURE;
	}

	*(int*)data = *(int*)data + *(int*)param;

	return SUCCESS;
}

/* function to pass to Create */
int IsBefore(const void *data1, const void *data2, void *param)
{
	/* data2 is the new data */

	return (*(int*)data1 < *(int*)data2);
}

/* function to pass to FindIf */
int IsMatch(const void *data, void *param)
{
	if (*(int*)data == *(int*)param)
	{
		puts("there is a match");
		return (true);
	}

	puts("there isn't match");
	return (false); 
}

/* function to pass to Create */
int IsBeforeFloat(const void *data1, const void *data2, void *param)
{
	/* data2 is the new data */
	
	return (*(float*)data1 < *(float*)data2);
}
