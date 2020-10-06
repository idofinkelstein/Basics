#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include "vsa.h"

void TestVSAInit();
void TestVSAAllocAndFree();
void TestVSABiggestFreeBlock();

int main(void)
{
	TestVSAInit();
	TestVSAAllocAndFree();
	return(0);
}

void TestVSAInit()
{
	void *my_pool1 = malloc(600);
	size_t pool_size = 600;
	vsa_t * pool_handle = NULL;

	pool_handle = VSAInit((char*)my_pool1 + 1, pool_size);
	printf("original pool address: %p\n", (void*)((char*)my_pool1 + 1));
	printf("aligned pool address: %p\n", (void*)pool_handle);
	
	free(my_pool1);
}

void TestVSAAllocAndFree()
{
	void *my_pool1 = malloc(600);
	size_t pool_size = 600;
	vsa_t * pool_handle;
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;

	pool_handle = VSAInit(my_pool1, pool_size);
	printf("biggest free block after init: %ld\n", VSABiggestFreeBlock(pool_handle));
	block1 = VSAAlloc(pool_handle, 400);
	printf("block1 address: %p\n", block1);
	printf("biggest free block: %ld\n", VSABiggestFreeBlock(pool_handle));

	VSAFree(block1);
	printf("biggest free block after block1 was freed: %ld\n", VSABiggestFreeBlock(pool_handle));

	block2 = VSAAlloc(pool_handle, 50);
	printf("block2 address: %p\n", block2);
	printf("biggest free block: %ld\n", VSABiggestFreeBlock(pool_handle));
	block3 = VSAAlloc(pool_handle, 25);
	printf("block3 address: %p\n", block3);
	printf("biggest free block: %ld\n", VSABiggestFreeBlock(pool_handle));

	block1 = VSAAlloc(pool_handle, 200);
	printf("block1 address after free and alloc bigger space: %p\n", block1);
	
	while(block1 != NULL)
	{
		block1 = VSAAlloc(pool_handle, 30);
	}
	printf("biggest free block after many allocations: %ld\n", VSABiggestFreeBlock(pool_handle));


	if (block3 != NULL) /* ido */
	{
		VSAFree(block3);
	}

	printf("biggest free block after block3 was freed: %ld\n", VSABiggestFreeBlock(pool_handle));
	block1 = VSAAlloc(pool_handle, 30);
	printf("biggest free block after block1 was allocated again: %ld\n", VSABiggestFreeBlock(pool_handle));
	free(my_pool1);
}






























