/* A Queue is a linear structure which follows a particular order in which
   the operations are performed. The policy is First In First Out (FIFO). 

Attributes:
-	Grows by demand.
-	Holds data by reference - can store handles to any type of data.
-	User has a pointer to the queue.

Main operations on Queue:
-   QCreate - returns an pointer to an empty queue. O(1)
-   QDestory - destory a given queue. O(n)
-   QSize - returns a count of total elements in a given queue. O(n)
-   QIsEmpty - checks if a given queue is empty. O(1) 
-   QEnqueue - inserts data to the end of a given queue. O(1)
-   QDequeue - removes data from the start of a given queue. O(1)
-	QPeek - retrieves data which is set on the start of a given queue. O(1)
-   QAppend - appends the start of source queue with end of destination queue.
	O(1)

Please note the documentation of each function for further details.
It is recommended to use asserts when compiling.

queue API
-   14/06/20 15:40 - Ver:  1.0  API team proposal
-   14/06/20 16:00 - Ver:  1.1  API updated comments
-   14/06/20 17:40 - Ver:  1.2  API mentor approval
-   15/06/20 20:43 - Ver:  1.3  fixing:  
									   - Add comment to QPeek
-                                      - Fix QDestory requested complicity 
										 from O(1) to O(n)


*/

#ifndef ILRD_QUEUE_H
#define ILRD_QUEUE_H

#include <stddef.h>	/* size_t */

/* C file
#include "slist.h"

struct queue
{
    slist_t *slist;
}
*/

typedef struct queue queue_t;

/*---------------------------------------------------------------------------*/
/* QCreate:
*   - Creates an empty queue.
*
* Return Value:
*   - if succeeded, return a pointer to a queue.
*   - if failed, return NULL.
*/
queue_t *QCreate(void);

/*---------------------------------------------------------------------------*/

/* QDestroy:
*   - Destory a given queue.
*
* Args:
*   - queue - pointer to queue given by a user.
*
* Comments: 
*   - in case of invalid queue - undefined behavior.
*
*/
void QDestroy(queue_t *queue);

/*---------------------------------------------------------------------------*/

/* QSize:
*   - Counts the number of elements in a given queue.
*
* Args:
*   - queue - pointer to queue given by a user.
*
* Return Value:
*   - Number of elemnts in the queue.
*
* Comments: 
*   - in case of invalid queue - undefined behavior.
*
*/
size_t QSize(const queue_t *queue);

/*---------------------------------------------------------------------------*/

/* QIsEmpty
*   - Checks if a given queue is empty.
*
* Args:
*   - queue - pointer to queue given by a user.
*
* Return Value - boolean:
*   - 1 - the queue is empty (TRUE).
*   - 0 - the queue is not empty (FALSE).
*
* Comments: 
*   - in case of invalid queue - undefined behavior.
*
*/
int QIsEmpty(const queue_t *queue);

/*---------------------------------------------------------------------------*/

/* QEnqueue:
*   - Inserts a new element to the end of a given queue.
*
* Args:
*   - queue - pointer to a queue given by a user.
*   - data - data to store.
*  
* Return Value - status:
*   - 0 - on success.
*   - 1 - on failure. 
*
* Comments: 
*   - in case of invalid queue - undefined behavior.
*  
*/
int QEnqueue(queue_t *queue, void *data);

/*---------------------------------------------------------------------------*/
/* QDequeue:
*   - Remove an element from the beginning of a given queue.
*
* Args:
*   - queue - pointer to a queue given by a user.
*
* Comments: 
*   - in case of invalid queue - undefined behavior.
*   - in case of empty queue - undefined behaviour.
*/
void QDequeue(queue_t *queue);

/*---------------------------------------------------------------------------*/

/* QPeek:
*   - retrieves data which is set on the beginning of a given queue.
*
* Args:
*   - queue - pointer to a queue given by a user.
*
* Return Value:
*   - returns a pointer to the data.
*
* Comments: 
*   - in case of invalid queue - undefined behavior.
*/
void *QPeek(const queue_t *queue);

/*---------------------------------------------------------------------------*/
/* QAppend:
*   - Append the src queue to the end of dest queue.
*
* Args:
*   - dest - pointer to a queue given by a user.
*   - src - pointer to a queue given by a user.
*
* Comments: 
*   - in case of invalid pointers - undefined behavior.
*   - src - becomes a pointer to an empty queue.
*   
*/
void QAppend(queue_t *dest, queue_t *src);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_QUEUE_H */ 
