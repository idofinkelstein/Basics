/***********************
File name: pqueue_test.c
Author: Ido Finkelstein
Reviewer: Inbal Elmalech
Date: 26/6/2020
************************/

#include <stdio.h>   /* printf, size_t */
#include <stdbool.h> /* true, false    */
 
#include "pqueue.h"

/* Utitlity function declarations */
int IsBefore(const void *data1, const void *data2);
int IsMatchInt(const void *data, void *param);
int IsBeforeFloat(const void *data1, const void *data2);

/* Test function declarations */
void Scenario1Test(void);
void Scenario2Test(void);
void Scenario3Test(void);

int main()
{
	pqueue_is_before_func_t is_before = IsBefore;
	pqueue_t *pq = PQCreate(is_before);
	int arr[] = {5, 5, 3, 2, 6, 7, 1, 11, 12 ,12 ,24 ,53, 77};

	printf("enqueue status = %d\n",PQEnpqueue(pq, &arr[5]));
	printf("enqueue status = %d\n",PQEnpqueue(pq, &arr[2]));
	printf("enqueue status = %d\n",PQEnpqueue(pq, &arr[0]));
	printf("enqueue status = %d\n",PQEnpqueue(pq, &arr[8]));
	printf("enqueue status = %d\n",PQEnpqueue(pq, &arr[8]));
	printf("size = %ld\n", PQSize(pq));
	printf("emptiness = %d\n", PQIsEmpty(pq));

	if (!PQIsEmpty(pq))
	{
		printf("%d\n", *(int*)PQDequeue(pq));
	}

	PQClear(pq);

	printf("size = %ld\n", PQSize(pq));

	PQDestroy(pq);

/*****************************************************************************/

	Scenario1Test();
	Scenario2Test();
	Scenario3Test();

	return 0;
}

/* tests Erase */
void Scenario1Test(void)
{
	pqueue_is_before_func_t is_before = IsBefore;
	pqueue_t *pq = PQCreate(is_before);
	pqueue_is_match_func_t is_match = IsMatchInt;
	int arr[] = {5, 5, 3, 2, 6, 7, 1, 11, 12 ,12 ,24 ,53, 77};
	size_t size = sizeof(arr) / sizeof(int);
	size_t i = 0;
	int to_match = 7;
	void *data = NULL;

	printf("*** Scenario1Test ***\n");

	for (i = 0; i < size; ++i)
	{
		PQEnpqueue(pq, &arr[i]);
	}

	printf("size = %ld\n", PQSize(pq));

	data = PQErase(pq, is_match, &to_match);
	
	if (NULL != data)
	{
		printf("to_match = %d\n", *(int*)data);
	}
	else
	{
		printf("to_match = NULL\n");
	}

	printf("size = %ld\n", PQSize(pq));

	data = PQErase(pq, is_match, &to_match);

	if (NULL != data)
	{
		printf("to_match = %d\n", *(int*)data);
	}
	else
	{
		printf("to_match = NULL\n");
	}

	printf("size = %ld\n", PQSize(pq));

	PQDestroy(pq);
}

/* tests Enqueue & Dequeue */
void Scenario2Test(void)
{
	pqueue_is_before_func_t is_before = IsBefore;
	pqueue_t *pq = PQCreate(is_before);
	int arr[] = {5, 5, 3, 2, 6, 7, 1, 11, 12 ,12 ,24 ,53, 77};
	size_t size = sizeof(arr) / sizeof(int);
	size_t i = 0;

	printf("*** Scenario2Test ***\n");


	for (i = 0; i < size; ++i)
	{
		PQEnpqueue(pq, &arr[i]);
	}

	while (!PQIsEmpty(pq))
	{
		printf("%d ", *(int*)PQDequeue(pq));
	}
	puts("");

	PQDestroy(pq);	
}

/* tests on floating point */
void Scenario3Test(void)
{
	pqueue_is_before_func_t is_before = IsBeforeFloat;
	pqueue_t *pq = PQCreate(is_before);
	float arr[] = {5.3, 0.23, -3.3, -21, 66.1, 45.45, 5, 3, 2, 6, 7, 1, 11,
				   12 ,12 ,24 ,53, 77, 0.5, 0.25, -87.34, 0, 7.25};
	size_t size = sizeof(arr) / sizeof(float);
	size_t i = 0;

	printf("*** Scenario3Test ***\n");

	for (i = 0; i < size; ++i)
	{
		PQEnpqueue(pq, &arr[i]);
	}

	printf("size = %ld\n", PQSize(pq));
	
	while (!PQIsEmpty(pq))
	{
		printf("%.2f ", *(float*)PQDequeue(pq));
	}
	puts("");

	printf("size = %ld\n", PQSize(pq));	

	PQDestroy(pq);	
}

/* function to pass to Create */
int IsBefore(const void *data1, const void *data2)
{
	/* data2 is the new data */

	return (*(int*)data1 < *(int*)data2);
}

/* function to pass to FindIf */
int IsMatchInt(const void *data, void *param)
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
int IsBeforeFloat(const void *data1, const void *data2)
{
	/* data2 is the new data */
	
	return (*(float*)data1 < *(float*)data2);
}
