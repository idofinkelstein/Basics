/*
 sorted list is a linear data structure, where elements are sorted uaccording
 to a criterion determined by the user.
Policy: Sort at insert
		Stable sort
		User provides a function to sort by

Attributes:
-	Grows by demand.
-	Holds data by reference - can store handles to any type of data.
-	User has a pointer to the list and iterators to data as needed.

Main operations on Sorted List:
-	Begin - returns an iterator to the first element in the list. O(1)
-	End - returns an iterator to the end of the list. O(1)
-	Next - returns an iterator to the next element. O(1)
-	Prev - returns an iterator to the previeus element in the list. O(1)
-	GetData - retrieves data from current iterator. O(1) 
-	Is_Equal - checks if two iterators are identical. O(1)
-	Insert - sorted insert to the list. O(n)
-	Remove - removes given iterator. O(1)
-	Size - counts the elements in the list. O(n)
-	PopFront - remove data from  the begining of the list O(1)
-	PopBack -remove data from  the end of the list O(1)
-	FindIf - finds data stored in list. O(n)
-	Find - finds where requested data is in the list. O(n)
-	ForEach - performs an operation given by the user on all elements in the
	range. O(n)
-	Merge - merges dest and src, two lists sorted based on the same
	criterion, into dest. Dest will be sorted after merge. O(n)


Generally, in case of errors will return the end of the list. User should
compare the results with the end of the list to determine errors. 
Please note the documentation of each function for further details.
It is recommended to use asserts when compiling.

Sorted list API
-	22/06/20 14:00 Ver 1.0	API team discussion
-	22/06/20 18:00 Ver 1.1	API mentor approval
-	22/06/20 22:30 Ver 1.2	SortedListCreate updated to return sorted_list_t
							do_action typedef changed from sl to sorted_list
							SortedListFind - added types to args
-	23/06/20 07:30 Ver 1.3	corrected const on cmp typedef
							SortedListCreate - changed from sl to sorted_list
-	23/06/20 22:30 Ver 1.4	const removed from all iter args
							Removed sorted list as arg to findif
							removed comment about 'where' with end
							of list in insert function
							cmp typedef - clarified which data is which
-	24/06/20 07:30 Ver 1.5	member name in sorted_list_iter_t was fixed		
-	24/06/20 11:30 Ver 1.6	fixed typedef of is_match and do_action
-							Merge comments were updated
-	28/06/20 15:40 Ver 1.7	Changed cmp to is_before and added void *param
-	28/06/20 19:00 Ver 1.8	Added void *param SortedListCreate
                            Updated SortedListCreate comments
                            Updated  comments in Merge
                            Updated retrun value comments of is_before
*/

#ifndef ILRD_SL_H
#define ILRD_SL_H

#include <stddef.h>	/* size_t */
#include "dlist.h" /* dlist_t */

/* typedefs for the sorted_list and the iterator  */
typedef struct
{
	dlist_iter_t internal_iter;
} sorted_list_iter_t;

typedef struct sorted_list sorted_list_t; 

/* typedefs of functions to be implemented by the user */

/* function should be implemented considering stable sorted policy
return value is boolean - TRUE for data1 is before data2, FALSE if not */
typedef int (*sorted_list_is_before_func_t)(const void *data1, 
								            const void *data2,
                                            void *param);

/* return value is boolean - TRUE for match, FALSE if not matched */
typedef int (*sorted_list_is_match_func_t)(const void *data, void *param);

/* return value is status - 0 for success otherwise any status set by user */
typedef int (*sorted_list_do_action_func_t)(void *data, void *param);

/*---------------------------------------------------------------------------*/
/* SortedListCreate:
*   - creates an empty list.
*
* Args:
*	- is_before - A pointer function that defines how to sorted the list
*	- param - parameters given by user to be sent into callback functions
*
* Return Value:
*   - pointer to the sorted list.
*/
sorted_list_t *SortedListCreate(sorted_list_is_before_func_t is_before,
								void * param);

/*---------------------------------------------------------------------------*/
/* SortedListDestroy:
*   - destroys the list
*
* Args:
*   - sorted_list - pointer to sorted list given by user
*/
void SortedListDestroy(sorted_list_t *sorted_list);

/*---------------------------------------------------------------------------*/
/* SortedListBegin
*   - returns an iterator to the first element in the list.
*
* Args:
*	- sorted_list - pointer to sorted list
*
* Return value:
*   - an iterator to the first element in the list
*/
sorted_list_iter_t SortedListBegin(const sorted_list_t *sorted_list);

/*---------------------------------------------------------------------------*/
/* SortedListEnd
*   - returns an iterator to the end of the list
*
* Args:
*	- sorted_list - pointer to sorted list
*
* Return value:
*   - iterator to the end of the list
*/

