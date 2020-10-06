/*************************************
* 									 *			
* file name - fsa_test.c			 *
* writer - Anna Poryadkov		 	 *
* reviewer - Ori Barak		 		 *
* date - 08.07.2020					 *
* topic - FSA						 *
*									 *
**************************************/

#include <stdio.h> /* printf, size_t */
#include <stdlib.h> /* malloc , free */

#include "fsa.h"

/* -------- Case Test functions Declaration -------- */

static void CaseTest(void);


/* ----------- main ----------- */
int main()
{
	size_t pool_size = 0;
	size_t num_of_blocks = 8;
	size_t block_size = 9;
	fsa_t *test_fsa = NULL;
	void *mem_pool = NULL;
	void *block = NULL;

	printf("\nFSARequiredPoolSizeTest: \n\n");

	pool_size = FSARequiredPoolSize(num_of_blocks, block_size);
	printf ("for block_size %ld and num_of_blocks %ld, the pool_size is %ld\n",
			block_size, num_of_blocks, pool_size);

	mem_pool = (void *) malloc (pool_size);
	if (NULL == mem_pool)  
	{
		return (1);
	}

	printf("\nFSAInit Test: \n\n");

	test_fsa = FSAInit(mem_pool, pool_size, block_size);

	if (NULL == test_fsa)
	{
		printf ("Init pool failed!\n");
	}
	else
	{
		printf ("Init pool Succeeded!\n");
	}
	
	printf("\nFSAFreeBlocks Test: \n\n");

	printf ("number of blocks in the pool: %ld\n",FSAFreeBlocks(test_fsa));

	printf("\nFSAAlloc Test: \n\n");

	block = FSAAlloc(test_fsa);

	printf ("number of blocks in the pool: %ld\n",FSAFreeBlocks(test_fsa));

	printf("address of new block: %p, and address is aligned: %ld "
		   "(if 0 - address is aligned) \n", block, (size_t)block % 8);

	FSAFree(block);

	printf ("number of blocks in the pool: %ld\n",FSAFreeBlocks(test_fsa));

	free(mem_pool);
	mem_pool = NULL;

	CaseTest();

	return(0);
}

/* ----------- Case Test Functions ----------- */

static void CaseTest(void)
{
	size_t pool_size = 0;
	size_t num_of_blocks = 5;
	size_t block_size = 18;
	fsa_t *test_fsa = NULL;
	void *mem_pool = NULL;
	void *mem_pool_unaligned = NULL;
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;
	void *block4 = NULL;

	typedef struct 
	{
		int dr_evil;
		int number_two;

	}data_t;

	data_t goldmember = {0, 0};
	goldmember.dr_evil = 1;

	printf("\nCaseTest: \n\n");

	pool_size = FSARequiredPoolSize(num_of_blocks, block_size);
	printf ("for block_size %ld and num_of_blocks %ld, the pool_size is %ld\n",
			block_size, num_of_blocks, pool_size);

	printf("test for unaligned address:\n");

	mem_pool = (void *) malloc (pool_size);
	if (NULL == mem_pool)  
	{
		return ;
	}

	mem_pool_unaligned = (char *)mem_pool + 2;

	printf("address of mem_pool_unaligned: %p, and address is aligned: %ld "
		   "(if 0 - address is aligned) \n", 
			mem_pool_unaligned, (size_t)mem_pool_unaligned % 8);

	test_fsa = FSAInit(mem_pool_unaligned, pool_size, block_size);

	if (NULL == test_fsa)
	{
		printf ("Init pool failed!\n");
	}
	else
	{
		printf ("Init pool Succeeded!\n");
	}

	printf("address of test fsa: %p, and address is aligned: %ld "
		   "(if 0 - address is aligned) \n",
			(void *)test_fsa, (size_t)test_fsa % 8);

	free(mem_pool);
	mem_pool = NULL;

	mem_pool = (void *) malloc (pool_size);
	if (NULL == mem_pool)  
	{
		return ;
	}

	printf("test if pool size < block size:\n");
	test_fsa = FSAInit(mem_pool, 10, 10);

	if (NULL == test_fsa)
	{
		printf ("Init pool failed!\n");
	}
	else
	{
		printf ("Init pool Succeeded!\n");
	}

	printf("test if pool size > block size:\n");
	test_fsa = FSAInit(mem_pool, pool_size, block_size);

	if (NULL == test_fsa)
	{
		printf ("Init pool failed!\n");
	}
	else
	{
		printf ("Init pool Succeeded!\n");
	}
	
	printf ("number of blocks in the pool: %ld\n",FSAFreeBlocks(test_fsa));

	block1 = FSAAlloc(test_fsa);

	*(long *)block1 = 2;

	printf ("the goldmember struct is: %d, %d\n",
			goldmember.dr_evil, goldmember.number_two);
	
	block2 = FSAAlloc(test_fsa);

	*(data_t *)block2 = goldmember;
	(*(data_t *)block2).number_two = 2; 
	(*(data_t *)block2).dr_evil = 10;

	printf ("the goldmember struct in the block after update is: %d, %d\n",
		   (*(data_t *)block2).dr_evil, (*(data_t *)block2).number_two);

	block3 = FSAAlloc(test_fsa);

	*(int *)block3 = 55;

	printf ("number of blocks in the pool: %ld\n",FSAFreeBlocks(test_fsa));

	FSAFree(block3);
	FSAFree(block2);

	block4 = FSAAlloc(test_fsa);

	*(short *)block4 = 3;

	printf ("the value in block4: %d\n",*(short *)block4);
	
	while (NULL != block1)
	{
		printf ("number of blocks in the pool: %ld\n",FSAFreeBlocks(test_fsa));
		block1 = FSAAlloc(test_fsa);
	}

	free(mem_pool);
	mem_pool = NULL;
}

