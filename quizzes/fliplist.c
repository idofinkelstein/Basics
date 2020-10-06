#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node node_t;

void SListDestroy(node_t *head);
node_t *CreateNode(node_t *node);
void FlipTest(void);
node_t *FlipList(node_t *node);
void SwapBytes(char *byte1, char *byte2, size_t n_bytes);
void Reverse(char *str, size_t len);
void ReverseStr(char *str);

struct node
{
	node_t *next;
	void *data;
};

int main()
{
	char str[] = "hello world";

	ReverseStr(str);

	FlipTest();

	puts(str);
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

	curr = FlipList(curr);

	/*while (curr)
	{
		printf("%d ", *(int*)curr->data);
		curr = curr->next;
	}*/
	puts("");

	SListDestroy(curr);

}

node_t *FlipList(node_t *node)
{
	node_t *curr = NULL;

	if (node == NULL || node->next == NULL)
	{
		return node;
	}
	
	curr = FlipList(node->next);

	node->next->next = node;
	node->next = NULL;

	return (curr);
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

void Reverse(char *str, size_t len)
{
	if (len < 2)
	{
		return;
	}

	SwapBytes(str,str + len - 1, 1);

	Reverse(str + 1, len - 2);-
}

void ReverseStr(char *str)
{
	size_t len = strlen(str);

	Reverse(str, len);
}

void SwapBytes(char *byte1, char *byte2, size_t n_bytes)
{
	char temp = 0;

	while (n_bytes--)
	{
		temp = *byte1; 
   	 	*byte1++ = *byte2;
    	*byte2++ = temp;
	}
}
