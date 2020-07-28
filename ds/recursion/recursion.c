/**********************
Author: Ido Finkelstein
File name: recursion.c
Reviewer: Hila Pilo
Date: 26/7/2020
***********************/


#include <stdio.h>  /* malloc, free */
#include <stdlib.h> /* printf */

#include "recursion.h"

int Fibonacci(int element_index)
{
	if (element_index < 1)
	{
		return 0;
	}

	else if (element_index < 2)
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

	if (element_index < 1)
	{
		return 0;
	}
	else if (element_index <= 2)
	{
		return 1;
	}
	
	while (element_index - 1)
	{
		res = prev + prevprev;
		prevprev = prev;	
		prev = res;
		
		--element_index;
	}

	return (res);
}

node_t *Flip(node_t *node)
{
	node_t *next_node = NULL;

    if (node == NULL || node->next == NULL)
    {
        return(node);
    }
    
    next_node = Flip(node->next);
    node->next->next = node;

    node->next = NULL;

    return(next_node);
}


size_t StrLen(const char *str)
{
	size_t count = 0;

	if (*str == '\0')
	{
		return (count);
	}
	
	return (++count + StrLen(str + 1));	
}


int StrCmp(const char *str1, const char *str2)
{
	if (*str2 != *str1 || *str2 == '\0')
	{
		return (*str1 - *str2);
	}

	return (StrCmp(str1 + 1, str2 + 1));
}

int StrnCmp(const char *str1, const char *str2, size_t n)
{
	if ((*str2 != *str1 || *str2 == '\0') && n)
	{
		return (*str1 - *str2);
	}
	else if (!n)
	{
		return (*(str1 - 1) - *(str2 - 1));
	}

	return (StrnCmp(str1 + 1, str2 + 1, n - 1));
}

char *StrCpy(char *dest, const char *src)
{
	*dest = *src;

	if (*src == '\0')
	{
		 return (dest);		
	}

	StrCpy(dest + 1, (char*)src + 1);

	return (dest);	
}

char *StrCat(char *dest, const char *src)
{	
	if (*dest != '\0')
	{
		StrCat(dest + 1, (char*)src);
		return (dest);
	}

	else if (*src != '\0')
	{
		*dest = *src;
		StrCat(dest + 1, (char*)src + 1);
	}

	return (dest);	
}

char *StrStr(const char *haystack, const char *needle)
{
	size_t len = StrLen(needle);

	if (StrnCmp(haystack, needle, len) == 0)
	{
		return ((char*)haystack);
	}
	else if (*haystack == '\0')
	{
		return (NULL);
	}

	return (StrStr(haystack + 1, needle));
	
}

/* inserts elements to stack in a sorted way */
void SortedInsert(stack_t *stack, int *num) 
{ 
    int *temp = NULL;
     
    if (StackIsEmpty(stack) || *num > *(int *)StackPeek(stack)) 
    { 
        StackPush(stack, num);
        return; 
    } 

    temp = (int *)StackPeek(stack);
    StackPop(stack);

    SortedInsert(stack, num); 
    
    StackPush(stack, temp);

} 

/* sort a stack */
void SortStack(stack_t *stack)
{
    int *num = NULL;

    if (!StackIsEmpty(stack))
    {
        num = (int *)StackPeek(stack);
        StackPop(stack);

        SortStack(stack);

        SortedInsert(stack, num);
    }
   
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


