/***********************
File name: dlist.c
Author: Ido Finkelstein
Reviewer: Janna Torbilo
Date: 19/6/2020
************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h>

#include "dlist.h"

/* management structure */
struct dlist
{
	struct dlist_node *head;
    struct dlist_node *tail;
};

/* node structure */
struct dlist_node
{
    void *data;
    struct dlist_node *next;
    struct dlist_node *prev;
};

dlist_t *DListCreate(void)
{
	dlist_t *list = (dlist_t*)malloc(sizeof(dlist_t));
	dlist_iter_t start_dummy = NULL;
	dlist_iter_t end_dummy = NULL;

	if (NULL == list)
	{
		return (NULL);
	}

	start_dummy = (dlist_iter_t)malloc(sizeof(struct dlist_node));

	if (NULL == start_dummy)
	{
		free(list);
		list = NULL;

		return (NULL);
	}

	end_dummy = (dlist_iter_t)malloc(sizeof(struct dlist_node));

	if (NULL == end_dummy)
	{
		free(list);
		free(start_dummy);

		list = NULL;
		start_dummy = NULL;

		return (NULL);
	}	

	start_dummy->prev = NULL;
	end_dummy->next = NULL;

	start_dummy->data = (void*)0xFEE1DEAD;
	end_dummy->data = (void*)0xFEE1DEAD;

	start_dummy->next = end_dummy;
	end_dummy->prev = start_dummy;

	list->head = start_dummy;
	list->tail = end_dummy;

	return (list);
}

void DListDestroy(dlist_t *dlist)
{
	dlist_iter_t curr = dlist->head;

	assert(dlist);

	while(curr != NULL)
	{
		curr = curr->next;
		free(dlist->head);
		dlist->head = curr;
	}

	free(dlist);
	dlist = NULL;
}

dlist_iter_t DListBegin(const dlist_t *dlist)
{
	assert(dlist);

	return (dlist->head->next);
}

dlist_iter_t DListEnd(const dlist_t *dlist)
{
	assert(dlist);

	return (dlist->tail);
}

dlist_iter_t DListNext(const dlist_iter_t iter)
{
	assert(iter);

	return (iter->next);
}

dlist_iter_t DListPrev(const dlist_iter_t iter)
{
	assert(iter);

	return (iter->prev);
}

void *DListGetData(dlist_iter_t iter)
{
	assert(iter);

	return (iter->data);
}

void DListSetData(dlist_iter_t iter, void *data)
{
	assert(iter);

	iter->data = data;
}

int DListIterIsEqual(const dlist_iter_t iter1, const dlist_iter_t iter2)
{
	assert(iter1);
	assert(iter2);

	return (iter1 == iter2);
}

int DListIsEmpty(const dlist_t *dlist)
{
	assert(dlist);
	
	return(dlist->head->next == DListEnd(dlist));
}

dlist_iter_t DListInsert(dlist_t *dlist, dlist_iter_t where, void *data)
{
	dlist_iter_t new = (dlist_iter_t)malloc(sizeof(struct dlist_node));

	assert(dlist);
	assert(where);

	if (NULL == new)
	{
		return (DListEnd(dlist));
	}

	new->next = where;
	new->prev = DListPrev(where);

	where->prev->next = new;
	where->prev = new;

	new->data = (void*)data;

	return (new);
}

dlist_iter_t DListRemove(dlist_iter_t iter)
{
	dlist_iter_t temp = DListNext(iter);

	assert(iter);

	iter->next->prev = DListPrev(iter);
	iter->prev->next = DListNext(iter);

	free(iter);
	iter = NULL;

	return (temp);
}

dlist_iter_t DListPushFront(dlist_t *dlist, void *data)
{
	assert(dlist);

	return (DListInsert(dlist, DListBegin(dlist), data));
}

dlist_iter_t DListPushBack(dlist_t *dlist, void *data)
{
	assert(dlist);

	return (DListInsert(dlist, DListEnd(dlist), data));
}

void *DListPopFront(dlist_t *dlist)
{
	void *temp_data = DListGetData(DListBegin(dlist));

	assert(dlist);

	DListRemove(DListBegin(dlist));	
	
	return (temp_data);
}

void *DListPopBack(dlist_t *dlist)
{
	void *temp_data = DListGetData(DListPrev(DListEnd(dlist)));

	assert(dlist);

	DListRemove(DListPrev(DListEnd(dlist)));
		
	return (temp_data);
}

size_t DListSize(const dlist_t *dlist)
{
	dlist_iter_t curr = DListBegin(dlist);
	size_t count = 0;

	assert(dlist);

	while (curr != DListEnd(dlist))
	{
		++count;
		curr = DListNext(curr);
	}

	return (count);
}

dlist_iter_t DListFind(const dlist_iter_t from, 
                       const dlist_iter_t to,
					   dlist_is_match_func_t is_match, 
                       void *param)
{
	dlist_iter_t curr = from;

	assert(from);
	assert(to);

	while (!DListIterIsEqual(curr, to))
	{
		if (is_match(curr->data, param))
		{
			return (curr);
		}

		curr = curr->next;
	}
	
	return (to);	
}

int DListForEach(dlist_iter_t from, 
                 const dlist_iter_t to, 
				 dlist_do_action_func_t do_action, 
                 void *param)
{
	dlist_iter_t curr = from;
	int do_action_status = 0;

	assert(from);
	assert(to);

	while (!DListIterIsEqual(curr, to) && !do_action_status)
	{
		do_action_status = do_action(curr->data, param);

		curr = DListNext(curr);	
	}	

	return (do_action_status);
}

dlist_iter_t DListSplice(dlist_iter_t from, dlist_iter_t to, dlist_iter_t where)
{
	dlist_iter_t temp = DListPrev(from);

	assert(from);
	assert(to);
	assert(from != to);
	assert(where);

	/* reconnects wires */
	where->prev->next = from;
	to->prev->next = where;

	from->prev->next = to;
	from->prev = DListPrev(where);

	where->prev = DListPrev(to);
	to->prev = temp;

	return (DListPrev(where));
}
