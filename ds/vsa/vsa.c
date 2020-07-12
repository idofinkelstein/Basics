/*************************
File name: vsa.c
Author: Ido Finkelstein
Reviewer: Gal Shvinkelstein
Date: 11.7.2020
**************************/

#include <assert.h>

#include "vsa.h"

static const size_t unalligned_address_mask = sizeof(size_t) - 1;
static const size_t word_size = sizeof(size_t);

/* Utility function declaration */
size_t ActualBlockSize(size_t block_size);

typedef struct block block_t;

struct variable_sized_alloc
{
	block_t *head;
	size_t pool_size;
};

struct block
{
	block_t *next;
	size_t available_bytes; /* how many bytes available */
	size_t capacity; 		/* volume of block */
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
	block->available_bytes = pool_size - 2 * sizeof(block_t) - sizeof(vsa_t) - padding;
	block->capacity = block->available_bytes;
	block->next = (block_t*)((char*)vsa  + pool_shift - word_size - sizeof(block_t));

	block = block->next;
	block->next = NULL;
	block->available_bytes = 0;
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
	while (prev->available_bytes < actual_block_size && curr->next != NULL )
	{
		prev = curr; /* saves the last block for evaluation in while
						loop condition */
		
		next = curr->next;

		/* this loop does the task of defragmenting adjacent free blocks */
		while (curr->available_bytes == curr->capacity && next->next != NULL)
		{
			curr->available_bytes += next->capacity + sizeof(block_t);
			curr->capacity = curr->available_bytes;
			curr->next = next->next;
			next = next->next;
		}

		curr = next;
	}

	curr = prev;

	/* no suitable block found */
	if (NULL == curr->next || curr->available_bytes < actual_block_size)
	{
		return (NULL);
	}

	capacity_remained = curr->capacity - actual_block_size;

	curr->available_bytes = 0;
	
	/* if remain_capacity is smaller then this size there is no need for new
	   block */
	if (capacity_remained < sizeof(block_t) * 2)
	{
		ret_block = (block_t*)((char*)curr + sizeof(block_t));

		return (ret_block);
	}

	new_block = (block_t*)((char*)curr + actual_block_size);
	new_block->next = curr->next;
	curr->next = new_block;

	new_block->capacity = capacity_remained;
	new_block->available_bytes = new_block->capacity;

	ret_block = (block_t*)((char*)curr + sizeof(block_t));

	curr->capacity = actual_block_size - sizeof(block_t);
	
	return (ret_block);	
}

void VSAFree(void *block)
{
	block_t *curr = (block_t*)((char*)block - sizeof(block_t));
	

	assert(block);

	curr->available_bytes = curr->capacity;
	
}

size_t VSABiggestFreeBlock(vsa_t *vsa)
{
	block_t *curr = vsa->head;
	size_t max_block_available = curr->available_bytes;
	
	/* this block size can't be achieved so basicly this
	   function call defragments all available blocks in the pool */
	VSAAlloc(vsa, vsa->pool_size);

	assert(vsa);

	while (curr != NULL)
	{
		if (curr->available_bytes > max_block_available)
		{
			max_block_available = curr->available_bytes;
		}
		
		curr = curr->next;
	}

	/* taking into account the block header overhead */
	return(max_block_available - sizeof(block_t));
}

size_t ActualBlockSize(size_t block_size)
{
	while (block_size & unalligned_address_mask)
	{
		++block_size;
	}

	return (block_size + sizeof(block_t));
}

