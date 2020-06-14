/**********************
Author: Ido Finkelstein
File name: ilrd_stack_test.c
Reviewer: Shiran Hodeda
***********************/

#include <stdio.h>
#include "ilrd_stack.h"

#define STACK_SIZE 100

void StackPeekTest(stack_t *stk);

int main()
{
	char str[] = "hello";
	char str2[] = "world!";


	stack_t *stk = StackCreate(STACK_SIZE);

	printf("IsStackEmpty = %d\n", StackIsEmpty(stk));

	StackPeekTest(stk);
	StackPush(stk, str);
	StackPeekTest(stk);
	StackPush(stk, str2);
	StackPeekTest(stk);
	printf("%ld\n", StackSize(stk));

	printf("IsStackEmpty = %d\n", StackIsEmpty(stk));

	/* popping more than size to check for errors */
	StackPop(stk);
	StackPop(stk);
	StackPop(stk);
	StackPop(stk);

	printf("IsStackEmpty = %d\n", StackIsEmpty(stk));

	printf("%ld\n", StackSize(stk));
	StackPeekTest(stk);
	StackPush(stk, str);
	StackPeekTest(stk);
	
	StackDestroy(stk);
	stk = NULL;

	stk = StackCreate(2);

	printf("IsStackEmpty = %d\n", StackIsEmpty(stk));

	/* pushing more than size to check for errors */
	StackPeekTest(stk);
	StackPush(stk, str);
	StackPeekTest(stk);
	StackPush(stk, str2);
	StackPeekTest(stk);
	printf("%ld\n", StackSize(stk));
	StackPeekTest(stk);
	StackPush(stk, str);
	StackPeekTest(stk);
	StackPush(stk, str2);
	StackPeekTest(stk);
	printf("%ld\n", StackSize(stk));

	StackDestroy(stk);
	stk = NULL;

	return 0;
}

void StackPeekTest(stack_t *stk)
{
	if(NULL != StackPeek(stk))
	{
		printf("%s\n", (char*)StackPeek(stk));
	}
}
