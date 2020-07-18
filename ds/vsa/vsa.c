/*************************
File name: vsa.c
Author: Ido Finkelstein
Reviewer: Gal Shvinkelstein
Date: 11.7.2020
**************************/

#include <assert.h>

#include "vsa.h"

typedef struct block block_t;

static const size_t unalligned_address_mask = sizeof(size_t) - 1;
static const size_t word_size = sizeof(size_t);
static const size_t mask = 0x1;

/* Utility function declaration */
size_t ActualBlockSize(size_t block_size);
int BlockIsFree(block_t *block);
size_t BlockActoualCapacity(block_t *block);
int BlockIsLast(block_t *block);

struct variable_sized_alloc
{
	block_t *head;
	size_t pool_size;
};

struct block
{
	block_t *next;	
	size_t capacity; 		/* volume of block */

	/* capacity last bit: 1 - occupied
						  0 - free
	*/
};

vsa_t *VSAInit(void *mem_pool, size_t pool_size)
{
	vsa_t *vsa = NULL;
	size_t padding = 0;
	block_t *block = NULL;
	size_t pool_shift = pool_size; /* for allignment purpose */

	assert(mem_pool);

	padding = !((size_t)mem_pool & unalligned_address_mask) ? 
			  0 											: 
			  sizeof(size_t) - ((size_t)mem_pool & unalligned_address_mask);

	vsa = (vsa_t*)((char*)mem_pool + padding);

	vsa->head = (block_t*)((char*)vsa + sizeof(vsa_t));
	vsa->pool_size = pool_size;

	/* this loop allignes pool size for positioning last block
	   in alligned address */
	while (pool_shift & unalligned_address_mask)
	{
		--pool_shift;
	}

	block = vsa->head;

	block->capacity = pool_shift - 2 * sizeof(block_t) -
							 sizeof(vsa_t) - word_size;

	block->next = (block_t*)((char*)vsa  + pool_shift -
				   word_size - sizeof(block_t));

	block = block->next;
	block->next = NULL;
	
	block->capacity = 0;

	return (vsa);	
}

void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
	block_t *curr = vsa->head;
	block_t *prev = curr;
	block_t *new_block = NULL;
	block_t *ret_block = NULL;
	block_t *next = NULL;
	size_t actual_block_size = ActualBlockSize(block_size);
	size_t capacity_remained = 0;
	
	assert(vsa);
	
	/* this loop increments curr & defragments adjacent free blocks until
	   it meets suitable block for allocation */
	while (BlockActoualCapacity(prev) < actual_block_size && !BlockIsLast(curr))
	{
		prev = curr; /* saves the last block for evaluation in while
						loop condition */
		
		next = curr->next;

		/* this loop does the task of defragmenting adjacent free blocks */
		while (BlockIsFree(curr) && BlockIsFree(next) && !BlockIsLast(next))
		{
			curr->capacity += BlockActoualCapacity(next) + sizeof(block_t);
			
			curr->next = next->next;
			next = next->next;
		}

		curr = next;
	}

	curr = prev;

	/* no suitable block found */
	if (BlockIsLast(curr) || 
		BlockActoualCapacity(curr) < actual_block_size || 
		!BlockIsFree(curr))
	{
		return (NULL);
	}

	capacity_remained = BlockActoualCapacity(curr) - actual_block_size;

	/* if remain_capacity is smaller then this size there is no need for new
	   block */
	if (capacity_remained < sizeof(block_t) * 2)
	{
		ret_block = (block_t*)((char*)curr + sizeof(block_t));
		curr->capacity += 0x1;

		return (ret_block);
	}

	new_block = (block_t*)((char*)curr + actual_block_size);

	new_block->next = curr->next;
	curr->next = new_block;

	new_block->capacity = capacity_remained;

	ret_block = (block_t*)((char*)curr + sizeof(block_t));

	curr->capacity = actual_block_size - sizeof(block_t) + 0x1;
		
	return (ret_block);	
}

void VSAFree(void *block)
{
	block_t *curr = (block_t*)((char*)block - sizeof(block_t));	

	assert(block);

	curr->capacity -= 0x1;	
}

size_t VSABiggestFreeBlock(vsa_t *vsa)
{
	block_t *curr = vsa->head;
	size_t max_block_available = curr->capacity * BlockIsFree(curr);

	/* this block size can't be achieved so basicly this
	   function call defragments all available blocks in the pool */
	VSAAlloc(vsa, vsa->pool_size);

	assert(vsa);

	while (curr != NULL)
	{
		if (curr->capacity > max_block_available && BlockIsFree(curr))
		{
			max_block_available = curr->capacity;
		}
		
		curr = curr->next;
	}

	return(max_block_available);
}

size_t ActualBlockSize(size_t block_size)
{
	while (block_size & unalligned_address_mask)
	{
		++block_size;
	}

	return (block_size + sizeof(block_t));
}

int BlockIsFree(block_t *block)
{
	return !(block->capacity & mask);
}

size_t BlockActoualCapacity(block_t *block)
{
	return (block->capacity & ~1);
}

int BlockIsLast(block_t *block)
{
	return (block->next == NULL);
}
