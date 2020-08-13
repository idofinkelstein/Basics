/*******************************
File name: heap.h
Author: Ido Finkelstein
Reviewer: Gal Shvinkelstein
Date: 13/8/2020
********************************/

/* a heap is a specialized tree-based data structure which is essentially an 
almost complete. Heap stores the max/min value in its root.

-------------------------------------------------------------------------------

Operations on heap:
-   Push - adds an element to the heap.
-   Pop - removes the top element of the heap.
-   Peek - displays the first element of heap which is the min / max value
-   Remove - removes given element from the heap
    a pointer to it.

-------------------------------------------------------------------------------
Heap API
-   Ver: 1.0 
-   Ver: 1.1 change heap_is_match_func_t
*/

#ifndef ILRD_HEAP_H
#define ILRD_HEAP_H 

#include <stddef.h>	/* size_t */

typedef struct heap heap_t;

/* compare function, returns whether data1 is bigger, 
   smaller or equals to data2 */
typedef int (*heap_cmp_func_t)(const void *data1, 
							   const void *data2, 
							   void *param);

/* return value is boolean - 1 for match, 0 if not matched */
typedef int (*heap_is_match_func_t)(const void *data1, 
									const void *data2, 
									void *param);

/*---------------------------------------------------------------------------*/

/* HeapCreate:
*   - Allocates memory and creates the heap of null according to capacity
*     given by the user.
*   - capacity - capacity of starting heap
* 
* Args:
*   - capacity - requested capacity of the heap to be created
*	- cmp - pointer compare function implementerd by the user
*	- param - parameter for cmp function
*
* Return Value:
*   - pointer to heap in case of success or NULL if memory allocation failed.
*/
heap_t *HeapCreate(heap_cmp_func_t cmp, void *param);

/*---------------------------------------------------------------------------*/

/* HeapDestroy:
*   - Frees the recources of the heap.
*
* Args:
*   - heap - handle to the heap given by user
*
*/
void HeapDestroy(heap_t *heap);

/*---------------------------------------------------------------------------*/

/* HeapPush:
*   - Pushes a new data to the heap
*
* Args:
*   - heap - handle to the heap given by user
*   - data - data to be pushed to the heap
*  
* Return Value:
*   - 0 on success
*   - 1 on failure - allocat fail 
*/
int HeapPush(heap_t *heap, void *data);

/*---------------------------------------------------------------------------*/

/* HeapPeek:
*   - Retrives the top data on the heap
*
* Args:
*   - heap - handle to the heap given by user
*
* Return Value:
*   - Upon success returns the data in the top of the heap.
*   - Upon failure returns null.
*/
void *HeapPeek(heap_t *heap);

/*---------------------------------------------------------------------------*/

/* HeapPop:  
*   - removes the top data from the heap
*
* Args:
*   - heap - handle to the heap given by user
*   
* Return Value:
*   - Upon success returns the data in the top of the heap.
*   - Upon failure returns null.
*/

void *HeapPop(heap_t *heap);

/*---------------------------------------------------------------------------*/

/* HeapRemove:   
*  - remove a given data from the heap
*
* Args:
*   - heap - handle to the heap given by user
*	- data - data to find and remove from the heap
*	- is_match - pointer IsMatch function implementerd by the user
*   - param - parameter for cmp function
*
* Return Value:
*   - return the data that was remove from heap
*/

void *HeapRemove(heap_t *heap, void *data, heap_is_match_func_t is_match, void *param);

/*---------------------------------------------------------------------------*/

/* HeapSize:
*   - Number of datas in the heap at a given moment
*
* Args:
*   - heap - handle to the heap given by user
*
* Return Value:
*   - Number of elemnts in the heap
*/
size_t HeapSize(heap_t *heap);

/*---------------------------------------------------------------------------*/

/*IsEmpty
*   - Checks if the heap is empty
*
* Args:
*   - heap - head of heap given by user
*
* Return Value is boolean:
*   - Returns 1 if heap is empty 
*	- Returns 0 if heap is not empty
*/
int HeapIsEmpty(heap_t *heap);

/*------------------------------Debug functions declaration-------------------*/
#ifdef NDEBUG
void Print(heap_t *heap);
int IsMaxHeap(heap_t *heap);
int IsMinHeap(heap_t *heap);
#endif

#endif /* ILRD_HEAP_H */
