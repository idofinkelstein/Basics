/********************************
File name: avl.c
Author: Ido Finkelstein
Reviewer: Guy Chen
Date: 1/8/2020
*********************************/

#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* printf */
#include <assert.h>

enum traversal
{
	INORDER = 1,
	PREORDER,
	POSTORDER
};

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
static void DeleteNode(avl_node_t *node);
static size_t GetSize(avl_node_t *node);
static void *RecursiveFind(const avl_t *avl, avl_node_t *node, const void *data);
static avl_node_t *InsertNode(avl_t *avl, avl_node_t *node, void *data);
static avl_node_t *CreateNode(avl_node_t *new, void *data);
static size_t NodeHeight(avl_node_t *node);
static size_t Max(size_t a, size_t b);
static int Balance(avl_node_t *node);
static avl_node_t *Rebalance(avl_node_t *node);
static avl_node_t *RightRotation(avl_node_t *root);
static avl_node_t *RightLeftRotation(avl_node_t *root);
static avl_node_t *LeftRotation(avl_node_t *root);
static avl_node_t *LeftRightRotation(avl_node_t *root);
static avl_node_t *RecursiveRemove(avl_t *avl, avl_node_t *node, void *data);
static avl_node_t *GetMinClosestNode(avl_node_t *node);
static int IsBalancedRecursive(avl_node_t *node, int balance);
static void InOrderTraversal(avl_node_t *node);
static void PreOrderTraversal(avl_node_t *node);
static void PostOrderTraversal(avl_node_t *node);
static int RecursiveForEach(avl_node_t *node, 
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
	assert(avl);

	DeleteNode(avl->root);	
	
	free(avl);
	avl = NULL;
}

int AVLIsEmpty(const avl_t *avl)
{
	assert(avl);

	return (avl->root == NULL);
}

size_t AVLSize(const avl_t *avl)
{
	assert(avl);

	return (GetSize(avl->root));
}

int AVLInsert(avl_t *avl, void *data)
{
	avl_node_t *node = NULL;

	assert(avl);

	node = avl->root;

	node = InsertNode(avl, node, data);

	return (node == NULL);
}

void *AVLFind(const avl_t *avl, const void *data)
{
	assert(avl);

	return (RecursiveFind(avl, avl->root, data));
}

int AVLForEach(avl_t *avl, avl_do_action_func_t do_action ,void *param)
{
	int status = 0;

	assert(avl);
	
	status = RecursiveForEach(avl->root, do_action, param, status);	

	return status;
}

void AVLRemove(avl_t *avl, void *data)
{
	avl_node_t *root = NULL;

	assert(avl);

	root = avl->root;

	if (!AVLIsEmpty(avl))
	{
		RecursiveRemove(avl, root, data);
	}
}

/*--------------------------Utility functions--------------------------------*/

static avl_node_t *RecursiveRemove(avl_t *avl, avl_node_t *node, void *data)
{
	avl_node_t *temp_node = NULL;
	/* variable to check whether the root has been changed during rebalancing */
	int root_swap = 0; 

	/* deletion part */
	if (0 == avl->cmp(node->data, data, avl->param))
	{
		/* node to remove has no children */
		if (NULL == node->left  && NULL == node->right)
		{
			free(node);
			return (NULL);
		}
		/* node to remove has one child */
		else if ((NULL == node->left && node->right) || 
				 (node->left && NULL == node->right))
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
	else if (avl->cmp(node->data, data, avl->param) > 0 && NULL != node->left)		
	{
		node->left = RecursiveRemove(avl, node->left, data);
	}
	else if (avl->cmp(node->data, data, avl->param) < 0 && NULL != node->right)
	{
		node->right = RecursiveRemove(avl, node->right, data);
	}

	if (node == avl->root)
	{
		root_swap = !root_swap;
	}

	/* rebalancing part */
	node = Rebalance(node);

	if (root_swap)
	{
		root_swap = !root_swap;
		avl->root = node;
	}

	return (node);	
}

static int RecursiveForEach(avl_node_t *node, 
							avl_do_action_func_t do_action,
							void *param,
							int status)
{
	if (NULL == node)
	{
		return (status);
	}

	status = RecursiveForEach(node->left, do_action, param, status);
	
	/* condition to stop function from iterating the whole tree */	
	if (status)
	{
		return (status);
	}

	status = do_action(node->data, param);

	status = RecursiveForEach(node->right, do_action, param, status);
	
	return (status);
}

static void DeleteNode(avl_node_t *node)
{
	if (NULL == node)
	{
		return;
	}
		
	DeleteNode(node->left);
	DeleteNode(node->right);

	free(node);
	node = NULL;	
}

static size_t GetSize(avl_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}
						
	return (1 + GetSize(node->left) + GetSize(node->right));
}

