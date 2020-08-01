#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "avl.h"
#include "stack.h"



typedef struct avl_node avl_node_t;

struct avl_node
{
	void *data;
	avl_node_t *left;
	avl_node_t *right;
};

struct avl
{
	avl_node_t *root;
	avl_cmp_func_t cmp;
	void *param;
};


void DeleteNode(avl_node_t *node);
size_t GetSize(avl_node_t *node, size_t count);
void *RecursiveFind(const avl_t *avl, avl_node_t *node, const void *data);
avl_node_t *InsertNode(avl_t *avl, avl_node_t *node, void *data);
avl_node_t *CreateNode(avl_node_t *new, void *data);
size_t NodeHeight(avl_node_t *node);
size_t Max(size_t a, size_t b);
int Balance(avl_node_t *node);
avl_node_t *RightRotation(avl_node_t *root);
avl_node_t *RightLeftRotation(avl_node_t *root);
avl_node_t *LeftRotation(avl_node_t *root);
avl_node_t *LeftRightRotation(avl_node_t *root);

avl_t *AVLCreate(avl_cmp_func_t cmp, void *param)
{
	avl_t *avl = NULL;

	avl = (avl_t*)malloc(sizeof(avl_t));

	if (NULL == avl)
	{
		return (NULL);
	}

	avl->cmp = cmp;
	avl->param = param;
	avl->root = NULL;

	return (avl);
}

void AVLDestroy(avl_t *avl)
{
	avl_node_t *node = avl->root;

	if (!AVLIsEmpty(avl))
	{
		DeleteNode(node);	
	}

	free(avl);
}

int AVLIsEmpty(const avl_t *avl)
{
	assert(avl);

	return (avl->root == NULL);
}

size_t AVLSize(const avl_t *avl)
{
	size_t count = 0;
	avl_node_t *node = avl->root;

	if (!AVLIsEmpty(avl))
	{
		count = GetSize(node, count);	
	}

	return (count);
}

int AVLInsert(avl_t *avl, void *data)
{
	avl_node_t *node = avl->root;

	node = InsertNode(avl, node, data);

	printf("height = %ld\n", NodeHeight(node));
	printf("balance = %d\n", Balance(node));

	return (node == NULL);
}

void *AVLFind(const avl_t *avl, const void *data)
{

	avl_node_t *node = avl->root;

	assert(avl);

	if (!AVLIsEmpty(avl))
	{
		node = RecursiveFind(avl, node, data);
	}

	return (node);
}

void DeleteNode(avl_node_t *node)
{

	if (node->left != NULL)
	{	
		DeleteNode(node->left);
		node->left = NULL;		
	}

	if (node->right != NULL)
	{
		DeleteNode(node->right);
		node->right = NULL;
	}

	if (node != NULL)
	{
		printf("%d ",*(int*)node->data);
		free(node);
		node = NULL;
	}
}

size_t GetSize(avl_node_t *node, size_t count)
{
	if (node->left != NULL)
	{			
		count = GetSize(node->left, count);			
	}
	if (node->right != NULL)
	{
		count = GetSize(node->right, count);		
	}

		return ++count;	
}

void *RecursiveFind(const avl_t *avl, avl_node_t *node, const void *data)
{
	if (avl->cmp(node->data, data, NULL) != 0) 
	{
		if (avl->cmp(node->data, data, NULL) > 0 &&
		    node->left != NULL)
		{
			node = RecursiveFind(avl, node->left, data);
		}
		else if (avl->cmp(node->data, data, NULL) < 0 && 
				 node->right != NULL)
		{
			node = RecursiveFind(avl, node->right, data);
		}
		else
		{
			return (NULL);
		}	
	}
	
	return node;
}

avl_node_t *InsertNode(avl_t *avl, avl_node_t *node, void *data)
{
	avl_node_t *new = NULL;
	int root_swap = 0;

	if (node == NULL)
	{
		new = CreateNode(new, data);

		if (avl->root == NULL)
		{
			avl->root = new;
		}

		return (new);
	}

	if (avl->cmp(node->data, data, data) != 0)
	{
		if (avl->cmp(node->data, data, data) > 0)
		{
			node->left = InsertNode(avl, node->left, data);		
		}
		else
		{
			node->right = InsertNode(avl, node->right, data);
		}

		if (node == avl->root)
		{
			root_swap = !root_swap;
		}


		if (Balance(node) > 1)
		{			
			if (NodeHeight(node->left->left) >= NodeHeight(node->left->right))
			{
				node = RightRotation(node);
			}
			else
			{
				node = LeftRightRotation(node);
			}
		}
		else if (Balance(node) < -1)
		{
			if (NodeHeight(node->right->right) >= NodeHeight(node->right->left))
			{
				node = LeftRotation(node);
			}
			else
			{
				node = RightLeftRotation(node);
			}
		}	
	}

	if (root_swap)
	{
		root_swap = !root_swap;
		avl->root = node;
	}

	return (node);
}

avl_node_t *CreateNode(avl_node_t *new, void *data)
{
	new = (avl_node_t*)malloc(sizeof(avl_node_t));
	new->data = data;
	new->left = new->right = NULL;

	return (new);
}

size_t Max(size_t a, size_t b)
{
	return (a > b ? a : b);
}

size_t NodeHeight(avl_node_t *node)
{
	size_t height = 0;

	if (node == NULL || (node->left == NULL && node->right == NULL))
	{
		return 0;
	}

	height = Max(NodeHeight(node->left), NodeHeight(node->right));

	return ++height;
}

int Balance(avl_node_t *node)
{
	return (NodeHeight(node->left) - NodeHeight(node->right));
}

avl_node_t *LeftRotation(avl_node_t *root)
{
	avl_node_t *pivot = root->right;
	
	root->right = pivot->left;
	pivot->left = root;

	return (pivot);
}

avl_node_t *RightLeftRotation(avl_node_t *root)
{
	avl_node_t *pivot = root;
	avl_node_t *temp = NULL;

	root = root->right;
	temp = root->left;
	root->left = temp->right;
	temp->right = root;
	pivot->right = temp;

	pivot = LeftRotation(pivot);

	return (pivot);
}

avl_node_t *RightRotation(avl_node_t *root)
{
	avl_node_t *pivot = root->left;
	
	root->left = pivot->right;
	pivot->right = root;

	return (pivot);
}

avl_node_t *LeftRightRotation(avl_node_t *root)
{
	avl_node_t *pivot = root;
	avl_node_t *temp = NULL;

	root = root->left;
	temp = root->right;
	root->right = temp->left;
	temp->left = root;
	pivot->left = temp;

	pivot = RightRotation(pivot);

	return (pivot);
}