sorted_list_iter_t SortedListEnd(const sorted_list_t *sorted_list);

/*---------------------------------------------------------------------------*/
/* SortedlistNext
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

sorted_list_iter_t SortedListNext(sorted_list_iter_t iter);

/*---------------------------------------------------------------------------*/
/* SortedlistPrev
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

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter);

/*---------------------------------------------------------------------------*/
/* SortedlistGetData
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
void *SortedListGetData(sorted_list_iter_t iter);

/*---------------------------------------------------------------------------*/
/* SortedListIsEqual
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
int SortedListIterIsEqual(sorted_list_iter_t iter1,
						  sorted_list_iter_t iter2);

/*---------------------------------------------------------------------------*/
/* SortedListIsEmpty:
*   - checks if the sorted list is empty or not
* 
* Args:
*   - sorted_list - pointer to sorted list given by user
*  
* Return boolean Value:
*   1 - empty (TRUE)
*   0 - not empty. (FALSE)      
*/
int SortedListIsEmpty(const sorted_list_t *sorted_list);

/*---------------------------------------------------------------------------*/
/* SortedListInsert:
*  stable insert 
* 
* Args:
*   - sorted_list - pointer to sorted list
*   - data - data to store
*
* Return value:
*   - if succeeded, returns an iterator to the data
*	- if failed, returns the end of the list
*
* Comments: 
*	- User should compare the return value to the end of the list to determine
*	  if function succeeded.
*   - In case of invalid sorted list - undefined behaviour
*/
sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data);

/*---------------------------------------------------------------------------*/
/* SortedListRemove:
*   - removes an element from the sorted list.
* 
* Args:
*   - iter - iterator to the element to remove
* 
* Return value:
*	- an iterator to the next element
*
* Comments: 
*   - if the end of the list is given - undefined behavior.
*/
sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter);

/*---------------------------------------------------------------------------*/
/* SortedListPopFront:
*   - removes an element from the beginning of linked list.
* 
* Args:
*	- sorted_list - pointer to sorted list given by user
* 
* Return value:
*	- the data in the popped element
*
* Comments: 
*   - if sorted list is empty - undefined behavior.
*/
void *SortedListPopFront(sorted_list_t *sorted_list);

/*---------------------------------------------------------------------------*/
/* SortedListPopBack:
*   - removes an element from the end of linked list.
* 
* Args:
*	- sorted_list - pointer to sorted list given by user
* 
* Return value:
*	- the data in the popped element
*
* Comments: 
*   -if sorted list is empty - undefined behavior.
*/
void *SortedListPopBack(sorted_list_t *sorted_list);

/*---------------------------------------------------------------------------*/
/* SortedListSize:
*   - counts the number of elements in the sorted list.
* 
* Args:
*   - sorted_list - pointer to sorted list
*  
* Return Value:
*   - number of elements in the sort list         
*/
size_t SortedListSize(const sorted_list_t *sorted_list);

/*---------------------------------------------------------------------------*/
/* SortedListFind:
*   - finds requested data in a given list.
* 
* Args:
*   - sorted_list - pointer to sorted list
*   - to_find - the data given by user, to be searched for in the list
*
* Return Value: 
*	- if succeeded, returns iterator to the first element matched
*	- if failed, returns the iterartor "to". 
*
* Comments: 
*	- User should compare the return value to the end of the list, to determine
*	  whether function succeeded.
*/
sorted_list_iter_t SortedListFind(sorted_list_t *sorted_list,
								  sorted_list_iter_t from,
								  sorted_list_iter_t to,
								  void *to_find);

/*---------------------------------------------------------------------------*/
/* SortedListFindIf:
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
sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, 
									sorted_list_iter_t to,
									sorted_list_is_match_func_t is_match, 
									void *param);

/*---------------------------------------------------------------------------*/
/* SortedListForEach:
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
*   - do_action - should not impact the checked data (undefined behaviour)
*/
int SortedListForEach(sorted_list_iter_t from, 
					  sorted_list_iter_t to, 
					  sorted_list_do_action_func_t do_action, 
					  void *param);		  

/*---------------------------------------------------------------------------*/
/* SortedListMerge:
*   - merge two sorted lists
* 
* Args:
*   dest - pointer to sorted list given by user.
*   src - pointer to sorted list given by user.
*
* Comments: 
*   - in case of invalid sorted list - undefined behaviour
*   - Pointers to lists must be different
*   - Lists must be sorted by the same is_before function
*   - Params of both lists must be the same
*/
void SortedListMerge(sorted_list_t *dest, sorted_list_t *src);

#endif /* ILRD_SL_LIST_H */