static void *RecursiveFind(const avl_t *avl, avl_node_t *node, const void *data)
{
	if (NULL == node)
	{
		return (NULL);
	}

	if (avl->cmp(node->data, data, avl->param) != 0) 
	{
		if (avl->cmp(node->data, data, avl->param) > 0)
		{
			node = RecursiveFind(avl, node->left, data);
		}
		else if (avl->cmp(node->data, data, avl->param) < 0)
		{
			node = RecursiveFind(avl, node->right, data);
		}
	}
	
	return (node);
}

static avl_node_t *InsertNode(avl_t *avl, avl_node_t *node, void *data)
{
	avl_node_t *new = NULL;
	/* variable to check whether the root has been changed during rebalancing */
	int root_swap = 0;

	/* insertion part */ 
	if (NULL == node)
	{
		new = CreateNode(new, data);

		if (NULL == avl->root)
		{
			avl->root = new;
		}

		return (new);
	}
	/* scanning part */
	if (0 != avl->cmp(node->data, data, avl->param))
	{
		if (avl->cmp(node->data, data, avl->param) > 0)
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
		node = Rebalance(node);
	}

	if (root_swap)
	{
		root_swap = !root_swap;
		avl->root = node;
	}

	return (node);
}

static avl_node_t *CreateNode(avl_node_t *new, void *data)
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

static size_t Max(size_t a, size_t b)
{
	return (a > b ? a : b);
}

static size_t NodeHeight(avl_node_t *node)
{
	size_t height = 0;

	/* this condition ignores leaves so it counts only the linkes  */
	if (NULL == node || (NULL == node->left && NULL == node->right))
	{
		return 0;
	}

	height = Max(NodeHeight(node->left), NodeHeight(node->right));

	return ++height;
}

static int Balance(avl_node_t *node)
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

static avl_node_t *RightLeftRotation(avl_node_t *root)
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

static avl_node_t *RightRotation(avl_node_t *root)
{
	avl_node_t *pivot = root->left;
	
	root->left = pivot->right;
	pivot->right = root;

	return (pivot);
}

static avl_node_t *LeftRightRotation(avl_node_t *root)
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

static avl_node_t *GetMinClosestNode(avl_node_t *node)
{
	if (NULL != node->right)
	{
		node = node->right;
	}
	
	while (NULL != node->left)
	{
		node = node->left;
	}

	return (node);	
}

static avl_node_t *Rebalance(avl_node_t *node)
{
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

static int IsBalancedRecursive(avl_node_t *node, int balance)
{
	if (NULL != node->left)
	{
		balance = IsBalancedRecursive(node->left, balance);
	}

	if (balance > 1 || balance < -1)
	{
		return (balance);
	}
	
	balance = Balance(node);

	if (NULL != node->right)
	{
		balance = IsBalancedRecursive(node->right, balance);
	}

	return (balance);
}

void ChooseTraversalOrder(avl_t *avl, int num)
{
	avl_node_t *root = avl->root;

	if (INORDER == num)
	{
		InOrderTraversal(root);
	}
	else if (PREORDER == num)
	{
		PreOrderTraversal(root);
	}
	else if (POSTORDER == num)
	{
		PostOrderTraversal(root);
	}
}

static void InOrderTraversal(avl_node_t *node)
{
	if (NULL != node->left)
	{
		InOrderTraversal(node->left);
	}
	
	printf("%d\n", *(int*)node->data);

	if (NULL !=node->right)
	{
		InOrderTraversal(node->right);
	}
}

static void PreOrderTraversal(avl_node_t *node)
{
	printf("%d\n", *(int*)node->data);

	if (NULL != node->left)
	{
		PreOrderTraversal(node->left);
	}

	if (NULL !=node->right)
	{
		PreOrderTraversal(node->right);
	}
}

static void PostOrderTraversal(avl_node_t *node)
{
	if (NULL != node->left)
	{
		PostOrderTraversal(node->left);
	}	

	if (NULL !=node->right)
	{
		PostOrderTraversal(node->right);
	}

	printf("%d\n", *(int*)node->data);
}

