/**********************
Author: Ido Finkelstein
File name: recursion.h
Reviewer: Hila Pilo
Date: 26/7/2020
***********************/

#ifndef __RECURSION_H__
#define __RECURSION_H__

#include "stack.h"

typedef struct node
{
	void *data;
	struct node *next;
} node_t;


void SListDestroy(node_t *head);
node_t *CreateNode(node_t *node);
int Fibonacci(int element_index);
int Fibonacci2(int element_index);
node_t *Flip(node_t *head);
size_t StrLen(const char *str);
int StrCmp(const char *str1, const char *str2);
char *StrCpy(char *dest, const char *src);
char *StrCat(char *dest, const char *src);
char *StrStr(const char *haystack, const char *needle);
int StrnCmp(const char *str1, const char *str2, size_t n);
void SortedInsert(stack_t *stack, int *num);
void SortStack(stack_t *stack);


#endif /* __RECURSION_H__ */
