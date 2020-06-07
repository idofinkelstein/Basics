/**********************
Author: Ido Finkelstein
File name: ilrd_stack.c
Reviewer: Shiran Hodeda
***********************/

#include <stdio.h>     /* printf, size_t */
#include <stdlib.h>    /* malloc, free   */
#include <sys/types.h> /* ssize_t 		 */

#define SECCESS 0
#define FAILURE 1

#define EXIT_IF_FAILES(CON, MSG, RET) if(CON){ printf(MSG); return (RET);}

typedef struct stack
{
	void **head;
	ssize_t top;
	size_t capacity;
	size_t size;
}stack_t;


stack_t *StackCreate(size_t capacity)
{
	stack_t *stack = (stack_t*)malloc(sizeof(stack_t));
	EXIT_IF_FAILES(NULL == stack, "malloc failed\n", NULL);

	stack->head = (void**)malloc(sizeof(void*) * capacity);
	EXIT_IF_FAILES(NULL == stack->head, "malloc failed\n", NULL);

	stack->capacity = capacity;
	stack->size = 0;
	stack->top = -1;
	
	return (stack);
}

void StackDestroy(stack_t *stack)
{
	if (NULL != stack)
	{
		free(stack->head);
		free(stack);	
	}	
}

int StackPush(stack_t *stack, void *element)
{
	if (stack->size == stack->capacity)
	{
		printf("Stack is full!\n");		
	
		return FAILURE;
	}

	++stack->top;

	*(stack->head + stack->top) = element;

	++stack->size;

	return SECCESS;
}

void StackPop(stack_t *stack)
{
	if (stack->size > 0) 	
	{
		*stack->head = 0;
		
		--stack->top;

		--stack->size;
	}
}

void *StackPeek(stack_t *stack)
{
	if (-1 == stack->top)
	{	
		printf("stack is empty!\n");

		return (NULL);
	}

	return (*(stack->head + stack->top));
}

size_t StackSize(stack_t *stack)
{
	return(stack->size);
}

int StackIsEmpty(stack_t *stack)
{
	return (stack->size > 0);
}

