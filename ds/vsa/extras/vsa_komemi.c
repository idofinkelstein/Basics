#include <stddef.h>
#include <stdio.h>  /* printf */
#include "vsa.h"

typedef struct metadata metadata_t;

struct variable_sized_alloc
{
	metadata_t *first_block;
};

struct metadata
{
	/* first bit of size represent : 0 - free block
			     					 1 - occupied block
	   second bit of size represent: 0 - any block but last     					 
			     					 1 - last block 	    */		 
	size_t size;	
};

static metadata_t *FindAndMergeFreeBlock(metadata_t * curr_block, size_t block_size);
static metadata_t *AssignFreeBlock(metadata_t * curr_block, size_t block_size);
static int last_block = 2;

vsa_t *VSAInit(void *mem_pool, size_t pool_size)
{
	vsa_t *vsa = NULL;
	metadata_t *new_block = NULL;
	
	/* align pool and update size*/
	while((size_t)mem_pool % sizeof(size_t) != 0)
	{
		mem_pool = (char *)mem_pool + 1;
		--pool_size;
	}
	
	/* make pool_size align to 8 */
	while (pool_size % 8 != 0)
	{
		--pool_size;
	}
	
	if(pool_size > sizeof(vsa_t))
	{
		/* init first block */
		new_block = (metadata_t *)((char *)mem_pool + sizeof(vsa_t));
		
		/* represented as a free and last block (pool_size aligned to 8) */
		new_block->size = pool_size + last_block;
		
		/* init vsa */
		vsa = (vsa_t *)mem_pool;
		vsa->first_block = new_block;	
			
	}	
	/* returns NULL in case of failure */
	return (vsa);
}


void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
	metadata_t *curr_block = NULL;

	curr_block = vsa->first_block;
	
	block_size += sizeof(metadata_t);
	
	/* make block_size align to 8 */
	while (block_size % 8 != 0)
	{
		++block_size;
	}
	
	curr_block = FindAndMergeFreeBlock(curr_block, block_size);
	
	/* if last block && (occupied \\ not enough free space) */
	if (curr_block->size & 2 && 
	   ((curr_block->size & 1) || (block_size > (curr_block->size >> 2) << 2)))
	{
		return (NULL);
	}
	
	/* if there is suitable free block available in vsa */
	else
	{
		curr_block = AssignFreeBlock(curr_block, block_size);
				
		return ((char *)curr_block + sizeof(metadata_t));	
	}	
}

void VSAFree(void *block)
{
	metadata_t *block_to_free = NULL;	

	block_to_free = (metadata_t *)((char *)block - sizeof(metadata_t));
	
	block_to_free->size -= 1; 
}
/*----------------------------------------------------------------------------*/

size_t VSABiggestFreeBlock(vsa_t *vsa)
{
	metadata_t *curr_block = NULL;
	metadata_t *last_block_of_biggest = NULL;
	size_t biggest_free_block = 0;
	size_t counter = 0;
	curr_block = vsa->first_block;
	
	/* while not last */
	while(!(curr_block->size & 2))
	{	
		/* occupied */
		if (curr_block->size & 1)
		{	
			counter = 0;
			last_block_of_biggest = NULL;
		}
		/* free */
		else 
		{
			counter += ((curr_block->size >> 2) << 2);		
		}
		
		/*update biggest_free_block */
		if (counter > biggest_free_block)
		{
			biggest_free_block = counter;
			last_block_of_biggest = curr_block;
		}
		/* move to next block */
		curr_block = (metadata_t *)
				     ((char *)curr_block + ((curr_block->size >> 2) << 2));
	}
	
	
	/* if end is free */ 
	if(!(curr_block->size & 1))
	{
		/*if biggest_free_block adjecnt to end */
		if( (char *)last_block_of_biggest + last_block_of_biggest->size == (char *)curr_block)
		{
			biggest_free_block += ((curr_block->size >> 2) << 2);
		}
		/* else if end bigger than biggest_free_block */
		else if ( ((curr_block->size >> 2) << 2) > biggest_free_block)
		{
			biggest_free_block = (curr_block->size >> 2) << 2;
		}
	}	


	return (biggest_free_block);
}

/*----------------------------------------------------------------------------*/

static metadata_t *FindAndMergeFreeBlock(metadata_t * curr_block, size_t block_size)
{
	metadata_t *next_block = NULL;	
	
	/* while size isnt big enough \\ already occupied block && not last block */
	while(((block_size > (curr_block->size >> 2) << 2) || curr_block->size & 1)	
			&& !(curr_block->size & 2)  )    
			
	{
		next_block = (metadata_t *)
					((char *)curr_block + ((curr_block->size >> 2) << 2));
					
		/*if curr occupied */
		if(curr_block->size & 1)
		{
			curr_block = next_block;
		}
		/* if curr is free but not big enough */ 
		else if (block_size > (curr_block->size >> 2) << 2)
		{
			/*if next block is free */
			if(!(next_block->size & 1))
			{	
				/* unite 2 free blocks together*/
				curr_block->size  += next_block->size;
			}
		}	
	}
	
	return (curr_block);
}

/*----------------------------------------------------------------------------*/

static metadata_t *AssignFreeBlock(metadata_t *curr_block, size_t block_size)
{
	metadata_t *next_block = NULL;		
	
	/* if no more space after(both for last and middle blocks) */	
	if ( (curr_block->size >> 2) << 2 == block_size)
	{	
		/* update occupied */
		curr_block->size = curr_block->size + 1; 
	}
	else
	{
		/* create next block after*/
		next_block = (metadata_t *)((char *)curr_block + block_size);
		/* next also free last as curr */
		next_block->size = curr_block->size - block_size;
		/* update curr to occupied */
		curr_block->size = block_size + 1; 
	}
	
	return(curr_block);
}

