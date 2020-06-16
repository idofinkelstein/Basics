/***********************
File name: slist_addition.c
Author: Ido Finkelstein
Reviewer: Rita Lempert
Date: 15/6/2020
************************/

#include <stdlib.h>

#include "slist_addition.h" /* size_t */

size_t ListSize(node_t *head);

node_t *Flip(node_t *head)
{
	node_t *curr = head->next;
	node_t *next = head->next;

	head->next = NULL;
	/* the idea is to keep 3 pointers - one for the current node, one for the
	   previous node and one for the next node. (head is the previous) */
	while(curr)
	{
		/* make sure i'm not incrementing a NULL pointer */
		if (next)
		{
			next = curr->next;
		}
		curr->next = head;
		head = curr;
		curr = next;
	}

	return (head);
}

int HasLoop(const node_t *head)
{
	node_t *fast = (node_t*)head; /* traverses loop at fast pace */
	node_t *slow = (node_t*)head; /* traverses loop at slow pace */

	/* this loop increment both node pointers, if the list contains loop - 
	   they will meet at some point */
	while(fast)
	{
		/*  make sure i'm not incrementing a NULL pointer,
		    perhaps the list has end  */
		if(fast->next)
		{
			fast = fast->next->next;
		}
		else
		{
			return 0;
		}

		slow = slow->next;

		if (fast == slow)
		{
			return 1;
		}
	}

	return 0;
}

node_t *FindIntersection(node_t *head1, node_t *head2)
{
	node_t *curr1 = head1;
	node_t *curr2 = head2;
	node_t *large = NULL;
	node_t *little = NULL;
	size_t size1 = 0;
	size_t size2 = 0;
	size_t diff = 0;

	/* obtains the size of list1 */
	size1 = ListSize(curr1);

	/* obtains the size of list2 */
	size2 = ListSize(curr2);

	/* checks who is bigger */
	if (size1 > size2)
	{
		diff = size1 - size2;
		little = curr2;
		large = curr1;
	}
	else
	{
		diff = size2 - size1;
		little = curr1;
		large = curr2;
	}

	/* increment the smaller list to start from the same position as
	   the large one */
	while (diff)
	{
		large = large->next;
		--diff;
	}
	
	/* if the two nodes are identical - returns one of them */
	while (large)
	{
		if (large == little)
		{
			return (large);
		}

		large = large->next;
		little = little->next;
	}
	
	return (NULL);
}

size_t ListSize(node_t *head)
{
	size_t size = 0;
	
	while (head)
	{
		++size;
		head = head->next;
	}
	
	return (size);
}
