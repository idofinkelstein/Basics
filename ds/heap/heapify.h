/* heap util file, contains funtions to support Heap DS.

-------------------------------------------------------------------------------

Util functions include:
-   HeapifyUp - re-arranges the array to have a heap property, going bottom-up
-   HeapifyDown - re-arranges the array to a have heap property, going up-bottom


-------------------------------------------------------------------------------
heap_util API
-   Ver: 1.0 
-   Ver: 1.1 - change signatures to receive nmemb 
*/

#ifndef ILRD_HEAP_UTIL_H
#define ILRD_HEAP_UTIL_H 

#include <stddef.h>    /* size_t */


/* compare function, returns number less than zero if data1 is lesser than
   data2, nubmer greater than zerp if data1 is greater than data2 and zero 
   if equal */
typedef int (*heapify_cmp_func_t)(const void *data1, const void *data2, void *param);


/*---------------------------------------------------------------------------*/

/* HeapifyUp:
*   re-arranges the array to have a heap property, going bottom-up
* 
* Args:
*  - arr - pointer to the array to transform to heap
*  - elem_size - size of elements stored in the array
*	- cmp - pointer compare function implementerd by the user
*	- param - parameter for cmp function
*  - index - index of the node to swap up
* 
*/
void HeapifyUp(void *base, size_t nmemb, size_t index, size_t elem_size,     
               heapify_cmp_func_t cmp, void *param);

/*---------------------------------------------------------------------------*/

/* HeapifyDown:
*   re-arranges the array to have a heap property, going up-bottom
* 
* Args:
*  - arr - array to transform to heap
*  - elem_size - size of elements stored in the array
*	- cmp - pointer compare function implementerd by the user
*	- param - parameter for cmp function
*  - index - index of the node to swap down
*
*/
void HeapifyDown(void *base, size_t nmemb, size_t index, size_t elem_size,     
                 heapify_cmp_func_t cmp, void *param);

/*---------------------------------------------------------------------------*/

#endif  /* ILRD_HEAP_UTIL_H */