/**********************
Author: Ido Finkelstein
File name: fsa.c
Reviewer: Guy Chen
Dat: 8/7/2020
***********************/

#include <assert.h>

#include "fsa.h"

/* Utility function declaration */
static size_t ActualBlockSize(size_t block_size);

static const size_t unalligned_address_mask = sizeof(size_t) - 1;

struct block
{
	void *next;	/* next data block */
};

typedef struct block block_t;

struct fixed_sized_alloc
{
	block_t *head;
	size_t free_blocks;
};

fsa_t *FSAInit(void *mem_pool, size_t pool_size, size_t block_size)
{
	fsa_t *fsa = NULL;
	size_t padding = 0;
	size_t allignment_offset = unalligned_address_mask;
	block_t *block = NULL;	
	size_t num_of_blocks = 0;
	size_t i = 0;
	
	assert(mem_pool);

	/* The complement for the unalligned address */
	padding = !((size_t)mem_pool & unalligned_address_mask) ? 
			  0 											: 
			  sizeof(size_t) - ((size_t)mem_pool & unalligned_address_mask);

	num_of_blocks = (pool_size - sizeof(fsa_t) - allignment_offset) / 
					 ActualBlockSize(block_size);

	fsa = (fsa_t*)((char*)mem_pool + padding);

	fsa->free_blocks = num_of_blocks;

	fsa->head = (block_t*)((char*)fsa + sizeof(fsa_t));

	block = fsa->head;

	/* conects all the blocks */
	for (i = 0; i < num_of_blocks - 1; ++i)
	{	
		block->next = (char*)block + ActualBlockSize(block_size);	
	
		block = block->next;	
	}

	block->next = NULL;

	return (fsa);
}

void *FSAAlloc(fsa_t *fsa)
{
	block_t *temp = fsa->head;
	block_t *ret_node = NULL;

	assert(fsa);

	if (fsa->head != NULL)
	{
		--fsa->free_blocks;

		fsa->head = fsa->head->next;

		temp->next = fsa; /* uses the allocated data pointer to point to
							 struct fsa and than use it again in 
							 FSAFree function */

		ret_node = (block_t*)((char*)temp + sizeof(block_t));

		return (ret_node);
	}

	return (NULL);
}

void FSAFree(void *block)
{
	fsa_t *fsa = NULL;
	block_t *temp = NULL;

	assert(block);
	
	block = ((char*)block - sizeof(block_t)); /* moves the pointer to the
												 actual data */
	temp = block;
	fsa = temp->next;

	++fsa->free_blocks;
	
	temp->next = fsa->head;
	fsa->head = temp;
}

size_t FSAFreeBlocks(fsa_t *fsa)
{
	assert(fsa);

	return (fsa->free_blocks);
}

size_t FSARequiredPoolSize(size_t num_of_blocks, size_t block_size)
{
	size_t pool_size = 0;
	size_t padding = unalligned_address_mask; /* in case the user passes 
												 unalligned pointer to pool */
	block_size = ActualBlockSize(block_size);

	pool_size = block_size * num_of_blocks + sizeof(fsa_t) + padding;

	return (pool_size);
}

static size_t ActualBlockSize(size_t block_size)
{
	while (block_size & unalligned_address_mask)
	{
		++block_size;
	}

	return (block_size + sizeof(block_t));
}
