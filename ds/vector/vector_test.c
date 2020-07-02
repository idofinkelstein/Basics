/***********************
File name: ilrd_vector_test.c
Author: Ido Finkelstein
Reviewer: Tal Kornblum
Date: 8/6/2020
************************/

#include <stdio.h>

#include "vector.h"
/* API testing functions declaration */
vector_t *VectorCreateTest(size_t capacity);
void VectorDestroyTest(vector_t *vector);
void VectorSizeTest(vector_t *vector);
void VectorCapacityTest(vector_t *vector);
void VectorPushBackTest(vector_t *vector, void *data);
void VectorSetElementTest(vector_t *vector, size_t index, void *data);
void VectorGetElementTest(vector_t *vector, size_t index);
void VectorPopBackTest(vector_t *vector);

void Scenario1Test(vector_t *vector);
void Scenario2Test(vector_t *vector);

int main()
{
	vector_t *vector = NULL;

	/* testing API functions */
	vector = VectorCreateTest(5);
	VectorPushBackTest(vector, "11");
	VectorSetElementTest(vector, 0 ,"22");
	VectorGetElementTest(vector, 0);
	VectorSizeTest(vector);
	VectorCapacityTest(vector);
	VectorPopBackTest(vector);
	VectorDestroyTest(vector);

	printf("scenario1 is now tested\n");
	Scenario1Test(vector);

	printf("scenario2 is now tested\n");
	Scenario2Test(vector);
	

	return 0;
}

vector_t *VectorCreateTest(size_t capacity)
{
	return (VectorCreate(capacity));
}

void VectorDestroyTest(vector_t *vector)
{
	VectorDestroy(vector);
}

void VectorSizeTest(vector_t *vector)
{
	printf("size = %ld\n", VectorSize(vector));
}

void VectorCapacityTest(vector_t *vector)
{
	printf("capacity = %ld\n", VectorCapacity(vector));
}

void VectorPushBackTest(vector_t *vector, void *data)
{
	VectorPushBack(vector, data);
}

void VectorSetElementTest(vector_t *vector, size_t index, void *data)
{
	VectorSetElement(vector, index, data);
}

void VectorGetElementTest(vector_t *vector, size_t index)
{
	printf("%s\n", (char*)VectorGetElement(vector, index));
}

void VectorPopBackTest(vector_t *vector)
{
	VectorPopBack(vector);
}

/* increases size multiple times with push back function */
void Scenario1Test(vector_t *vector)
{
	vector = VectorCreateTest(2);
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorPushBackTest(vector, "11");
	VectorSizeTest(vector);
	VectorCapacityTest(vector);
	VectorDestroyTest(vector);
}
/* reduces size and capacity multiple times */
void Scenario2Test(vector_t *vector)
{
	
	vector = VectorCreateTest(5);
	Scenario1Test(vector);
	
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);

	VectorSizeTest(vector);
	VectorCapacityTest(vector);

	VectorDestroyTest(vector);
}
