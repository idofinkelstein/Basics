/**********************
File name: c_stack.c
Author: Ido Finkelstein
Reviewer: Ori Barak
Date: 29/7/2020
***********************/

#include <stdlib.h> /* malloc, free */
#include <assert.h>

#include "c_stack.h"

#define ERROR 1
#define SUCCESS 0

struct stack
{
	size_t top;
	size_t capacity;
	char *head;
};

/* creates a new stack */
c_stack_t* CStackCreate(size_t capacity)
{
	c_stack_t *stack_ptr = (c_stack_t *)malloc(sizeof(c_stack_t));

	if (!stack_ptr)
	{
		return (NULL);
	}

	stack_ptr->capacity = capacity;
	stack_ptr->head = (char *)malloc(sizeof(char) * capacity);

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
void CStackDestroy(c_stack_t *stack)
{
	assert(stack);

	free(stack->head);
	stack->head = NULL;
	free(stack);
	stack = NULL;
}

/* pushes a new element to the top of the stack */
int CStackPush(c_stack_t *stack, char element)
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
void CStackPop(c_stack_t *stack)
{
	assert(stack);

	if (!CStackIsEmpty(stack))
	{	
		/*stack->head[(stack->top) - 1] = NULL; */
		--(stack->top);
	}
}

/* retrieves the last added element from the stack */
char CStackPeek(c_stack_t *stack)
{
	char element = '0';

	assert(stack);

	if(0 == stack->top)
	{
		return (0);
	}
	
	element = stack->head[(stack->top) - 1];

	return (element);
}

/* returns the current number of the elements at the stack */
size_t CStackSize(c_stack_t *stack)
{
	assert(stack);

	return (stack->top);
}

/* checks whether the stack is empty */
int CStackIsEmpty(c_stack_t *stack)
{
	assert(stack);

	return (!(stack->top));
}
