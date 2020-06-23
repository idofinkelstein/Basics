/* 
 doubly linked list is a linear data structure, 
 each node contains, besides the next-node link,
 a second link field pointing to the 'previous' node in the sequence

Attributes:
-	Grows by demand.
-	Holds data by reference - can store handles to any type of data.
-	User has a pointer to the list and iterators to data as needed.

Main operations on DLL:
-   Begin - returns an iterator to the first element in the list. O(1)
-   End - returns an iterator to the end of the list. O(1)
-   Next - returns an iterator to the next element. O(1)
-   prev - returns an iterator to the previeus element in the list. O(1)
-   GetData - retrieves data from current iterator. O(1) 
-   SetData - sets data in current iterator. O(1)
-   Is_Equal - checks if two iterators are identical. O(1)
-   Insert - inserts data before given iterator. O(1)
-   Remove - removes given iterator. O(1)
-   size - counts the elements in the list. O(n)
-   pushfront - insert data to begnining the of the list O(1) 
-   pushback - insert data to end the of the list O(1)
-   popfront - remove data from  the begining of the list O(1)
-   popback -remove data from  the end of the list O(1)
-   Find - finds data stored in list. O(n)
-   ForEach - performs an operation given by the user on all elements in the
	list. O(n)
-	splice - slices the range from src list and appends to the dest list before the 
    iterator where O(1)

Generally, in case of errors will return the end of the list. User should
compare the results with the end of the list to determine errors. 
Please note the documentation of each function for further details.
It is recommended to use asserts when compiling.

Dlist API
-   18/06/20 15:00  Ver:  1.0  API team discussion
-   18/06/20 17:00  Ver:  1.1  API mentor approval
-   19/06/20 11:00  Ver:  1.2  fixig: removing "const" from void *data in DListSetData
                                      Dlist where Slist was still written
-   19/06/20 13:30  Ver:  1.3  fixig: removing "const" from void *data in 
									  do_action, Insert, PushFront, PushBack.
                                      Adding "const" to void *data  is_match.
*/

#ifndef ILRD_DLIST_H
#define ILRD_DLIST_H

#include <stddef.h>	/* size_t */

/* typedefs for the dlist and the iterator  */
typedef struct dlist_node* dlist_iter_t;  
typedef struct dlist dlist_t; 

/* typedefs of functions to be implemented by the user */

/* return value is boolean - 1 for match, 0 if not matched */
typedef int (*dlist_is_match_func_t)(const void *data, void *param);
/* return value is status - 0 for success, otherwise any status set 
   by the user */
typedef int (*dlist_do_action_func_t)(void *data, void *param);

/*---------------------------------------------------------------------------*/
/* DListCreate:
*   - creates an empty list.
*
* Return Value:
*   - pointer to the dlist.
*/
dlist_t *DListCreate(void);

/*---------------------------------------------------------------------------*/
/* DListDestroy:
*   - destroys the list
*
* Args:
*   - dlist - pointer to dlist given by user
*/
void DListDestroy(dlist_t *dlist);

/*---------------------------------------------------------------------------*/
/* DListBegin
*   - returns an iterator to the first element in the list.
*
* Args:
*	- dlist - pointer to dlist
*
* Return value:
*   - an iterator to the first element in the list
*/
dlist_iter_t DListBegin(const dlist_t *dlist);

/*---------------------------------------------------------------------------*/
/* DListEnd
*   - returns an iterator to the end of the list
*
* Args:
*	- dlist - pointer to dlist
*
* Return value:
*   - iterator to the end of the list
*/

dlist_iter_t DListEnd(const dlist_t *dlist);

/*---------------------------------------------------------------------------*/
/* DlistNext
*   - returns an iterator to the element after the iterator given by the user
*
* Args:
*   - iter - iterator to get the element after
*
* Return value:
*   - an iterator to the next element after the iterator given.
*
* Comments: 
*   - in case of invalid iterator given - undefined behavior.
*/

dlist_iter_t DListNext(const dlist_iter_t iter);

/*---------------------------------------------------------------------------*/
/* DlistPrev
*   - returns an iterator to the element before the iterator given by the user
*
* Args:
*   - iter - iterator to get the element after
*
* Return value:
*   - an iterator to the element before the iterator given.
*
* Comments: 
*   - in case of invalid iterator given - undefined behavior.
*/

dlist_iter_t DListPrev(const dlist_iter_t iter);

/*---------------------------------------------------------------------------*/
/* DlistGetData
* - returns the data stored in the given iterator.
*
* Args:
*   - iter - iterator to retrieve data from
*
* Return value:
*   - Data stored in the iterator
*
* Comments: 
*   - in case of invalid iterator - undefined behavior.
*/
void *DListGetData(const dlist_iter_t iter);

/*---------------------------------------------------------------------------*/
/* DListSetData
* - sets data in a given iterator
*
* Args:
*   -  iter - iterator in which we want to set the data

* Comments: 
*	- in case of invalid iterator - undefined behavior.
*/
void DListSetData(dlist_iter_t iter, void *data);

/*---------------------------------------------------------------------------*/
/* DListIsEqual
* - checks if two iterators are equal
*
* Args:
*   - iter1 - first iterator to compare
*   - iter2 - second iterator to compare 
*
* Return boolean value:
*   - 1 - equal (TRUE) 
*   - 0 - not equal (FALSE)
*/
int DListIterIsEqual(const dlist_iter_t iter1, const dlist_iter_t iter2);

