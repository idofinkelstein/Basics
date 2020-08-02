/********************************
File name: avl.c
Author: Ido Finkelstein
Reviewer: Guy Chen
Date: 1/8/2020
*********************************/

#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* printf */
#include <assert.h>

#include "avl.h"


typedef struct avl_node avl_node_t;

struct avl_node
{
	void *data; /* represents the key, more fields could be added in the future */
	avl_node_t *left;
	avl_node_t *right;
};

struct avl
{
	avl_node_t *root;
	avl_cmp_func_t cmp;
	void *param;
};

/* Utility function declarations */
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
avl_node_t *RecursiveRemove(avl_t *avl, avl_node_t *node, void *data);
avl_node_t *GetMinClosestNode(avl_node_t *node);
int IsBalancedRecursive(avl_node_t *node, int balance);
void InOrderTraversal(avl_node_t *node);
void PreOrderTraversal(avl_node_t *node);
void PostOrderTraversal(avl_node_t *node);
int RecursiveForEach(avl_node_t *root, 
							avl_do_action_func_t do_action,
							void *param,
							int status);

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

	assert(avl);

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

	assert(avl);

	if (!AVLIsEmpty(avl))
	{
		count = GetSize(node, count);	
	}

	return (count);
}

int AVLInsert(avl_t *avl, void *data)
{
	avl_node_t *node = avl->root;

	assert(avl);

	node = InsertNode(avl, node, data);

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

int AVLForEach(avl_t *avl, avl_do_action_func_t do_action ,void *param)
{
	avl_node_t *root = avl->root;
	int status = 0;

	assert(avl);

	if (!AVLIsEmpty(avl))
	{
		status = RecursiveForEach(root, do_action, param, status);
	}

	return status;
}

void AVLRemove(avl_t *avl, void *data)
{
	avl_node_t *root = avl->root;

	assert(avl);

	if (!AVLIsEmpty(avl))
	{
		RecursiveRemove(avl, root, data);
	}
}

/*--------------------------Utility functions--------------------------------*/

avl_node_t *RecursiveRemove(avl_t *avl, avl_node_t *node, void *data)
{
	avl_node_t *temp_node = NULL;
	/* variable to check whether the root has been changed during rebalancing */
	int root_swap = 0; 

	/* deletion part */
	if (avl->cmp(node->data, data, NULL) == 0)
	{
		/* node to remove has no children */
		if (node->left == NULL && node->right == NULL)
		{
			free(node);
			return (NULL);
		}
		/* node to remove has one child */
		else if ((node->left == NULL && node->right) || 
				 (node->left && node->right == NULL))
		{		
			if (node->left)
			{
				temp_node = node->left;
				free(node);
				return (temp_node);
			}
			else
			{
				temp_node = node->right;
				free(node);
				return(temp_node);
			}
		}
		/* node to remove has two children */
		else
		{
			temp_node = GetMinClosestNode(node);
			node->data = temp_node->data;		
			node->right = RecursiveRemove(avl, node->right, node->data);
			return (node);			
		}
	}
	
	/* scanning part */
	else if (avl->cmp(node->data, data, NULL) > 0 && node->left != NULL)		
	{
		node->left = RecursiveRemove(avl, node->left, data);
	}
	else if (avl->cmp(node->data, data, NULL) < 0 && node->right != NULL)
	{
		node->right = RecursiveRemove(avl, node->right, data);
	}

	if (node == avl->root)
	{
		root_swap = !root_swap;
	}

	/* rebalancing part */
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

	if (root_swap)
	{
		root_swap = !root_swap;
		avl->root = node;
	}

	return (node);	
}

int RecursiveForEach(avl_node_t *root, 
							avl_do_action_func_t do_action,
							void *param,
							int status)
{
	if (root->left != NULL)
	{
		status = RecursiveForEach(root->left, do_action, param, status);
	}

	/* condition to stop function from iterating the whole tree */
	if (status)
	{
		return (status);
	}
	
	status = do_action(root->data, param);

	if (root->right != NULL)
	{
		status = RecursiveForEach(root->right, do_action, param, status);
	}

	return (status);
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
	/* variable to check whether the root has been changed during rebalancing */
	int root_swap = 0;

	/* insertion part */ 
	if (node == NULL)
	{
		new = CreateNode(new, data);

		if (avl->root == NULL)
		{
			avl->root = new;
		}

		return (new);
	}
	/* scanning part */
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

		/* rebalancing part */
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

	if (NULL == new)
	{
		return (NULL);
	}	

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

	/* this condition ignores leaves so it counts only the linkes  */
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

avl_node_t *GetMinClosestNode(avl_node_t *node)
{
	if (node->right != NULL)
	{
		node = node->right;
	}
	
	while (node->left != NULL)
	{
		node = node->left;
	}

	return (node);	
}

/*------------------------Debug functions------------------------------*/

/* boolian function, return 1 if the whole tree is balanced */
int IsBalanced(avl_t *avl)
{
	avl_node_t *root = avl->root;
	int balance = 0;

	balance = IsBalancedRecursive(root, balance);

	return (balance <= 1 && balance >= -1);
}

int IsBalancedRecursive(avl_node_t *node, int balance)
{
	if (node->left != NULL)
	{
		balance = IsBalancedRecursive(node->left, balance);
	}

	if (balance > 1 || balance < -1)
	{
		return (balance);
	}
	
	balance = Balance(node);

	if (node->right != NULL)
	{
		balance = IsBalancedRecursive(node->right, balance);
	}

	return (balance);
}

void ChooseTraversalOrder(avl_t *avl, int num)
{
	avl_node_t *root = avl->root;

	if (num == 1)
	{
		InOrderTraversal(root);
	}
	else if (num == 2)
	{
		PreOrderTraversal(root);
	}
	else if (num == 3)
	{
		PostOrderTraversal(root);
	}
}

void InOrderTraversal(avl_node_t *node)
{
	if (node->left != NULL)
	{
		InOrderTraversal(node->left);
	}
	
	printf("%d\n", *(int*)node->data);

	if (node->right != NULL)
	{
		InOrderTraversal(node->right);
	}
}

void PreOrderTraversal(avl_node_t *node)
{
	printf("%d\n", *(int*)node->data);

	if (node->left != NULL)
	{
		PreOrderTraversal(node->left);
	}

	if (node->right != NULL)
	{
		PreOrderTraversal(node->right);
	}
}

void PostOrderTraversal(avl_node_t *node)
{
	if (node->left != NULL)
	{
		PostOrderTraversal(node->left);
	}	

	if (node->right != NULL)
	{
		PostOrderTraversal(node->right);
	}

	printf("%d\n", *(int*)node->data);
}


