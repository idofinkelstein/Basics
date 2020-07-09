/**********************
Author: Ido Finkelstein
File name: fsa_test.c
Reviewer: Guy Chen
Date: 8/7/2020
***********************/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

#include "fsa.h"

static void TestCase1(void);

int main()
{
	TestCase1();	

	return 0;
}

static void TestCase1(void)
{
	fsa_t *fsa = NULL; 
	void *pool = NULL;

	void *block1 = NULL;
	size_t pool_size = 0;
	void *block2 = NULL;
	void *block3 = NULL;
	void *block4 = NULL;
	void *block5 = NULL;

	printf("%ld\n", pool_size = FSARequiredPoolSize(5, 12));

	pool = malloc(pool_size);

	pool = (fsa_t*)((char*)pool + 3); /* forces an unalligned address */

	fsa = FSAInit(pool, pool_size, 12);
	block1 = FSAAlloc(fsa);
	printf("%ld\n", FSAFreeBlocks(fsa));

	
	printf("block1 address = %p\n", (void*)block1);
	block2 = FSAAlloc(fsa);
	printf("block2 address = %p\n", (void*)block2);
	block3 = FSAAlloc(fsa);
	printf("block3 address = %p\n", (void*)block3);
	block4 = FSAAlloc(fsa);
	printf("%ld\n", FSAFreeBlocks(fsa));
	printf("block4 address = %p\n", (void*)block4);
	block5 = FSAAlloc(fsa);
	printf("block5 address = %p\n", (void*)block5);

	FSAFree(block1);
	FSAFree(block3);
	FSAFree(block4);
	FSAFree(block5);

	block4 = FSAAlloc(fsa);
	block1 = FSAAlloc(fsa);
	block3 = FSAAlloc(fsa);

	printf("block1 address = %p\n", (void*)block1);
	printf("block3 address = %p\n", (void*)block3);
	printf("block4 address = %p\n", (void*)block4);

	FSAFree(block1);
	FSAFree(block3);
	FSAFree(block4);
	
	block4 = FSAAlloc(fsa);
	block1 = FSAAlloc(fsa);
	block3 = FSAAlloc(fsa);

	FSAFree(block1);
	FSAFree(block3);
	FSAFree(block4);
	FSAFree(block2);

	
	block1 = FSAAlloc(fsa);
	block2 = FSAAlloc(fsa);
	block3 = FSAAlloc(fsa);
	block4 = FSAAlloc(fsa);
	block5 = FSAAlloc(fsa);

	printf("block1 address = %p\n", (void*)block1);
	printf("block2 address = %p\n", (void*)block2);
	printf("block3 address = %p\n", (void*)block3);
	printf("block4 address = %p\n", (void*)block4);
	printf("block5 address = %p\n", (void*)block5);

	FSAFree(block1);
	FSAFree(block2);
	FSAFree(block3);
	FSAFree(block4);
	FSAFree(block5);
	
	block1 = FSAAlloc(fsa);
	block2 = FSAAlloc(fsa);
	block3 = FSAAlloc(fsa);
	block4 = FSAAlloc(fsa);
	block5 = FSAAlloc(fsa);

	printf("block1 address = %p\n", (void*)block1);
	printf("block2 address = %p\n", (void*)block2);
	printf("block3 address = %p\n", (void*)block3);
	printf("block4 address = %p\n", (void*)block4);
	printf("block5 address = %p\n", (void*)block5);
	
	printf("%ld\n", FSAFreeBlocks(fsa));

	pool = (fsa_t*)((char*)pool - 3);

	free(pool);
}
