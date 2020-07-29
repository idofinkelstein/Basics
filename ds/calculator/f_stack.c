/**********************
File name: f_stack.c
Author: Ido Finkelstein
Reviewer: Ori Barak
Date: 29/7/2020
***********************/

#include <stdlib.h> /* malloc, free */
#include <assert.h>

#include "f_stack.h"


#define ERROR 1
#define SUCCESS 0

struct stack
{
	size_t top;
	size_t capacity;
	float *head;
};

/* creates a new stack */
f_stack_t* FStackCreate(size_t capacity)
{
	f_stack_t *stack_ptr = (f_stack_t *)malloc(sizeof(f_stack_t));

	if (!stack_ptr)
	{
		return (NULL);
	}

	stack_ptr->capacity = capacity;
	stack_ptr->head = (float *)malloc(sizeof(float) * capacity);

	if (!stack_ptr)
    {
		free(stack_ptr);
		stack_ptr = NULL;

		return (NULL);
	}

	stack_ptr->top = 0;

	return (stack_ptr);
}

/* deletes the stack and releases the memory */
void FStackDestroy(f_stack_t *stack)
{
	assert(stack);

	free(stack->head);
	stack->head = NULL;
	free(stack);
	stack = NULL;
}

/* pushes a new element to the top of the stack */
int FStackPush(f_stack_t *stack, float element)
{
	assert(stack);

	if(stack->top == stack->capacity )	
	{	
		return (ERROR);
	}
	
	stack->head[stack->top] = element; 
	++(stack->top);

	return (SUCCESS);
}

/* removes the last added element from the stack */
void FStackPop(f_stack_t *stack)
{
	assert(stack);

	if (!FStackIsEmpty(stack))
	{	
		/*stack->head[(stack->top) - 1] = NULL; */
		--(stack->top);
	}
}

/* retrieves the last added element from the stack */
float FStackPeek(f_stack_t *stack)
{
	float element = 0;

	assert(stack);

	if(0 == stack->top)
	{
		return (0);
	}
	
	element = stack->head[(stack->top) - 1];

	return (element);
}

/* returns the current number of the elements at the stack */
size_t FStackSize(f_stack_t *stack)
{
	assert(stack);

	return (stack->top);
}

/* checks whether the stack is empty */
int FStackIsEmpty(f_stack_t *stack)
{
	assert(stack);

	return (!(stack->top));
}
