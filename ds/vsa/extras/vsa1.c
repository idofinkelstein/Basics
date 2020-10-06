#include <stdio.h>
#include <assert.h>

#include "vsa.h"

static const size_t unalligned_address_mask = sizeof(size_t) - 1;
static const size_t word_size = sizeof(size_t);

size_t ActualBlockSize(size_t block_size);

typedef struct block block_t;

struct variable_sized_alloc
{
	block_t *head;


};

struct block
{
	block_t *next;
	vsa_t *vsa;
	size_t available_bytes;
	size_t capacity;
	
};


vsa_t *VSAInit(void *mem_pool, size_t pool_size)
{
	vsa_t *vsa = NULL;
	size_t padding = 0;
	block_t *block = NULL;
	size_t pool_shift = pool_size;

	assert(mem_pool);

	padding = !((size_t)mem_pool & unalligned_address_mask) ? 
			  0 											: 
			  sizeof(size_t) - ((size_t)mem_pool & unalligned_address_mask);

	vsa = (vsa_t*)((char*)mem_pool + padding);

	vsa->head = (block_t*)((char*)vsa + sizeof(vsa_t));

	printf("vsa address = %p\n", (void*)vsa);
	printf("vsa->head address = %p\n", (void*)vsa->head);
	printf("padding = %ld\n", padding);

	while (pool_shift & unalligned_address_mask)
	{
		--pool_shift;
	}

	block = vsa->head;
	block->available_bytes = pool_size - 2 * sizeof(block_t) - sizeof(vsa_t) - padding;
	block->capacity = block->available_bytes;
	block->next = (block_t*)((char*)vsa  + pool_shift - word_size - sizeof(block_t));

	printf("block->available_bytes = %ld\n", block->available_bytes);

	printf("first block address = %p\n", (void*)block);
	printf("first block->next address = %p\n", (void*)block->next); 


	block = block->next;
	block->next = NULL;
	block->available_bytes = 0;
	block->capacity = 0;



	printf("last block address = %p\n", (void*)block);
	printf("last block->next address = %p\n", (void*)block->next);
		
	return (vsa);
	
}

void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
	block_t *curr = vsa->head;
	block_t *new_block = NULL;
	block_t *ret_block = NULL;
	size_t actual_block_size = ActualBlockSize(block_size);
	size_t remain_capacity = curr->capacity - actual_block_size;
	

	while (curr->available_bytes < actual_block_size && curr->next != NULL )
	{
		curr = curr->next;
	}

	if (NULL == curr->next)
	{
		printf("no free blocks available\n");

		return (NULL);
	}

	printf("requested_block_size = %ld\n", block_size);
	printf("actual_block_size = %ld\n", actual_block_size);
	printf("curr address = %p\n", (void*)curr);

	curr->available_bytes = 0;
	
	if (remain_capacity < sizeof(block_t) * 2)
	{
		
		ret_block = (block_t*)((char*)curr + sizeof(block_t));

		return (ret_block);
	}
	new_block = (block_t*)((char*)curr + actual_block_size);
	new_block->next = curr->next;
	curr->next = new_block;

	new_block->capacity = curr->capacity - actual_block_size;
	new_block->available_bytes = new_block->capacity;

	

	ret_block = (block_t*)((char*)curr + sizeof(block_t));

	printf("curr->next address = %p\n", (void*)curr->next);

	printf("new->capacity = %ld\n", new_block->capacity);
	printf("data address = %p\n", (void*)curr);
	curr->capacity = actual_block_size - sizeof(block_t);
	printf("curr->capacity = %ld\n", curr->capacity);


	
	return (ret_block);	
}

void VSAFree(void *block)
{
	block_t *first = (block_t*)((char*)block - sizeof(block_t));
	block_t *next = first->next;

	first->available_bytes = first->capacity;

	if (next->available_bytes > 0)
	{

		first->available_bytes += next->capacity + sizeof(block_t);
		first->next = next->next;

	}
		first->capacity = first->available_bytes;		
}

size_t VSABiggestFreeBlock(vsa_t *vsa)
{
	block_t *curr = vsa->head;
	size_t max_block_available = curr->available_bytes;

	while (curr != NULL)
	{
		if (curr->available_bytes > max_block_available)
		{
			max_block_available = curr->available_bytes;
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

void Help(vsa_t *vsa)
{
	block_t *curr = vsa->head;
	puts("");

	while (curr != NULL)
	{
		printf("curr->capacity = %ld\n", curr->capacity);
		printf("curr->available_bytes = %ld\n", curr->available_bytes);
		printf("curr address = %p\n", (void*)curr);
	
		puts("");
		curr = curr->next;
	}
}
