/***********************
File name: sorted_list.c
Author: Ido Finkelstein
Reviewer: Tal Kornblum
Date: 24/6/2020
************************/

#include <stdlib.h> /* malloc, free, size_t */
#include <assert.h>

#include "sorted_list.h"

struct sorted_list
{
	dlist_t *dlist;
	sorted_list_is_before_func_t is_before; 
};

sorted_list_t *SortedListCreate(sorted_list_is_before_func_t is_before)
{
	sorted_list_t *list = (sorted_list_t*)malloc(sizeof(sorted_list_t));

	if (NULL == list)
	{
		return (NULL);
	}

	list->dlist = DListCreate();

	if (NULL == list->dlist)
	{
		free(list);
		list = NULL;

		return (NULL);
	}

	list->is_before = is_before;

	return (list);
}

void SortedListDestroy(sorted_list_t *sorted_list)
{
	assert(sorted_list);

	DListDestroy(sorted_list->dlist);

	free(sorted_list);
	sorted_list = NULL;
}

sorted_list_iter_t SortedListBegin(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t iter = {NULL};

	iter.internal_iter = DListBegin(sorted_list->dlist);

	assert(sorted_list);

	return (iter);
}

sorted_list_iter_t SortedListEnd(const sorted_list_t *sorted_list)
{
	sorted_list_iter_t iter = {NULL};

	iter.internal_iter = DListEnd(sorted_list->dlist);

	assert(sorted_list);

	return (iter);
}

sorted_list_iter_t SortedListNext(sorted_list_iter_t iter)
{
	assert(iter.internal_iter);

	iter.internal_iter = DListNext(iter.internal_iter);

	return (iter);	
}

sorted_list_iter_t SortedListPrev(sorted_list_iter_t iter)
{
	assert(iter.internal_iter);

	iter.internal_iter = DListPrev(iter.internal_iter);

	return (iter);	
}

void *SortedListGetData(sorted_list_iter_t iter)
{
	assert(iter.internal_iter);

	return (DListGetData(iter.internal_iter));
}

int SortedListIterIsEqual(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{
	assert(iter1.internal_iter);
	assert(iter2.internal_iter);

	return (DListIterIsEqual(iter1.internal_iter, iter2.internal_iter)); 
}

int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
	assert(sorted_list);

	return(DListIsEmpty(sorted_list->dlist));
}

sorted_list_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data) 
{
	sorted_list_iter_t new = {NULL};
	
	new = SortedListBegin(sorted_list);

	/* increments new node to the right place to keep it orderly */
	while (!SortedListIterIsEqual(new, SortedListEnd(sorted_list)) && 
		   !sorted_list->is_before(data, SortedListGetData(new)))
	{
		new = SortedListNext(new);
	}

	new.internal_iter = DListInsert(sorted_list->dlist,
									new.internal_iter,
									data);
	
	return (new);
}

sorted_list_iter_t SortedListRemove(sorted_list_iter_t iter)
{
	assert(iter.internal_iter);

	iter.internal_iter = DListRemove(iter.internal_iter);

	return (iter);
}

void *SortedListPopFront(sorted_list_t *sorted_list)
{
	assert(sorted_list);
	
	return (DListPopFront(sorted_list->dlist));
}

void *SortedListPopBack(sorted_list_t *sorted_list)
{
	assert(sorted_list);

	return (DListPopBack(sorted_list->dlist));
}

size_t SortedListSize(const sorted_list_t *sorted_list)
{
	assert(sorted_list);

	return (DListSize(sorted_list->dlist));
}

sorted_list_iter_t SortedListFind(sorted_list_t *sorted_list,
								  sorted_list_iter_t from,
								  sorted_list_iter_t to,
								  void *to_find)
{
	sorted_list_iter_t curr = from;

	assert(from.internal_iter);
	assert(to.internal_iter);

	while (!SortedListIterIsEqual(curr, to) &&
			sorted_list->is_before(SortedListGetData(curr), to_find))
	{
		curr = SortedListNext(curr);
	}
	
	if (!SortedListIterIsEqual(curr, to) &&
		!sorted_list->is_before(to_find, SortedListGetData(curr)))
	{
		return (curr);
	}
	
	return (to);	
}

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, 
									sorted_list_iter_t to,
									sorted_list_is_match_func_t is_match, 
									void *param)
{
	sorted_list_iter_t iter;

	assert(from.internal_iter);
	assert(to.internal_iter);

	iter.internal_iter = DListFind(from.internal_iter,
						 		   to.internal_iter,
						 		   is_match,
						 		   param);

	return (iter);
}

int SortedListForEach(sorted_list_iter_t from, 
					  sorted_list_iter_t to, 
					  sorted_list_do_action_func_t do_action, 
					  void *param)
{
	assert(from.internal_iter);
	assert(to.internal_iter);

	return (DListForEach(from.internal_iter,
						 to.internal_iter,
						 do_action,
						 param));
}

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	sorted_list_iter_t where = SortedListBegin(dest);
	sorted_list_iter_t to = SortedListBegin(src);
	sorted_list_iter_t from = SortedListBegin(src);

	assert(dest);
	assert(src);

	/* as long as both lists didn't reach end. */
	while (!SortedListIterIsEqual(from, SortedListEnd(src)) &&
		   !SortedListIterIsEqual(where, SortedListEnd(dest)))
	{
		from = to;
		
		/* as long as to->data is lesser than where->data this loop increments to */		
		while (!SortedListIterIsEqual(to, SortedListEnd(src))  &&
			   dest->is_before(SortedListGetData(to), SortedListGetData(where)))
		{
			to = SortedListNext(to);
		}
		
		/* if to and from are not the same node, splices the segment to dest list */  
		if (!SortedListIterIsEqual(from, to))
		{
			DListSplice(from.internal_iter, to.internal_iter, where.internal_iter);			
		}

		where  = SortedListNext(where);
	}

	/* if src list didn't reach end yet and dest does, splices the rest of 
	   src to dest. */
	if (!SortedListIterIsEqual(to, SortedListEnd(src)) &&
		SortedListIterIsEqual(where, SortedListEnd(dest)))
	{
		from = to;
		to = SortedListEnd(src);
		where = SortedListEnd(dest);

		DListSplice(from.internal_iter, to.internal_iter, where.internal_iter);
	}
}
