/*
Sorted List - List of sorted elements.

operations:
	Create - creates an empty list.
	Destroy - destroies the list.
	Size - returns the size of the list.
	IsEmpty - boolian function to indicate whether the list is empty or not.
	Insert - inserts new element to the list by keeping the right order.
	Remove - removes an element from the list.
	ForEach - Performs an operation on given range of nodes in the list.
	Find - Finds a position of a specific node.
	Find - Finds a position of a specific node by a specific criteria.
	Merge - merged to list and sorts them on the way.דש
*/

#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

typedef struct sorted_list_node* sorted_list_iter_t;

typedef struct sorted_list sorted_list_t;

typedef int (*dlist_is_match_func_t)(const void *data, void *param);

typedef int (*dlist_do_action_func_t)(void *data, void *param);


sorted_list_iter_t SortedListCreate(is_before__func_t is_before);

void SortedListDestroy(sorted_list_t sorted_list);

size_t SortedListSize(sorted_list_t sorted_list);

sorted_list_iter_t SortedListBegin(sorted_list_t sorted_list);

sorted_list_iter_t SortedListEnd(sorted_list_t sorted_list);

sorted_list_iter_t SortedListNext(sorted_list_t sorted_list);

sorted_list_iter_t SortedListPrev(sorted_list_t sorted_list);

int SortedListIsEqual(sorted_list_iter_t iter1, sorted_list_iter_t iter2);

void *SortedListGetData(sorted_list_iter_t iter);

void *SortedListPopFront(sorted_list_t sorted_list);

void *SortedListPopBack(sorted_list_t sorted_list);

int SortedListIsEmpty(sorted_list_t sorted_list);

sorted_list_iter_t SortedListInsert(sorted_list_t sorted_list);

sorted_list_iter_t SortedListRemove(sorted_list_t sorted_list);

sorted_list_iter_t SortedListForEach(sorted_list_iter_t from,
									 sorted_list_iter_t to,
									 sorted_list_do_action_func_t do_action,
									 void *param);

sorted_list_iter_t SortedListFind(sorted_list_iter_t from,
								  sorted_list_iter_t to,
								  is_before__func_t is_before);

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from,
								  sorted_list_iter_t to,
								  is_before__func_t is_before);

sorted_list_iter_t SortedListMerge(sorted_list_t sorted_list);


#endif /* __SORTED_LIST_H__ */
