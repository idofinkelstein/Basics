 /* 
*  Variable Sized allocation is a used to allocate Variable size blocks in
*  continguous memory.
*   
*   Attributes:
* -	Blocks are aligned to WORD size.
* - Defragmantation accure durinng alloc 
* -	User provides pointer to the memory pool allocated.
* - All sizes are in bytes.
*
* Main operations:
* - Init:       		    initializing the handler 
* - Free:       		    freeing a block O(1)
* - Allocate:   		    allocation of block O(n)  
* - VSABiggestFreeBlock: 	biggest block left in the pool 
*/

/*---------------------------------------------------------------------------*/

#ifndef ILRD_VSA_H
#define ILRD_VSA_H

#include <stddef.h>

typedef struct variable_sized_alloc vsa_t;

/*---------------------------------------------------------------------------*/

/* VSAInit:
*   - Initiates an VSA handler.
*
* Args:
*	- mem_pool - pointer to the memory pool.
*	- pool_size - size of memory pool allocated by the user (in bytes).
*
* Return Value:
*   - if succeeded, return a pointer to an VSA handler.
*/
vsa_t *VSAInit(void *mem_pool, size_t pool_size);

/*---------------------------------------------------------------------------*/

/* VSAFree:
*   - Free block given by the user. 
*
* Args:
*   - block - pointer to the block. 
*/

void VSAFree(void *block);

/*---------------------------------------------------------------------------*/

/* VSAAlloc:
*	- Allocate a block of memory in the pool
*
* Args:
*	- vsa - pointer to an vsa handler given by a user.
*	- block_size - requested size block(in bytes).
*
* Return Value:
*	pointer to the block allocated.
*
* Comments:
*	- in case biggest free space not big enough - returns NULL
*/

void *VSAAlloc(vsa_t *vsa, size_t block_size);

/*---------------------------------------------------------------------------*/

/* VSABiggestFreeBlock:
*   - check for the biggest block available left in the pool and return size.
*
* Args:
*   - fsa - pointer to vsa handler given by a user.
*
* Return Value:
*	number of bytes of the biggest possible block available in the pool taking
	into acount Adjacent free blocks. 
*/

size_t VSABiggestFreeBlock(vsa_t *vsa);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_VSA_H */ 
