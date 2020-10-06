/* File Name   : stack.c
 * Developer   : Janna Torbilo
 * Reviewer    : Gal Shvinkelstein
 * Review Date : 7.6.20
 */

#include <stdlib.h> /* malloc 	   	 */
#include "stack.h"	/* *      	     */

#define ERROR 1
#define SUCCESS 0

struct stack
{
	size_t top;
	size_t capacity;
	void **head;
};

/* creates a new stack */
stack_t* StackCreate(size_t capacity)
{
	stack_t *stack_ptr = (stack_t *)malloc(sizeof(stack_t));

	if (!stack_ptr)
	{
		return (NULL);
	}

	stack_ptr->capacity = capacity;
	stack_ptr->head = (void **)malloc(sizeof(void *) * capacity);

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
void StackDestroy(stack_t *stack)
{
	free(stack->head);
	stack->head = NULL;
	free(stack);
	stack = NULL;
}

/* pushes a new element to the top of the stack */
int StackPush(stack_t *stack, void *element)
{
	if(stack->top == stack->capacity )	
	{	
		return (ERROR);
	}
	
	stack->head[stack->top] = element; 
	++(stack->top);

	return (SUCCESS);
}

/* removes the last added element from the stack */
void StackPop(stack_t *stack)
{
	if (!StackIsEmpty(stack))
	{	
		stack->head[(stack->top) - 1] = NULL; 
		--(stack->top);
	}
}

/* retrieves the last added element from the stack */
void *StackPeek(stack_t *stack)
{
	void *element = NULL;

	if(0 == stack->top)
	{
		return (NULL);
	}
	
	element = stack->head[(stack->top) - 1];

	return (element);
}

/* returns the current number of the elements at the stack */
size_t StackSize(stack_t *stack)
{
	return (stack->top);
}

/* checks whether the stack is empty */
int StackIsEmpty(stack_t *stack)
{
	return (!(stack->top));
}
