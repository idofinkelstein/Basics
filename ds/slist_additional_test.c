/********************************
File name: slist_addition_test.c
Author: Ido Finkelstein
Reviewer: Rita Lempert
Date: 15/6/2020
*********************************/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

#include "slist_addition.h"

/* unit-test functions declaration */
void FlipTest(void);
void HasLoopTest(void);
void FindIntersectionTest(void);

/* utility functions declaration */
void SListDestroy(node_t *head);
node_t *CreateNode(node_t *node);

int main()
{
	FlipTest();
	HasLoopTest();
	FindIntersectionTest();

	return 0;
}

void FlipTest(void)
{
	node_t *node1 = NULL;
	node_t *node2 = NULL;
	node_t *node3 = NULL;
	node_t *node4 = NULL;
	node_t *node5 = NULL;
	node_t *node6 = NULL;
	node_t *node7 = NULL;
	node_t *node8 = NULL;
	node_t *curr = NULL;
	int x1 = 1;
	int x2 = 2;
	int x3 = 3;
	int x4 = 4;
	int x5 = 5;
	int x6 = 6;
	int x7 = 7;
	int x8 = 8;

	node1 = CreateNode(node1);
	node2 = CreateNode(node2);
	node3 = CreateNode(node3);
	node4 = CreateNode(node4);
	node5 = CreateNode(node5);
	node6 = CreateNode(node6);
	node7 = CreateNode(node7);
	node8 = CreateNode(node8);

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = node7;
	node7->next = node8;
	node8->next = NULL;
	curr = node1;
	node1->data = &x1;
	node2->data = &x2;
	node3->data = &x3;
	node4->data = &x4;
	node5->data = &x5;
	node6->data = &x6;
	node7->data = &x7;
	node8->data = &x8;
	
	while (curr)
	{
		printf("%d ", *(int*)curr->data);
		curr = curr->next;
	}
	puts("");

	node1 = Flip(node1);

	while (node1)
	{
		printf("%d ", *(int*)node1->data);
		node1 = node1->next;
	}
	puts("");

	SListDestroy(node8);
}

void HasLoopTest(void)
{
	node_t *node1 = NULL;
	node_t *node2 = NULL;
	node_t *node3 = NULL;
	node_t *node4 = NULL;
	node_t *node5 = NULL;
	node_t *node6 = NULL;
	node_t *node7 = NULL;
	node_t *node8 = NULL;
	
	int x1 = 1;
	int x2 = 2;
	int x3 = 3;
	int x4 = 4;
	int x5 = 5;
	int x6 = 6;
	int x7 = 7;
	int x8 = 8;

	node1 = CreateNode(node1);
	node2 = CreateNode(node2);
	node3 = CreateNode(node3);
	node4 = CreateNode(node4);
	node5 = CreateNode(node5);
	node6 = CreateNode(node6);
	node7 = CreateNode(node7);
	node8 = CreateNode(node8);

	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = node6;
	node6->next = node7;
	node7->next = node8;
	node8->next = node3; /* start of loop */
	node1->data = &x1;
	node2->data = &x2;
	node3->data = &x3;
	node4->data = &x4;
	node5->data = &x5;
	node6->data = &x6;
	node7->data = &x7;
	node8->data = &x8;

	printf("%d\n", HasLoop(node1));

	free(node1);
	free(node2);
	free(node3);
	free(node4);
	free(node5);
	free(node6);
	free(node7);
	free(node8);
	
}

void FindIntersectionTest(void)
{
	node_t *res_node = NULL;
	node_t *node_a1 = NULL;
	node_t *node_a2 = NULL;
	node_t *node_a3 = NULL;
	node_t *node_a4 = NULL;
	node_t *node_a5 = NULL;
	node_t *node_a6 = NULL;
	node_t *node_a7 = NULL;
	node_t *node_a8 = NULL;
	node_t *node_b1 = NULL;
	node_t *node_b2 = NULL;
	node_t *node_b3 = NULL;
	node_t *node_b4 = NULL;
	node_t *node_b5 = NULL;
	node_t *node_b6 = NULL;
	node_t *node_b7 = NULL;
	node_t *node_b8 = NULL;
	int x1 = 1;
	int x2 = 2;
	int x3 = 3;
	int x4 = 4;
	int x5 = 5;
	int x6 = 6;
	int x7 = 7;
	int x8 = 8;

	node_a1 = CreateNode(node_a1);
	node_a2 = CreateNode(node_a2);
	node_a3 = CreateNode(node_a3);
	node_a4 = CreateNode(node_a4);
	node_a5 = CreateNode(node_a5);
	node_a6 = CreateNode(node_a6);
	node_a7 = CreateNode(node_a7);
	node_a8 = CreateNode(node_a8);
	node_b1 = CreateNode(node_b1);
	node_b2 = CreateNode(node_b2);
	node_b3 = CreateNode(node_b3);
	node_b4 = CreateNode(node_b4);
	node_b5 = CreateNode(node_b5);
	node_b6 = CreateNode(node_b6);
	node_b7 = CreateNode(node_b7);
	node_b8 = CreateNode(node_b8);

	node_a1->next = node_a2;
	node_a2->next = node_a3;
	node_a3->next = node_a4;
	node_a4->next = node_a5;
	node_a5->next = node_a6;
	node_a6->next = node_a7;
	node_a7->next = node_a8; /* this node is the intersection node */
	node_a8->next = NULL;
	node_b1->next = node_b2;
	node_b2->next = node_b3;
	node_b3->next = node_b4;
	node_b4->next = node_b5;
	node_b5->next = node_b6;
	node_b6->next = node_b7;
	node_b7->next = node_b8;
	node_b8->next = node_a7; 
	node_a1->data = &x1;
	node_a2->data = &x2;
	node_a3->data = &x3;
	node_a4->data = &x4;
	node_a5->data = &x5;
	node_a6->data = &x6;
	node_a7->data = &x7;
	node_a8->data = &x8;
	node_b1->data = &x1;
	node_b2->data = &x2;
	node_b3->data = &x3;
	node_b4->data = &x4;
	node_b5->data = &x5;
	node_b6->data = &x6;
	node_b7->data = &x7;
	node_b8->data = &x8;

	res_node = FindIntersection(node_a1, node_b1);

	if(res_node)
	{
		printf("%d\n", *(int*)res_node->data);
	}
	else
	{
		puts("no intersection found");
	}

	SListDestroy(node_a1);

	node_b8->next = NULL; /* was freed because of intersection */
	
	SListDestroy(node_b1);

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
