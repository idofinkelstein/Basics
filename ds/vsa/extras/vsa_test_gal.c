/*******************************************************************
* File Name: vsa_test.c						
* Name: Gal S						           
* Date: 06.07.2020						   
* Reviewed by: Guy Chen       		   
* Topic: system programing							   
********************************************************************/

#include <stdio.h>	/* printf */
#include <stddef.h>	/* size_t */
#include <stdlib.h> /* malloc */

#include "vsa.h"

static void TestBiggestFreeBlock();
static void TestCase1();
static void TestCase2();

int main()
{
/* unit testing to the new API's */	

	TestBiggestFreeBlock();

/* test cases to verfy all minor functions and possible scenarios */

	TestCase1();
	TestCase2();

	return (0);
}

static void TestBiggestFreeBlock()
{
	size_t pool1_size = 500;
	size_t block_size1 = 27;
	vsa_t *vsa1 = NULL;

	void *pool1 = malloc( pool1_size );
	vsa1 = VSAInit(pool1, pool1_size);

	printf("number of bytes in the biggest block is %ld\n", 
			VSABiggestFreeBlock(vsa1));

	VSAAlloc(vsa1, block_size1);
	VSAAlloc(vsa1, block_size1);

	printf("number of bytes in the biggest block after 2 allocs of total %ld is\
 %ld\n",block_size1 *2, VSABiggestFreeBlock(vsa1));
	
	free(pool1);

	printf("\n--------------- TestBiggestFreeBlock ---------------\n\n");
}

/* intits 2 pools and check for free bytes left, than alloc 3 from both of
 them and check for biggest block , free 2 and check for the biggest blocks */
static void TestCase1()
{
	size_t pool1_size = 700;
	size_t block_size1 = 27;	
	size_t pool2_size = 1000;
	size_t block_size2 = 35;

	vsa_t *vsa1 = NULL;
	vsa_t *vsa2 = NULL;

	void *a_ptr1 = NULL;
	void *b_ptr1 = NULL;
	void *a_ptr2 = NULL;
	void *b_ptr2 = NULL;

	void *pool1 = malloc( pool1_size );
	void *pool2 = malloc( pool2_size );

	vsa1 = VSAInit(pool1, pool1_size);
	vsa2 = VSAInit(pool2, pool2_size);
   
	printf("number of bytes in the biggest block of first pool is %ld\n", 
			VSABiggestFreeBlock(vsa1));
	printf("number of bytes in the biggest block of second pool is %ld\n", 
			VSABiggestFreeBlock(vsa2));

	a_ptr1 = VSAAlloc(vsa1, block_size1);
	b_ptr1 = VSAAlloc(vsa2, block_size2);
	a_ptr2 = VSAAlloc(vsa1, block_size2);
	b_ptr2 = VSAAlloc(vsa2, block_size1);
	VSAAlloc(vsa1, block_size1);
	VSAAlloc(vsa2, block_size2);

	printf("number of bytes in the biggest block of first pool after allocs is\
 %ld\n", VSABiggestFreeBlock(vsa1));
	printf("number of bytes in the biggest block of first pool after allocs is\
 %ld\n", VSABiggestFreeBlock(vsa2));

	VSAFree(a_ptr1);
    VSAFree(b_ptr1);
  	VSAFree(a_ptr2);
    VSAFree(b_ptr2);

	printf("number of bytes in the biggest block of first pool after free is\
 %ld\n", VSABiggestFreeBlock(vsa1));
	printf("number of bytes in the biggest block of first pool after free is\
 %ld\n", VSABiggestFreeBlock(vsa2));
  
    free(pool1);
    free(pool2);

	printf("\n---------------end of test case 1---------------\n\n");
}

/* intits 1 pool and than alloc 3 and write to each pointer. free the second
alloc and check again. alloc last time and check agin */
static void TestCase2()
{
	vsa_t *vsa1 = NULL;
	size_t pool1_size = 700;
	size_t block_size1 = 150;	
	size_t i = 0;

	void *a_ptr1 = NULL;
	void *a_ptr2 = NULL;
	void *a_ptr3 = NULL;
	void *a_ptr4 = NULL;

	char *b_ptr1 = NULL;
	char *b_ptr2 = NULL;
	char *b_ptr3 = NULL;

	void *pool1 = malloc( pool1_size );
	vsa1 = VSAInit(pool1, pool1_size);

	a_ptr1 = VSAAlloc(vsa1, block_size1);
	a_ptr2 = VSAAlloc(vsa1, block_size1);
	a_ptr3 = VSAAlloc(vsa1, block_size1);

	b_ptr1 = a_ptr1;
	b_ptr2 = a_ptr2;
	b_ptr3 = a_ptr3;

	for(i=0; i < 25 ; ++i)
	{
		*b_ptr1 = 'a';
		++b_ptr1;
	}
	*b_ptr1 = '\0';	
	
	for(i=0; i < 25 ; ++i)
	{
		*b_ptr2 = 'b';
		++b_ptr2;
	}
	*b_ptr2 = '\0';	

	for(i=0; i < 25 ; ++i)
	{
		*b_ptr3 = 'c';
		++b_ptr3;
	}
	*b_ptr3 = '\0';

	printf("First all strings: \n%s\n",(char *)a_ptr1);
	printf("\n%s\n",(char *)a_ptr2);
	printf("\n%s\n\n",(char *)a_ptr3);

	printf("block1 address: %p\n", a_ptr1);
	printf("block2 address: %p\n", a_ptr2);
	printf("block3 address: %p\n", a_ptr3);


	if (NULL != a_ptr2)
	{	
		VSAFree(a_ptr2);
	}
	a_ptr4 = VSAAlloc(vsa1, block_size1);
	
	printf("After free block2 and alloc again the address is: %p\n", a_ptr4);

	printf("number of bytes in the biggest block of first pool after allocs is\
 %ld\n", VSABiggestFreeBlock(vsa1));

	if (NULL != a_ptr1)
	{
		VSAFree(a_ptr1);
	}

	if (NULL != a_ptr4)
	{
		VSAFree(a_ptr4);
	}

	printf("number of bytes in the biggest block of first pool after free is\
 %ld\n", VSABiggestFreeBlock(vsa1));

	free(pool1);

	printf("\n---------------end of test case 2---------------\n\n");
}
