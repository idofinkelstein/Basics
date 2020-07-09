 /* 
*  Fixed Sized allocation is a used to allocate fixed size blocks in continguous 
*  memory.
*   
*  Attributes:
* -	Blocks are aligned to WORD size.
* -	User provides pointer to the memory pool allocated.
* - All sizes are in bytes.
*
* Main operations:
* - Init:       		initializing the handler O(1)
* - Free:       		freeing a block O(1)
* - Allocate:   		allocation of block O(1)  
* - FreeBlocks: 		number of free blocks left in the pool 
* - RequiredPoolSize:   calculates the required pool size
*
* FSA API
* -   06/07/20 17:00 - Ver:  1.0  API team proposal
* -   06/07/20 18:18 - Ver:  1.1  API Approval
* -   07/07/20 08:46 - Ver:  1.2  Remove Init function complexity limitation
*								  Init Function - Add comment on return value
*								  Add <stddef.h> libary
*/

#if 0

/* Example of use: */
int main(void)
{
	fsa_t *fsa1 = NULL;
	fsa_t *fsa2 = NULL;

	T1 *a_ptr = NULL;
	T2 *b_ptr = NULL;
    /* pool
     * block
     */

    /* allocate pool to hold 10 blocks of 4-bytes size */
    
    size_t pool2_size = FSARequiredPoolSize(num_of_blocks=10000, block_size=37);

	void *pool1 = malloc( pool1_size );
	void *pool2 = malloc( pool2_size );
	
	

	fsa1 = FSAInit(pool1, pool_size=4000, block_size=24);
	fsa2 = FSAInit(pool2, pool_size=pool2_size, block_size=37);

    while(1)
    {
        note_t* node_ptr = FSAAlloc(fsa1);
        struct Person* pers_ptr = FSAAlloc(fsa2);

        node_ptr->data = ...;
        
        printf("num of free blocks in pool: %lu\n", FSAFreeBlocks(fsa1));
        if (node_ptr == NULL)
        {
            printf("no more free blocks\n");
        }

        FSAFree(/*fsa1,*/ a_ptr);
        FSAFree(/*fsa2,*/ b_ptr);
    }

    
    free(pool1);
    free(pool2);

	return (0);
}

#endif /* End of example */

#ifndef ILRD_FSA_H
#define ILRD_FSA_H

#include <stddef.h>

typedef struct fixed_sized_alloc fsa_t;

/*---------------------------------------------------------------------------*/

/* FSAInit:
*   - Initiates an FSA handler.
*
* Args:
*	- mem_pool - pointer to the memory pool.
*	- pool_size - size of memory pool allocated by the user (in bytes).
*	- block_size - requested size of each block (in bytes).
*
* Return Value:
*   - if succeeded, return a pointer to an FSA handler.
*   - if pool size not enough for at least one block, return NULL.
*/
fsa_t *FSAInit(void *mem_pool, size_t pool_size, size_t block_size);

/*---------------------------------------------------------------------------*/

/* FSAFree:
*   - Free block given by the user. 
*
* Args:
*   - block - pointer to the block. 
*/

void FSAFree(void *block);

/*---------------------------------------------------------------------------*/

/* FSAAlloc:
*	- Allocate a block of memory in the pool
*
* Args:
*	- fsa - pointer to an fsa handler given by a user.
*
* Return Value:
*	pointer to the block allocated.
*
* Comments:
*	- in case no more blocks available - returns NULL
*/

void *FSAAlloc(fsa_t *fsa);

/*---------------------------------------------------------------------------*/

/* FSARequiredPoolSize:
*
*   - calculates the required pool size according to number of blocks and 
*     block size given by the user.
*
* Args:
*   - num_of_blocks - number of blocks.
*   - block_size - size of each block (in bytes).
*
* Return Value:
*	required pool size in bytes. 	
*/

size_t FSARequiredPoolSize(size_t num_of_blocks, size_t block_size);

/*---------------------------------------------------------------------------*/

/* FSAFreeBlocks:
*   - returns the number of available blocks left in the pool.
*
* Args:
*   - fsa - pointer to fsa handler given by a user.
*
* Return Value:
*	nubmer of available blocks left in the pool. 
*/

size_t FSAFreeBlocks(fsa_t *fsa);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_FSA_H */ 
