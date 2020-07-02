/***********************
File name: ilrd_vector.c
Author: Ido Finkelstein
Reviewer: Tal Kornblum
Date:  8/6/2020
************************/

#include <stdio.h>     /* printf, size_t */
#include <stdlib.h>    /* malloc, free   */
#include <sys/types.h> /* ssize_t 		 */
#include <assert.h>
#include "vector.h"

#define INC_FACTOR 2 /* increase factor */
#define DEC_FACTOR 2 /* decrease factor */
#define RESIZE_FACTOR 4

enum status
{
	SUCCESS = 0,
	FAILURE
};

struct vector
{
	void **data;
	size_t init_capacity;
	size_t curr_capacity;
	size_t size;
	ssize_t back; /* the last member in vector */
};

vector_t *VectorCreate(size_t capacity)
{
	vector_t *vector = (vector_t*)malloc(sizeof(vector_t));

	if (NULL == vector)
	{
		return (NULL);
	}

	vector->data = (void**)malloc(sizeof(void*) * capacity);

	/* frees vector in case of second allocation failes. */
	if (NULL == vector->data)
	{
		free(vector);
		vector = NULL;

		return (NULL);
	}

	vector->init_capacity = capacity;
	vector->curr_capacity = capacity;
	vector->size = 0;
	vector->back = -1; /* vector is empty */

	return (vector);
}

void VectorDestroy(vector_t *vector)
{
	free(vector->data);
	vector->data = NULL;

	free(vector);
	vector = NULL;
}

void *VectorGetElement(const vector_t *vector, size_t index)
{
	assert(vector);
	assert(index < VectorSize(vector));

	return (*(vector->data + index));
}

void VectorSetElement(vector_t *vector, size_t index, void *element)
{
	assert(vector);
	assert(index < VectorSize(vector));
	
	*(vector->data + index) = element;
}

int VectorPushBack(vector_t *vector, void *element)
{
	void *tmp_data = NULL; /* temporery pointer to store the address returned
							  by realloc. */
	assert(vector);

	++vector->size;

	/* reallocates memory in case of size is greater than current capacity. */
	if (VectorSize(vector) > VectorCapacity(vector))
	{
		tmp_data = realloc(vector->data,
				   INC_FACTOR * vector->curr_capacity * sizeof(void*));

		if(NULL == tmp_data)
		{
			return(FAILURE);
		}

		vector->curr_capacity *= INC_FACTOR;
		vector->data = tmp_data;
	}

	++vector->back;
	
	*(vector->data + vector->back) = element;

	return(SUCCESS);
}

void VectorPopBack(vector_t *vector)
{
	assert(vector);

	if (0 != VectorSize(vector))
	{
		--vector->back;
		--vector->size;
	}

	/* reduces capacity by 2 in case of size < (current capacity / 4) AND 
	   current capacity > initial capacity. */ 
	if ((VectorSize(vector) < (VectorCapacity(vector) / RESIZE_FACTOR)) &&
	   (VectorCapacity(vector) > vector->init_capacity))
	{
		vector->data = realloc(vector->data,
					   (vector->curr_capacity  / DEC_FACTOR) * sizeof(void*));

		vector->curr_capacity /= DEC_FACTOR;
	}
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	void *tmp_data = NULL;

	assert(vector);

	if (new_capacity > VectorCapacity(vector))
	{
		tmp_data = realloc(vector->data, new_capacity * sizeof(void*));

		if(NULL == tmp_data)
		{
			return(FAILURE);
		}

		vector->curr_capacity = new_capacity;
		vector->data = tmp_data;

		return(SUCCESS);
	}

	return(FAILURE);
}

void VectorShrinkToFit(vector_t *vector)
{
	assert(vector);

	if (VectorSize(vector) > vector->init_capacity)
	{
		vector->data = realloc(vector->data, vector->size * sizeof(void*));

		vector->curr_capacity = vector->size;
	}
}

size_t VectorCapacity(const vector_t *vector)
{
	assert(vector);

	return (vector->curr_capacity);
}

size_t VectorSize(const vector_t *vector)
{
	assert(vector);

	return (vector->size);
}

