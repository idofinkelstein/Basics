#include <stdio.h> /* printf */
#include <assert.h>	/* assert */
#include <stdlib.h> /* malloc */

#include "fsa.h"

static void FSARequiredPoolSizeTest(size_t num_of_blocks, size_t block_size);
static void FSAFreeBlocksTest(fsa_t *fsa);

int main(void)
{
	fsa_t *fsa = NULL;
	void *pool=NULL; 	
	void *data1 = NULL; 
	void *data2 = NULL; 
		
	size_t num_of_blocks = 1000;
	size_t block_size = 37;
	
    size_t pool_size = FSARequiredPoolSize(num_of_blocks, block_size);

	printf("\n------ FSARequiredPoolSizeTest test ----\n\n");
		    
    FSARequiredPoolSizeTest(num_of_blocks, block_size);
	pool = calloc( pool_size , sizeof(char));
	
	printf("\n------ init pool: address check ----\n\n");
		    	
	printf("Address of first pool is: %p\n", pool);
	fsa = FSAInit(pool, pool_size, block_size);
	printf("Address of fsa (should be the same) is: %p\n\n", (void*)fsa);
	FSAFreeBlocksTest(fsa);	
		
    data1 = FSAAlloc(fsa);
    data2 = FSAAlloc(fsa);
 	FSAFreeBlocksTest(fsa);	
 	
 	printf("\n------free one blocks address----\n\n");
 			
    FSAFree(data1);
	FSAFreeBlocksTest(fsa);	
	
 	printf("\n------free one blocks address----\n\n");
 			      
    FSAFree(data2);   
	FSAFreeBlocksTest(fsa);	
	
 	printf("\n------ free user pool ----\n\n");		   
    free(pool);

	return (0);
}


static void FSARequiredPoolSizeTest(size_t num_of_blocks, size_t block_size)
{
	printf("The pool size shuld be: %lu\n",
            FSARequiredPoolSize(num_of_blocks, block_size));
}

static void FSAFreeBlocksTest(fsa_t *fsa)
{
	size_t amount_of_free_blocks = 0;	

	amount_of_free_blocks = FSAFreeBlocks(fsa);

	if (amount_of_free_blocks)
	{
		printf("Number of empty blocks: %lu\n", amount_of_free_blocks);
	}
	else
	{
		printf("There is no free block for use\n");
	}
}
