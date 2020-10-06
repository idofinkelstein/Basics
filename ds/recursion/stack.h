/* 
-------------------------------------------------------------------------------
Stack is a LIFO policy structure.

Attributes:
-   Capacity is a user given value
-   Can hold pointers to any type of data, including structs
-   All Operations are in O(1)

-------------------------------------------------------------------------------

Operations on stack:
-   Push - adds an element to the stack.
-   Pop - removes the most recently added element that was not yet removed.
-   Peek - looks at the most recently added element on the stack and returns
    a pointer to it.

-------------------------------------------------------------------------------
Stack API
-   Ver: 1.0  API team Approval
-   Ver: 1.1  Update Comments 
-   Ver: 1.2  API Approved
-   Ver: 1.3  Fixing rollback issue
*/

#ifndef ILRD_STACK_H
#define ILRD_STACK_H

#include <stddef.h>	/* size_t */

typedef struct stack stack_t; 

/*---------------------------------------------------------------------------*/

/* StackCreate:
*   - Allocates memory and creates the stack of null according to capacity
*     given by the user.
*   - capacity - max volume of the stack
* 
* Args:
*   - capacity - requested capacity of the stack to be created
*
* Return Value:
*   - pointer to stack in case of success or NULL if memory allocation failed.
*/
stack_t* StackCreate(size_t capacity);

/*---------------------------------------------------------------------------*/

/* StackDestroy:
*   - Frees the memory of the stack.
*
* Args:
*   - stack - head of stack given by user
*
*/
void StackDestroy(stack_t *stack);

/*---------------------------------------------------------------------------*/

/* StackPush:
*   - Pushes a new element on top of the stack
*
* Args:
*   - stack - head of stack given by user
*   - element - element to be pushed to the stack
*  
* Return Value:
*   - 0 on success
*   - 1 on failure - stack is full
*/
int StackPush(stack_t *stack, void *element);

/*---------------------------------------------------------------------------*/

/* StackPop:
*   - Releases the element on top of the stack
*
* Args:
*   - stack - head of stack given by user
*
*/
void StackPop(stack_t *stack);

/*---------------------------------------------------------------------------*/

/* StackPeek:
*   - Retrives the value of the element on top of the stack
*
* Args:
*   - stack - head of stack given by user

* Return Value:
*   - Upon success returns the element in the top of the stack.
*   - Upon failure returns null.
*/
void *StackPeek(stack_t *stack);

/*---------------------------------------------------------------------------*/

/* StackSize:
*   - Number of elements in the stack at a given moment
*
* Args:
*   - stack - head of stack given by user
*
* Return Value:
*   - Number of elemnts in the stack
*/
size_t StackSize(stack_t *stack);

/*---------------------------------------------------------------------------*/

/*IsEmpty
*   - Checks if the stack is empty
*
* Args:
*   - stack - head of stack given by user
*
* Return Value:
*   - Returns 1 when stack is empty and 0 when stack is not empty
*/
int StackIsEmpty(stack_t *stack);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_STACK_H */

