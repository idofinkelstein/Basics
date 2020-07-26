#include <stdio.h>
#include <stdlib.h>

#include "recursion.h"






int Fibonacci(int element_index)
{
	if (element_index < 2)
	{
		return 1;
	}

	return (Fibonacci(element_index - 1) + Fibonacci(element_index - 2));
}

int Fibonacci2(int element_index)
{
	int prev = 1;
	int prevprev = 0;
	int res = 0;

	if (element_index < 2)
	{
		return 1;
	}
	
	while (element_index)
	{

		res = prev + prevprev;
		prevprev = prev;	
		prev = res;
		
		--element_index;
	}

	return res;
}

node_t *Flip2(node_t *head)
{
	 node_t *curr = head;
	
	curr = head->next;
	
	if(head == NULL)
	{
		return head;
	}
	


	return Flip2(head->next);

	head->next = curr;

}

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

size_t StrLen(const char *str)
{
	size_t count = 0;

	if (*str == '\0')
	{
		return (count);
	}
	
	return ++count + StrLen(str + 1);	
}

	
int StrCmp(const char *str1, const char *str2)
{
	if (*str2 != *str1 || *str2 == '\0')
	{
		return (*str1 - *str2);
	}

	return StrCmp(str1 + 1, str2 + 1);
}

char *StrCpy(char *dest, const char *src)
{
	*dest = *src;

	if (*src == '\0')
	{
		 return(dest);		
	}

	StrCpy(dest + 1, (char*)src + 1);

	return dest;	
}

char *StrCat(char *dest, const char *src)
{	
	if (*dest != '\0')
	{
		StrCat(dest + 1, (char*)src);
		return dest;
	}

	else if (*src != '\0')
	{

		*dest = *src;
		StrCat(dest + 1, (char*)src + 1);

	}

	return dest;	
}

node_t *CreateNode(node_t *node)
{
	node = (node_t*)malloc(sizeof(node_t));

	if (NULL == node)
	{
		return (NULL);
	}
	
	return (node);
}

void SListDestroy(node_t *head)
{
	node_t *temp = head;

	while(temp != NULL)
	{
		temp = temp->next;
				
		free(head);
		
		head = temp;
	}
}


