/* A Priority Queue is an extension of queue, in which every element has 
   a priority associated with it.
   
Attributes:
-	Grows by demand.
-	Holds data by reference - can store handles to any type of data.
-	User has a pointer to the pqueue.

Main operations on Queue:
-   PQCreate - returns an pointer to an empty pqueue. O(1)
-   PQDestroy - destory a given pqueue. O(n)
-   PQSize - returns a count of total elements in a given pqueue. O(n)
-   PQIsEmpty - checks if a given pqueue is empty. O(1) 
-   PQEnqueue - Inserts a new element to a given pqueue, according to a 
                given priority. O(n)
-   PQDequeue - removes data from the start of a given pqueue. O(1)
-	PQPeek - retrieves data which is set on the start of a given pqueue. O(1)
-   PQClear - Clears all the elements from the pqueue. O(n)
-   PQErase - Finds the first element to match the given param, returns the 
			  data, and removes the element from the pqueue. O(n)
	

Please note the documentation of each function for further details.
It is recommended to use asserts when compiling.

pqueue API
-   25/06/20 16:20 - Ver:  1.0  API team proposal
                           1.1  Approved
-   26/06/20 10:20 - Ver:  1.2  return value of PQErase updated
-   26/06/20 19:55 - Ver:  1.3  fixed mistake in is before typedef 
-   28/06/20 17:40 - Ver:  1.4  is before edited to compare
-   28/06/20 18:45 - Ver:  1.5  added argument void *param to create function
*/

#ifndef ILRD_PQUEUE_H
#define ILRD_PQUEUE_H

#include <stddef.h>	/* size_t */

typedef struct pqueue pqueue_t;

/* typedefs of functions to be implemented by the user 
* Return values:
*   1 - if data1 is bigger then data2
*  -1 - if data1 is lesser then data2
*   0 - equal 
*/

typedef int (*pqueue_cmp_func_t)(const void *data1, const void *data2, void *param);

/* return value is boolean - TRUE for match, FALSE if not matched */
typedef int (*pqueue_is_match_func_t)(const void *data, void *param);

/*---------------------------------------------------------------------------*/
/* PQCreate:
*   - Creates an empty pqueue.
*
* Return Value:
*   - if succeeded, return a pointer to a pqueue.
*   - if failed, return NULL.
*/
pqueue_t *PQCreate(pqueue_cmp_func_t cmpare, void *param);

/*---------------------------------------------------------------------------*/

/* PQDestroy:
*   - Destroys a given pqueue.
*
* Args:
*   - pqueue - pointer to pqueue given by a user.
*
* Comments: 
*   - in case of invalid pqueue - undefined behavior.
*
*/
void PQDestroy(pqueue_t *pqueue);

/*---------------------------------------------------------------------------*/

/* PQSize:
*   - Counts the number of elements in a given pqueue.
*
* Args:
*   - pqueue - pointer to pqueue given by a user.
*
* Return Value:
*   - Number of elemnts in the pqueue.
*
* Comments: 
*   - in case of invalid pqueue - undefined behavior.
*
*/
size_t PQSize(const pqueue_t *pqueue);

/*---------------------------------------------------------------------------*/

/* PQIsEmpty
*   - Checks if a given pqueue is empty.
*
* Args:
*   - pqueue - pointer to pqueue given by a user.
*
* Return Value - boolean:
*   - 1 - the pqueue is empty (TRUE).
*   - 0 - the pqueue is not empty (FALSE).
*
* Comments: 
*   - in case of invalid pqueue - undefined behavior.
*
*/
int PQIsEmpty(const pqueue_t *pqueue);

/*---------------------------------------------------------------------------*/

/* PQEnqueue:
*   - Inserts a new element to a given pqueue, according to a given priority.
*
* Args:
*   - pqueue - pointer to a pqueue given by a user.
*   - data - data to store.
*  
* Return Value - status:
*   - 0 - on success.
*   - 1 - on failure. 
*
* Comments: 
*   - in case of invalid pqueue - undefined behavior.
*  
*/
int PQEnqueue(pqueue_t *pqueue, void *data);

/*---------------------------------------------------------------------------*/
/* PQDequeue:
*   - Removes an element from the beginning of a given pqueue.
*
* Args:
*   - pqueue - pointer to a pqueue given by a user.
*
* Return Value :
*   - returns a pointer to the data.
*
* Comments: 
*   - in case of invalid pqueue - undefined behavior.
*   - in case of empty pqueue - undefined behaviour.
*/
void *PQDequeue(pqueue_t *pqueue);

/*---------------------------------------------------------------------------*/

/* PQPeek:
*   - retrieves data which is set on the beginning of a given pqueue.
*
* Args:
*   - pqueue - pointer to a pqueue given by a user.
*
* Return Value:
*   - returns a pointer to the data.
*
* Comments: 
*   - in case of invalid pqueue - undefined behavior.
*/
void *PQPeek(const pqueue_t *pqueue);

/*---------------------------------------------------------------------------*/
/* PQClear:
*   - Clears all the elements from the pqueue.
*
* Args:
*   - pqueue - pointer to a pqueue given by a user.
*
* Comments: 
*   - in case of invalid pointer - undefined behavior.
*   
*/
void PQClear(pqueue_t *pqueue);

/*---------------------------------------------------------------------------*/

/* PQErase:
*   - Finds the first element to match the given param, returns the data, and
*	  removes the element from the pqueue.
*
* Args:
*   - pqueue - pointer to a pqueue given by a user.
*   - is_match - function pointer to perform comparison.
*   - param - parameter to pass to match function
*
* Return Value:
*   - if searched element found ,returns a pointer to the data.
*   - if searched element did not found ,returns NULL.
* Comments: 
*   - in case of invalid pqueue - undefined behavior.
*/
void *PQErase(pqueue_t *pqueue, pqueue_is_match_func_t is_match, void *param);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_PQUEUE_H */ 
