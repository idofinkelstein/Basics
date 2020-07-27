#ifndef ILRD_BST_H
#define ILRD_BST_H

#include <stddef.h>	/* size_t */


/*version 1.1  Remove function second input is changed from void * to bst_iter_t  
and changed comments regarding insert, prev, next, end and begin and iter
typedef */
/* version 1.2: changes Remove input arg, edited typedef */
/* version 1.3 changed comment regarding cmp function and typedef */
/* version 1.4: removed all complexity mentions, updated notes for, remove,
 prev, next, begin, end*/


/* typedefs for the bst and the iterator  */

typedef struct bst_node bst_node_t;
typedef struct iterator
{
    struct bst_node *node;
}bst_iter_t;

typedef struct bst bst_t;

/* typedefs of functions to be implemented by the user */

/* compare function, returns whether data1 is bigger, smaller or equals to
 data2 */
typedef int (*bst_cmp_func_t)(const void *data1, const void *data2, void *param);
/* return value is status - 0 for success, 1 for fail */
typedef int (*bst_do_action_func_t)(void *data, void *param);

/*---------------------------------------------------------------------------*/
/* BSTCreate:
*   - creates an empty tree.
*
* Args:
	- cmp - pointer to function that defines how to compare to items
*	- param - parameters given by user to be sent into callback functions
*
* Return Value:
*   - pointer to the tree.
*
*/
bst_t *BSTtCreate(bst_cmp_func_t cmp, void *param);

/*---------------------------------------------------------------------------*/
/* BSTDestroy:
*   - destroys the tree.
*
* Args:
*   - bst - pointer to the tree to be destroyed
*
*/
void BSTDestroy(bst_t *bst);

/*---------------------------------------------------------------------------*/
/* BSTSize:
*   - counts the number of elements in the tree.
* 
* Args:
*   - bst - pointer to bst
*  
* Return Value:
*   - number of elements in the tree
*
*/
size_t BSTSize(const bst_t *bst);

/*---------------------------------------------------------------------------*/
/* BSTIsEmpty:
*   - checks if the bst is empty or not
* 
* Args:
*   - bst - pointer to bst given by user
*  
* Return boolean Value:
*   1 - empty (TRUE)
*   0 - not empty. (FALSE)
*
*/
int BSTIsEmpty(const bst_t *bst);

/*---------------------------------------------------------------------------*/
/* BSTInsert:
* - inserts new element to the tree.
* 
* Args:
*   - bst - pointer to bst
*   - data - data to be inserted
*
* Return value:
*   - if succeeded, returns an iterator to the data
*	- if failed, returns the end of the list
*   - no duplicates in the bst
*
* Comments: 
*	- in case of invalid iterator - undefined behavior.
*	- User should compare the return value to the end of the treee to determine
*	  if function succeeded.
*
*/
bst_iter_t BSTInsert(bst_t *bst, void *data);

/*---------------------------------------------------------------------------*/
/* BSTRemove:
*   - removes an element from the tree.
* 
* Args:
*   - iter - iterator to element to be removed
*
* Comments: 
*   - if the end of the tree is given as input - undefined behavior.
*
*/
void BSTRemove(bst_iter_t iter);

/*---------------------------------------------------------------------------*/
/* BSTBegin:
*   - returns an iterator to the first (smallest) element in the tree,
*     acordind to the order defined by the cmp function.
*
* Args:
*   - bst - pointer to the tree
*
* Return Value:
*   - an iterator to the first (smallest) element in the tree acording to the
*     order defined by the cmp function.
*
*/
bst_iter_t BSTBegin(const bst_t *bst);

/*---------------------------------------------------------------------------*/
/* BSTEnd
*   - returns an iterator to the end of the list. The prev on the BSTEnd is
*    defined as the largest item on the tree acordind to the order defined by
*    the cmp function.
*
* Args:
*	- bst - pointer to the tree
*
* Return value:
*   - an iterator to the next of the largest element in the tree acording to
*     the order defined by the cmp function.
*
*/
bst_iter_t BSTEnd(const bst_t *bst);

/*---------------------------------------------------------------------------*/
/* BSTPrev
*   - returns an iterator to the previous (smaller) element of the given input,
*    acordind to the order defined by the cmp function.
*
* Args:
*   - iter - iterator to get the element after
*
* Return value:
*   -an iterator to the previous (smaller) element of the given input,
*    acordind to the order defined by the cmp function.
*
* Comments: 
*   - in case of invalid iterator given - undefined behavior.
*   - prev of BSTBegin is undefined.
*
*/
bst_iter_t BSTPrev(bst_iter_t iter);

/*---------------------------------------------------------------------------*/
/* BSTNext
*   - returns an iterator to the next (bigger) element of the given input,
*    acordind to the order defined by the cmp function.
*
* Args:
*   - iter - iterator to get the element after
*
* Return value:
*   - an iterator to the next (bigger) element of the given input,
*    acordind to the order defined by the cmp function.
*
* Comments: 
*   - in case of invalid iterator given - undefined behavior.
*   - next of BSTEnd is undefined.
*
*/
bst_iter_t BSTNext(bst_iter_t iter);

/*---------------------------------------------------------------------------*/
/* BSTIterIsEqual
* - checks if two iterators are equal
*
* Args:
*   - iter1 - first iterator to compare
*   - iter2 - second iterator to compare 
*
* Return boolean value:
*   - 1 - equal (TRUE) 
*   - 0 - not equal (FALSE)
*
*/
int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2);

/*---------------------------------------------------------------------------*/
/* BSTGetData
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
*
*/
void *BSTGetData(bst_iter_t iter);

/*---------------------------------------------------------------------------*/
/* BSTFind:
*   - finds data stored in bst.
* 
* Args:
*   - bst - pointer to bst
*	- data - data to find
*
* Return Value: 
*	- if succeeded, returns iterator to the matched element
*	- if failed, returns the end of the tree. 
*
* Comments: 
*	- User should compare the return value to the end iterator, to determine
*	  whether function succeeded.
*
*/
bst_iter_t BSTFind(const bst_t *bst, const void *data);

/*---------------------------------------------------------------------------*/
/* BSTForEach:
*   - performes action in a function given by the user on all tree elements
*
* Args:
*   - from - iterator to the beginning of range
*   - to - iterator to the end of range
*   - do_action - function pointer to the action to do
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
*
*/
int BSTForEach(bst_iter_t from, bst_iter_t to, 
				bst_do_action_func_t do_action ,void *param);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_BST_H */
