/***********************
File name: ilrd_vector_test.c
Author: Ido Finkelstein
Reviewer: Tal Kornblum
Date: 8/6/2020
************************/

#include <stdio.h>
#include "ilrd_vector.h"

int main()
{
	vector_t *vector = VectorCreate(4);
	char str[] = "hello!";
	char str2[] = "bye!";

	VectorSize(vector);

	VectorPushBack(vector, str);
	printf("capacity = %ld\n", VectorCapacity(vector));
	printf("size = %ld\n", VectorSize(vector));
	VectorPushBack(vector, str);
	VectorPushBack(vector, str);
	printf("size = %ld\n", VectorSize(vector));
	VectorPushBack(vector, str);
	VectorPushBack(vector, str);	
	printf("size = %ld\n", VectorSize(vector));

	printf("%s\n", (char*)VectorGetElement(vector, 2));
	VectorSetElement(vector, 2, str2);
	printf("%s\n", (char*)VectorGetElement(vector, 2));

	printf("capacity = %ld\n", VectorCapacity(vector));

	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);
	VectorPopBack(vector);

	printf("capacity = %ld\n", VectorCapacity(vector));
	VectorReserve(vector, 2);
	printf("capacity = %ld\n", VectorCapacity(vector));
	VectorReserve(vector, 12);

	VectorShrinkToFit(vector);

	printf("capacity = %ld\n", VectorCapacity(vector));

	printf("size = %ld\n", VectorSize(vector));

	VectorPushBack(vector, str);
	VectorPushBack(vector, str);
	VectorPushBack(vector, str);
	VectorPushBack(vector, str);
	VectorPushBack(vector, str);
	VectorPushBack(vector, str);
	VectorPushBack(vector, str);
	VectorPushBack(vector, str);
	VectorPushBack(vector, str);
	VectorPushBack(vector, str);
	VectorPushBack(vector, str);
	VectorPushBack(vector, str);
	VectorPushBack(vector, str);

	printf("capacity = %ld\n", VectorCapacity(vector));

	VectorShrinkToFit(vector);

	printf("capacity = %ld\n", VectorCapacity(vector));
	printf("size = %ld\n", VectorSize(vector));

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

	printf("capacity = %ld\n", VectorCapacity(vector));
	printf("size = %ld\n", VectorSize(vector));

	VectorDestroy(vector);	

	return 0;
}
