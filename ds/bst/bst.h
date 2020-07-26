#ifndef ILRD_BST_H
#define ILRD_BST_H

#include <stddef.h>	/* size_t */


/*version 1.1  Remove function second input is changed from void * to bst_iter_t  
and changed comments regarding insert, prev, next, end and begin and iter
typedef */
/* version 1.2: changes Remove input arg, edited typedef */
/* version 1.3 changed comment regarding cmp function and typedef */


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
* The function is in O(1) complexity
*/
bst_t *BSTtCreate(bst_cmp_func_t cmp, void *param);

/*---------------------------------------------------------------------------*/
/* BSTDestroy:
*   - destroys the tree.
*
* Args:
*   - bst - pointer to the tree to be destroyed
*
* The function is in O(n) complexity
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
* The function is in O(n) complexity
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
* The function is in O(1) complexity   
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
* The function is in O(n) complexity
*/
bst_iter_t BSTInsert(bst_t *bst, void *data);

/*---------------------------------------------------------------------------*/
/* BSTRemove:
*   - removes an element from the tree.
* 
* Args:
*   - bst - pointer to bst
*   - data - data to remove
*
* Comments: 
*   - if the end of the tree is given - undefined behavior.
*
* The function is in O(n) complexity
*/
void BSTRemove(bst_iter_t iter);

/*---------------------------------------------------------------------------*/
/* BSTBegin:
*   - returns an iterator to the first element in the tree.
*
* Args:
*   - bst - pointer to the tree
*
* Return Value:
*   - an iterator to the smallest element in the tree acording to he bst's cmp
*     function logic
*
* The function is in O(height) complexity
*/
bst_iter_t BSTBegin(const bst_t *bst);

/*---------------------------------------------------------------------------*/
/* BSTEnd
*   - returns an iterator to the end of the list
*
* Args:
*	- bst - pointer to the tree
*
* Return value:
*   - an iterator to the next of the largest element in the tree acording to
*     the bst's cmp function logic
*
* The function is in O(1) complexity
*/
bst_iter_t BSTEnd(const bst_t *bst);

/*---------------------------------------------------------------------------*/
/* BSTPrev
*   - returns an iterator to the next bigest element to the iterator given by
*     the user
*
* Args:
*   - iter - iterator to get the element after
*
* Return value:
*   - an iterator to the next bigest element to the iterator given.
*
* Comments: 
*   - in case of invalid iterator given - undefined behavior.
*
* The function is in O(1) complexity
*/
bst_iter_t BSTPrev(bst_iter_t iter);

/*---------------------------------------------------------------------------*/
/* BSTNext
*   - returns an iterator to the next smallest element to the iterator given
*     by the user
*
* Args:
*   - iter - iterator to get the element after
*
* Return value:
*   - an iterator to the next smallest element to the iterator given.
*
* Comments: 
*   - in case of invalid iterator given - undefined behavior.
*
* The function is in O(1) complexity
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
* The function is in O(1) complexity
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
* The function is in O(1) complexity
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
* The function is in O(n) complexity
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
* The function is in O(n) complexity
*/
int BSTForEach(bst_iter_t from, bst_iter_t to, 
				bst_do_action_func_t do_action ,void *param);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_BST_H */
