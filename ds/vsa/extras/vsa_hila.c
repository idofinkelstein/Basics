
#include <stddef.h> /* size_t */
#include <assert.h>
#include "vsa.h"

typedef struct node node_t;

struct node
{
    vsa_t *vsa;
	node_t *next;
	size_t block_size; 
	int is_free;        /* 1 means free, 0 means allocated */
};

struct variable_sized_alloc
{
	node_t *end_of_free_space;
	node_t *head_of_free_space;
	size_t biggest_block_size;
};


/*---------------------------------------------------------------------------*/

vsa_t *VSAInit(void *mem_pool, size_t pool_size)
{
	size_t padding = 0;	
	node_t *curr_block = NULL;
	vsa_t *vsa = NULL;

	assert(mem_pool);

	/*initial padding for entire pool */
	padding = ((size_t)mem_pool % sizeof(size_t) == 0) ? 0 : 
				(sizeof(size_t) - (size_t)mem_pool % sizeof(size_t));
	vsa = (vsa_t*)((char*)mem_pool + padding);
	
	/* vsa handle initialized */
	vsa->head_of_free_space = (node_t *)((char*)vsa + sizeof(vsa_t));
	vsa->biggest_block_size = pool_size - padding - sizeof(vsa_t) - 2 * sizeof(node_t);

	if(pool_size <= (sizeof(vsa_t) + 2 * sizeof(node_t) + padding))
	{
		return (NULL);
	}
	/* head of space initialized */
	curr_block = vsa->head_of_free_space;
	curr_block->vsa = vsa;
	curr_block->block_size = vsa->biggest_block_size;
	curr_block->is_free = 1;
	curr_block->next = (node_t*)((char*)curr_block + sizeof(node_t) + vsa->biggest_block_size - 8);

	/* end of space initialized */
	curr_block = curr_block->next;
	curr_block->vsa = vsa;
	curr_block->is_free = 0;
	curr_block->block_size = 0;
	curr_block->next = NULL;
	vsa->end_of_free_space = curr_block;

	return (vsa);

}

/*---------------------------------------------------------------------------*/

void VSAFree(void *block)
{
	node_t *curr_block = NULL;
	vsa_t *vsa = NULL;

	assert(block);

	curr_block = (node_t*)((char*)block - sizeof(node_t));
	curr_block->is_free = 1;
	vsa = curr_block->vsa;

	/* making 2 free blocks into 1 big block */
	if(curr_block->next->is_free)
	{
		curr_block->block_size += sizeof(node_t) + curr_block->next->block_size;
		curr_block->next = curr_block->next->next;
	}

	/* update biggest block in vsa */
	VSABiggestFreeBlock(vsa);
}

/*---------------------------------------------------------------------------*/

void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
	node_t *curr_block = NULL;
	node_t *temp = NULL;
	void *return_value = NULL;
	size_t original_block_size = 0;

	/* adding padding to block size */
	block_size = block_size + ((block_size % sizeof(size_t) == 0) ? 0 : (sizeof(size_t) - block_size % sizeof(size_t)));

	if(block_size > vsa->biggest_block_size)
	{
		return (NULL);
	}
	
	curr_block = vsa->head_of_free_space;
	while(	curr_block->block_size < block_size ||
			!curr_block->is_free)
	{
		curr_block = curr_block->next;
	}

	/* when we reach here, then we found our block to allocate */

	/* in case this block is bigger than requested space */
	if(block_size < curr_block->block_size)
	{
		original_block_size = curr_block->block_size;
		return_value = (void*)((char*)curr_block + sizeof(node_t));
		curr_block->block_size = block_size;
		curr_block->is_free = 0;	
			if ((node_t*)((char*)return_value + block_size + sizeof(node_t)) < curr_block->next)			
			{
				temp = curr_block;				
				curr_block = (node_t*)((char*)return_value + block_size);
				curr_block->block_size = original_block_size - sizeof(node_t) - block_size;
				curr_block->vsa = vsa;	
				curr_block->next = temp->next;
				curr_block->is_free = 1;
				temp->next = curr_block;
			}
			else
			{
				temp = curr_block + sizeof(node_t) + block_size;
				temp->block_size = (curr_block->next - temp) - sizeof(node_t);
				temp->vsa = vsa;
				temp->is_free = 1;
				temp->next = curr_block->next;
				curr_block->next = temp;
			}
	}
	else
	{
		return_value = (void*)((char*)curr_block + sizeof(node_t));
		curr_block->is_free = 0;
	}
	VSABiggestFreeBlock(vsa);

	return (return_value);
}

/*---------------------------------------------------------------------------*/

size_t VSABiggestFreeBlock(vsa_t *vsa)
{
	node_t *curr_block = NULL;
	size_t max_block = 0;

	assert(vsa);

	curr_block = vsa->head_of_free_space;
	while(curr_block != vsa->end_of_free_space)
	{
		if((curr_block->block_size > max_block) && (curr_block->is_free))
		{
			max_block = curr_block->block_size;
		}
		curr_block = curr_block->next;
	}
	vsa->biggest_block_size = max_block;
	return (vsa->biggest_block_size);
}

/*---------------------------------------------------------------------------*/