/*---------------------------------------------------------------------------*/
/* DListIsEmpty:
*   - checks if the dlist is empty or not
* 
* Args:
*   - dlist - pointer to dlist given by user
*  
* Return boolean Value:
*   1 - empty (TRUE)
*   0 - not empty. (FALSE)      
*/
int DListIsEmpty(const dlist_t *dlist);

/*---------------------------------------------------------------------------*/
/* DListInsert:
* - inserts new element before the iterator given by the user.
* 
* Args:
*   - dlist - pointer to dlist
*   - where - iterator before which we want to store the data
*   - data - data to store
*
* Return value:
*   - if succeeded, returns an iterator to the data
*	- if failed, returns the end of the list
*
* Comments: 
*	- in case of invalid iterator - undefined behavior.
*	- User should compare the return value to the end of the list to determine
*	  if function succeeded.
*	- In case list is empty, provide the end of the list (DListEnd) as "where"
*/
dlist_iter_t DListInsert(dlist_t *dlist, dlist_iter_t where, void *data);

/*---------------------------------------------------------------------------*/
/* DListRemove:
*   - removes an element from the linked list.
* 
* Args:
*	- dlist - pointer to dlist given by user
*   - iter - iterator to the element to remove
* 
* Return value:
*	- an iterator to the next element
*
* Comments: 
*   - if the end of the list is given - undefined behavior.
*/
dlist_iter_t DListRemove(dlist_iter_t iter);

/*---------------------------------------------------------------------------*/
/* DListPushFront:
* - inserts new element in the beginning of the list.
* 
* Args:
*   - dlist - pointer to dlist
*   - data - data to store
*
* Return value:
*   - if succeeded, returns an iterator to the data
*	- if failed, returns the end of the list
*
* Comments: 
*	- User should compare the return value to the end of the list to determine
*	  if function succeeded.
*/
dlist_iter_t DListPushFront(dlist_t *dlist, void *data);

/*---------------------------------------------------------------------------*/
/* DListPushBack:
* - inserts new element in the end of the list.
* 
* Args:
*   - dlist - pointer to dlist
*   - data - data to store
*
* Return value:
*   - if succeeded, returns an iterator to the data
*	- if failed, returns the end of the list
*
* Comments: 
*	- User should compare the return value to the end of the list to determine
*	  if function succeeded.
*/
dlist_iter_t DListPushBack(dlist_t *dlist, void *data);

/*---------------------------------------------------------------------------*/
/* DListPopFront:
*   - removes an element from the beginning of linked list.
* 
* Args:
*	- dlist - pointer to dlist given by user
* 
* Return value:
*	- the data in the popped element
*
* Comments: 
*   - if dlist is empty - undefined behavior.
*/
void *DListPopFront(dlist_t *dlist);

/*---------------------------------------------------------------------------*/
/* DListPopBack:
*   - removes an element from the end of linked list.
* 
* Args:
*	- dlist - pointer to dlist given by user
* 
* Return value:
*	- the data in the popped element
*
* Comments: 
*   -if dlist is empty - undefined behavior.
*/
void *DListPopBack(dlist_t *dlist);

/*---------------------------------------------------------------------------*/
/* DListSize:
*   - counts the number of elements in the dlist.
* 
* Args:
*   - dlist - pointer to dlist
*  
* Return Value:
*   - number of elements in the dlist         
*/
size_t DListSize(const dlist_t *dlist);

/*---------------------------------------------------------------------------*/
/* DListFind:
*   - finds data stored in list.
* 
* Args:
*   - from - iterator to the beginning of the range
*   - to - iterator to the end of the range
*   - is_match - function pointer to perform comparison
*	- param - parameter to pass to match function (optional)
*
* Return Value: 
*	- if succeeded, returns iterator to the first element matched
*	- if failed, returns the iterartor "to". 
*
* Comments: 
*	- Range includes "from" and excludes "to".
*	- User should compare the return value to the "to" iterator, to determine
*	  whether function succeeded.
*	- is_match is a function to be implemeneted by the user. See signature 
*	  in typedef.
*/
dlist_iter_t DListFind(const dlist_iter_t from, 
                       const dlist_iter_t to,
					   dlist_is_match_func_t is_match, 
                       void *param);

/*---------------------------------------------------------------------------*/
/* DListForEach:
*   - performes action in a function given by the user on all list elements
*
* Args:
*   - from - iterator to the beginning of range
*   - to - iterator to the end of range
*   - do_action - function pointer to the action pointer
*	- param - parameter to pass to action function (optional)
*   
* Return value:
*   - 0 - the action succeeds for all the elements in the range
*   - otherwise, the action failed and returns the status returned 
*     from the do_action function  .
*
* Comments: 
*	- Range includes "from" and excludes "to".
*	- do_action is a function to be implemeneted by the user. See signature 
*	  in typedef.
*/
int DListForEach(dlist_iter_t from, 
                 const dlist_iter_t to, 
				 dlist_do_action_func_t do_action, 
                 void *param);
                 
/*---------------------------------------------------------------------------*/
/* DListSplice:
*   - slices the range from src list and appends to the dest list before the 
*    iterator where
*
* Args:
*   - from - iterator to the beginning of range in src list
*   - to - iterator to the end of range in src list
*   - where - iterator in dest before which to append the range
*
* Return value:
*   - an iterator to the last spliced element
*
* Comments: 
*   - in case of invalid iterators - undefined behaviour
*   - Range includes "from" and excludes "to". 
*/
dlist_iter_t DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_DLIST_H */
