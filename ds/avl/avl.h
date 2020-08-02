/********************************
File name: avl.h
Author: Ido Finkelstein
Reviewer: Guy Chen
Date: 1/8/2020
*********************************/

/*
An AVL tree is a binary search tree which has the following properties:
1. The sub-trees of every node differ in height by at most one.
2. Every sub-tree is an AVL tree.

Find, insertion, and remove are O(log n), where n is the number of nodes in the tree.
*/


#ifndef ILRD_AVL_H
#define ILRD_AVL_H

#include <stddef.h>	/* size_t */


/*version 1.0  mentor approval */


typedef struct avl avl_t;

/* typedefs of functions to be implemented by the user */

/* compare function, returns whether data1 is bigger, smaller or equals to
 data2 */
typedef int (*avl_cmp_func_t)(const void *data1, const void *data2, void *param);
/* return value is status - 0 for success, 1 for fail */
typedef int (*avl_do_action_func_t)(void *data, void *param);

/*---------------------------------------------------------------------------*/
/* AVLCreate:
*   - creates an empty tree.
*
* Args:
	- cmp - pointer to function that defines how to compare two items
*	- param - parameters given by user to be sent into callback functions
*
* Return Value:
*   - pointer to the tree.
*
*/
avl_t *AVLCreate(avl_cmp_func_t cmp, void *param);

/*---------------------------------------------------------------------------*/
/* AVLDestroy:
*   - destroys the tree.
*
* Args:
*   - avl - pointer to the tree to be destroyed
*
*/
void AVLDestroy(avl_t *avl);

/*---------------------------------------------------------------------------*/
/* AVLSize:
*   - counts the number of elements in the tree.
* 
* Args:
*   - avl - pointer to the tree
*  
* Return Value:
*   - number of elements in the tree
*
*/
size_t AVLSize(const avl_t *avl);

/*---------------------------------------------------------------------------*/
/* AVLIsEmpty:
*   - checks if the tree is empty or not
* 
* Args:
*   - avl - pointer to tree given by user
*  
* Return boolean Value:
*   1 - empty (TRUE)
*   0 - not empty. (FALSE)
*
*/
int AVLIsEmpty(const avl_t *avl);

/*---------------------------------------------------------------------------*/
/* AVLInsert:
* - inserts new element to the tree.
* 
* Args:
*   - avl - pointer to tree
*   - data - data to be inserted
*
* Return value:
*   - if succeeded, returns 0
*	- if failed 1
*   
* Comments: 
*	- User should check return value to determine
*	  if function succeeded.
*
*/
int AVLInsert(avl_t *avl, void *data);

/*---------------------------------------------------------------------------*/
/* AVLRemove:
*   - removes an element from the tree.
* 
* Args:
*   - avl - pointer to tree
*   - data - data to be removed
*
*/
void AVLRemove(avl_t *avl, void *data);

/*---------------------------------------------------------------------------*/
/* AVLFind:
*   - finds data stored in tree. 
* 
* Args:
*   - avl - pointer to the tree
*	- data - data to find (may be only part of data stored)
*
* Return Value: 
*	- if succeeded, returns pointer to the matched element
*	- if failed, returns NULL. 
*
*/
void *AVLFind(const avl_t *avl, const void *data);

/*---------------------------------------------------------------------------*/
/* AVLForEach:
*   - performes action in a function given by the user on all tree elements, traverse is in-order.
*
* Args:
*	- avl - pointer to the tree
*   - do_action - function pointer to the action to do
*	- param - parameter to pass to action function (optional)
*   
* Return value:
*   - 0 - the action succeeds for all the elements in the range
*   - otherwise, the action failed and returns the status returned 
*     from the do_action function  .
*
* Comments: 
*	- Range includes all elements in the tree.
*	- do_action is a function to be implemeneted by the user. See signature 
*	  in typedef.
*
*/
int AVLForEach(avl_t *avl, avl_do_action_func_t do_action ,void *param);

/* debug functions - not included in the API */
int IsBalanced(avl_t *avl);
void ChooseTraversalOrder(avl_t *avl, int num);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_AVL_H */
