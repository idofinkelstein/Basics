/***********************
File name: slist.c
Author: Ido Finkelstein
Reviewer: Rita Lempert
Date: 13/6/2020
************************/


#include <stdlib.h> /* malloc, free */
#include <assert.h>

#include "slist.h"
/*
typedef struct slist_node* slist_iter_t;  
typedef struct slist slist_t; 
*/

struct slist
{
	struct slist_node *head;
	struct slist_node *tail;
};

struct slist_node
{
	void *data;
	struct slist_node *next;
};


slist_t *SListCreate(void)
{
	slist_t *list =(slist_t*)malloc(sizeof(slist_t));
	slist_iter_t dummy = NULL;

	if (NULL == list)
	{
		return (NULL);
	}

	dummy = (slist_iter_t)malloc(sizeof(struct slist_node));

	if (NULL == dummy)
	{
		free(list);
		return (NULL);
	}
	
	list->head = dummy;
	list->tail = dummy;

	dummy->data = NULL;
	dummy->next = NULL;

	return(list);
}

void SListDestroy(slist_t *slist)
{
	slist_iter_t temp = slist->head;

	assert(slist);

	while(temp != NULL)
	{
		temp = temp->next;
		free(slist->head);
		slist->head = temp;
	}

	free(slist);
}

slist_iter_t SListBegin(const slist_t *slist)
{
	assert(slist);

	return (slist->head);
}

slist_iter_t SListEnd(const slist_t *slist)
{
	assert(slist);
	
	return (slist->tail);
}

slist_iter_t SlistNext(const slist_iter_t iter)
{
	assert(iter);

	return(iter->next);
}

int SListIterIsEqual(const slist_iter_t iter1, const slist_iter_t iter2)
{
	assert(iter1);
	assert(iter2);

	return (iter1 == iter2);
}

int SListIsEmpty(const slist_t *slist)
{
	assert(slist);
	
	return (slist->head == slist->tail);
}

void *SListGetData(const slist_iter_t iter)
{
	assert(iter);

	return(iter->data);
}

void SlistSetData(slist_iter_t iter, void *data)
{
	assert(iter);

	iter->data = data;
}

slist_iter_t SListInsert(slist_t *slist, slist_iter_t where, void *data)
{
	slist_iter_t new =(slist_iter_t)malloc(sizeof(struct slist_node));
	
	assert(slist);
	assert(where);

	if (NULL == new)
	{
		return (slist->tail);
	}

	*new = *where; /* duplicates where */
	where->next = new; 

	where->data = data;
	
	/* moves the tail in case insertion occurs in the end of
	   the list */
	if (SListIterIsEqual(where, slist->tail))
	{
		slist->tail = new;
	}
	
	return(where);

}

slist_iter_t SListInsertAfter(slist_t *slist, slist_iter_t where, void *data)
{
	slist_iter_t new = (slist_iter_t)malloc(sizeof(struct slist_node));

	assert(slist);
	assert(where);

	if (NULL == new)
	{
		return (slist->tail);
	}

	new->data = data;

	new->next = where->next;
	where->next = new;

	return (new);
}

slist_iter_t SListRemove(slist_t *slist, slist_iter_t iter)
{
	slist_iter_t temp = NULL;

	assert(slist);
	assert(iter);
	
	/* if iter points to tail - the list is empty or invalid
	   pointer, doesn't do anyhing */
	if (SListIterIsEqual(iter, slist->tail))
	{
		return (iter);
	}

	/* speacial cases - only one item in the list or the iterator
	   to be removed is the head of the list */
	if (SListIterIsEqual(iter, slist->head))
	{
		slist->head = slist->head->next;
		free(iter);

		return (slist->head);
	}
	
	/* in case node to be removed is the last valid node,
	   tail needs to be decremented once */
	if(SListIterIsEqual(iter->next, slist->tail))
	{
		slist->tail = iter;
	}

	temp = iter->next;
	*iter = *iter->next;

	free(temp);

	return (iter);
}

size_t SListCount(const slist_t *slist)
{
	slist_iter_t util = SListBegin(slist);
	size_t count = 0;

	assert(slist);

	while (util != SListEnd(slist))
	{
		++count;
		util = SlistNext(util);
	}

	return (count);
}

slist_iter_t SListFind(const slist_iter_t from, 
                       const slist_iter_t to,
					   slist_is_match_func_t is_match, 
                       void *param)
{
	slist_iter_t curr = from;

	assert(from);
	assert(to);

	while (!SListIterIsEqual(curr, to))
	{
		if (1 == is_match(curr->data, param))
		{
			return (curr);
		}

		curr = curr->next;
	}
	
	return (to);	
}

int SListForEach(const slist_iter_t from, 
                 const slist_iter_t to, 
				 slist_do_action_func_t do_action, 
                 void *param)
{
	slist_iter_t curr = from;

	assert(from);
	assert(to);

	while (!SListIterIsEqual(curr, to))
	{
		if (NULL == curr)	
		{
			return do_action(curr->data, param);
		}

		do_action(curr->data, param);
	
		curr = SlistNext(curr);	
	}

	return 0;
}

void SListAppend(slist_t *dest, slist_t *src)
{
	assert(dest);
	assert(src);

	/* copies the content of node pointed to by src->head to the 
	   node pointed to by dest->tail */
	*dest->tail = *src->head; 

	dest->tail = src->tail;

	src->tail = src->head;

	src->head->data = NULL;
	src->head->next = NULL;
	 
}

