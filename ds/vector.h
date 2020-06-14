/* 
Dynamic vector is a random access dynamic array.

Attributes:
-   Capacity is a user given value
-   Can hold pointers to any type of data, including structs
-   All Operations are amortized O(1)

Main operations on vector:
-	Get element - Retrieves the value of the element at a specific index
-   Push back - adds an element to the end of the size of the vector
-   Pop back - removes the last element that was not yet removed
-   Set element- sets the value of the element at a specific index
-   Reserve - reallocates memory to the new capacity
-   Shrink to fit - shrinks capacity of the memory to the current size

Vector API
-   Ver:  1.0  API team Approval
-   Ver:  1.1  API approved 
-   Ver:  1.2  fixing:  - Adapted VectorSetElement signature
-                       - Comments in - VectorSetElement
-                                     - VectorGetElement
-                                     - VectorCapacity  
*/

#ifndef ILRD_VECTOR_H
#define ILRD_VECTOR_H

#include <stddef.h>	/* size_t */

typedef struct vector vector_t; 

/*---------------------------------------------------------------------------*/

/* VectorCreate:
*   - Allocates memory and creates the vector of null according to capacity
*     given by the user.
* Args:
*   - capacity - requested initial capacity of the vector to be created           
*
* Return Value:
*   - pointer to vector in case of success or NULL if creation failed
*
* Comment: capacity must be greater than zero,  otherwise undefined behavior
*/
vector_t *VectorCreate(size_t capacity);

/*---------------------------------------------------------------------------*/

/* StackDestroy:
*   - Frees the memory of the vector
*
* Args:
*   - vector - pointer to vector given by user
*/
void VectorDestroy(vector_t *vector);

/*---------------------------------------------------------------------------*/
/* VectorGetElement:
*   - Retrieves the value of the element at a specific index
* 
* Args:
*   - vector - pointer to vector given by user
*   - index -  index of the element to be retrieved
*
* Return Value:
*   - element in the given index
*
* Comment: Index must be < than the size of vector,
* otherwise undefined behavior
*                
*/
void *VectorGetElement(const vector_t *vector, size_t index);

/*---------------------------------------------------------------------------*/
/* vectorSetElement:
*   - Sets the value of the element at a specific index
* 
* Args:
*   - vector - pointer to vector given by user
*   - index - index of the to be set element
*   - element - the element to set
* Comment: In case index is bigger or equal to size, it's
* undefined behavior
* 
*/
void VectorSetElement(vector_t *vector, size_t index, void *element);

/*---------------------------------------------------------------------------*/

/* VectorPushBack:
*   - Add an element, allocated memory if necessary
* 
* Args:
*   - vector - pointer to vector given by user
*	- element - the element to add
*
* Return Value:
*   - 0 on success
*   - 1 on failure
*
*  Comment: In case size is equal to capacity, duplicate the memory capacity. 
*/
int VectorPushBack(vector_t *vector, void *element);

/*---------------------------------------------------------------------------*/

/* VectorPopBack:
* 
*   - Remove the element on top of the vector
* 
* Args:
*   - vector - pointer to vector given by user
*
*  Comment: In case size is a quarter of the capacity,
*  the memory capacity will be reduced by half. 
*/
void VectorPopBack(vector_t *vector);

/*---------------------------------------------------------------------------*/

/* VectorSize:
*   - Retrieves the number of elements in the vector at a given moment
* 
* Args:
*   - vector - pointer to vector given by user
*
* Return Value:
*   - Number of elements in the vector
*/
size_t VectorSize(const vector_t *vector);

/*---------------------------------------------------------------------------*/

/* VectorCapacity:
*   - Retrieves the capacity of the vector
*
* Args:
*   - vector - pointer to vector given by user
*
* Return Value:
*   - Capacity of the vector
*/
size_t VectorCapacity(const vector_t *vector);

/*---------------------------------------------------------------------------*/

/* VectorReserve:
*   - Increase the capacity of the vector
* 
* Args:
*   - vector - pointer to vector given by user
*   - new_capacity -  the new capacity to be allocated  
*
* Return Value:
*   - 0 - on success
*   - 1 - on failure
*
*  Comment: the new memory to reserve must be greater than the
*  current capacity
*/
int VectorReserve(vector_t *vector, size_t new_capacity);

/*---------------------------------------------------------------------------*/

/* VectorShrinkToFit:
*   - Removal of unused capacity to reduce capacity to size.
* 
* Args:
*   - vector - pointer to vector given by user
*
*  Comment: the new shrinked memory must be equal
*  or greater than the initial capacity.
*/
void VectorShrinkToFit(vector_t *vector);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_VECTOR_H */