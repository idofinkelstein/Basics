/*************************
File name: vsa.c
Author: Ido Finkelstein
Reviewer: Gal Shvinkelstein
Date: 11.7.2020
**************************/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

#include "vsa.h"

void TestCase1(void);
void TestCase2(void);

int main()
{
	TestCase1();
	TestCase2();

	return 0;
}

void TestCase1(void)
{
	void *pool = NULL;
	vsa_t *vsa = NULL;
	size_t pool_size = 600;
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *block4 = NULL;
	void *block5 = NULL;
	void *block6 = NULL;

	pool = malloc(pool_size);

	pool = (char*)pool + 5;

	vsa = VSAInit(pool, pool_size);

	puts("\n*** TestCase 1 ***");

	printf("max block available = %ld\n", VSABiggestFreeBlock(vsa));

	block1 = VSAAlloc(vsa, 33);
	block2 = VSAAlloc(vsa, 47);

	printf("max block available = %ld\n", VSABiggestFreeBlock(vsa));

	block3 = VSAAlloc(vsa, 16);

	printf("max block available = %ld\n", VSABiggestFreeBlock(vsa));	

	block4 = VSAAlloc(vsa, 111);
	block5 = VSAAlloc(vsa, 87);
	block6 = VSAAlloc(vsa, 100);
	
	printf("max block available = %ld\n", VSABiggestFreeBlock(vsa));

	if (block6 != NULL)
	{
		VSAFree(block6);
	}

	if (block5 != NULL)
	{
		VSAFree(block5);
	}

	if (block3 != NULL)
	{
		VSAFree(block3);
	}

	if (block4 != NULL)
	{
		VSAFree(block4);
	}

	printf("max block available4 = %ld\n", VSABiggestFreeBlock(vsa));

	block4 = VSAAlloc(vsa, 200);

	printf("max block available4after = %ld\n", VSABiggestFreeBlock(vsa));

	if (block4 != NULL)
	{
		VSAFree(block4);
	}

	if (block2 != NULL)
	{
		VSAFree(block2);
	}

	if (block1 != NULL)
	{	
		VSAFree(block1);
	}

	printf("max block available = %ld\n", VSABiggestFreeBlock(vsa));

	pool = (char*)pool - 5;	

	free(pool); 
}

void TestCase2(void)
{
	void *pool = NULL;
	vsa_t *vsa = NULL;
	size_t pool_size = 1200;
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *block4 = NULL;
	void *block5 = NULL;
	void *block6 = NULL;

	pool = malloc(pool_size);

	pool = (char*)pool + 3;

	vsa = VSAInit(pool, pool_size);

	puts("\n*** TestCase 2 ***");

	printf("max block available = %ld\n", VSABiggestFreeBlock(vsa));

	block1 = VSAAlloc(vsa, 140);
	block2 = VSAAlloc(vsa, 140);
	block3 = VSAAlloc(vsa, 140);
	block4 = VSAAlloc(vsa, 140);
	block5 = VSAAlloc(vsa, 140);

	printf("max block available = %ld\n", VSABiggestFreeBlock(vsa));

	block6 = VSAAlloc(vsa, 140);

	printf("max block available = %ld\n", VSABiggestFreeBlock(vsa));

	VSAFree(block3);
	VSAFree(block5);
	VSAFree(block1);
	VSAFree(block6);
	VSAFree(block2);
	VSAFree(block4);

	printf("max block available after frees them all = %ld\n",
		   VSABiggestFreeBlock(vsa));

	block1 = VSAAlloc(vsa, 900);

	printf("max block available after huge allocation = %ld\n",
		   VSABiggestFreeBlock(vsa));
	
	pool = (char*)pool - 3;	

	free(pool); 
}
