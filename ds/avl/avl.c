/********************************
File name: avl.c
Author: Ido Finkelstein
Reviewer: Guy Chen
Date: 1/8/2020
*********************************/
#ifndef NDEBUG
#include <stdio.h> /* printf */
#endif

#include <stdlib.h> /* malloc, free */
#include <assert.h>

enum traversal
{
	INORDER = 1,
	PREORDER,
	POSTORDER
};

typedef enum 
{
	LEFT = 0, /* NEVER CHANGE THIS VALUE!!! */
	RIGHT

}child_t;

#include "avl.h"


typedef struct avl_node avl_node_t;

struct avl_node
{
	void *data; /* represents the key, more fields could be added in the future */
	avl_node_t *child[2];
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
	assert(avl);

	return (InsertNode(avl, avl->root, data) == NULL);
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
	assert(avl);
	
	RecursiveRemove(avl, avl->root, data);	
}

/*--------------------------Utility functions--------------------------------*/

static avl_node_t *RecursiveRemove(avl_t *avl, avl_node_t *node, void *data)
{
	avl_node_t *temp_node = NULL;
	child_t child = 0;
	/* variable to check whether the root has been changed during rebalancing */
	int root_swap = 0; 

	if (NULL == node)
	{
		return (NULL);
	}

	/* deletion part */
	if (0 == avl->cmp(node->data, data, avl->param))
	{
		/* node to remove has no children */
		if (NULL == node->child[LEFT]  && NULL == node->child[RIGHT])
		{
			free(node);
			return (NULL);
		}
		/* node to remove has one child */
		else if (node->child[LEFT] && NULL == node->child[RIGHT])
		{		
			temp_node = node->child[LEFT];
			free(node);
			return (temp_node);
		}	
		else if (node->child[RIGHT] && NULL == node->child[LEFT])
		{
			temp_node = node->child[RIGHT];
			free(node);
			return(temp_node);
		}	
		/* node to remove has two children */
		else
		{
			temp_node = GetMinClosestNode(node);
			node->data = temp_node->data;		
			node->child[RIGHT] = RecursiveRemove(avl, 
												 node->child[RIGHT], 
												 node->data);
			return (node);			
		}
	}
	
	/* scanning part */
	else
	{
		/* if node->data > data go left, else go right */
		child = avl->cmp(node->data, data, avl->param) < 0;
		node->child[child] = RecursiveRemove(avl, node->child[child], data);
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

	status = RecursiveForEach(node->child[LEFT], do_action, param, status);
	
	/* condition to stop function from iterating the whole tree */	
	if (status)
	{
		return (status);
	}

	status = do_action(node->data, param);

	status = RecursiveForEach(node->child[RIGHT], do_action, param, status);
	
	return (status);
}

static void DeleteNode(avl_node_t *node)
{
	if (NULL == node)
	{
		return;
	}
		
	DeleteNode(node->child[LEFT]);
	DeleteNode(node->child[RIGHT]);

	free(node);
	node = NULL;	
}

static size_t GetSize(avl_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}
						
	return (1 + GetSize(node->child[LEFT]) + GetSize(node->child[RIGHT]));
}

static void *RecursiveFind(const avl_t *avl, avl_node_t *node, const void *data)
{
	child_t child = 0;

	if (NULL == node)
	{
		return (NULL);
	}

	if (avl->cmp(node->data, data, avl->param) != 0) 
	{	
		/* if node->data > data go left, else go right */
		child = avl->cmp(node->data, data, avl->param) < 0;
		node = RecursiveFind(avl, node->child[child], data);
	}
	
	return (node);
}

static avl_node_t *InsertNode(avl_t *avl, avl_node_t *node, void *data)
{
	avl_node_t *new = NULL;
	child_t child = 0;
	/* variable to check whether the root has been changed during rebalancing */
	int root_swap = 0;

	/* insertion part */ 
	if (NULL == node)
	{
		new = CreateNode(new, data);

		if (AVLIsEmpty(avl))
		{
			avl->root = new;
		}

		return (new);
	}
	/* scanning part */
	else if (0 != avl->cmp(node->data, data, avl->param)) 
	{
		/* if node->data > data go left, else go right */
		child = avl->cmp(node->data, data, avl->param) < 0;
		node->child[child] = InsertNode(avl, node->child[child], data);
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

static avl_node_t *CreateNode(avl_node_t *new, void *data)
{
	new = (avl_node_t*)malloc(sizeof(avl_node_t));

	if (NULL == new)
	{
		return (NULL);
	}	

	new->data = data;
	new->child[LEFT] = new->child[RIGHT] = NULL;

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
	if (NULL == node || (NULL == node->child[LEFT] && NULL == node->child[RIGHT]))
	{
		return 0;
	}

	height = Max(NodeHeight(node->child[LEFT]), NodeHeight(node->child[RIGHT]));

	return ++height;
}

static int Balance(avl_node_t *node)
{
	return (NodeHeight(node->child[LEFT]) - NodeHeight(node->child[RIGHT]));
}

avl_node_t *LeftRotation(avl_node_t *root)
{
	avl_node_t *pivot = root->child[RIGHT];
	
	root->child[RIGHT] = pivot->child[LEFT];
	pivot->child[LEFT] = root;

	return (pivot);
}

static avl_node_t *RightLeftRotation(avl_node_t *root)
{
	avl_node_t *pivot = root;
	avl_node_t *temp = NULL;

	root = root->child[RIGHT];
	temp = root->child[LEFT];
	root->child[LEFT] = temp->child[RIGHT];
	temp->child[RIGHT] = root;
	pivot->child[RIGHT] = temp;

	pivot = LeftRotation(pivot);

	return (pivot);
}

static avl_node_t *RightRotation(avl_node_t *root)
{
	avl_node_t *pivot = root->child[LEFT];
	
	root->child[LEFT] = pivot->child[RIGHT];
	pivot->child[RIGHT] = root;

	return (pivot);
}

static avl_node_t *LeftRightRotation(avl_node_t *root)
{
	avl_node_t *pivot = root;
	avl_node_t *temp = NULL;

	root = root->child[LEFT];
	temp = root->child[RIGHT];
	root->child[RIGHT] = temp->child[LEFT];
	temp->child[LEFT] = root;
	pivot->child[LEFT] = temp;

	pivot = RightRotation(pivot);

	return (pivot);
}

static avl_node_t *GetMinClosestNode(avl_node_t *node)
{
	if (NULL != node->child[RIGHT])
	{
		node = node->child[RIGHT];
	}
	
	while (NULL != node->child[LEFT])
	{
		node = node->child[LEFT];
	}

	return (node);	
}

static avl_node_t *Rebalance(avl_node_t *node)
{
	if (Balance(node) > 1)
	{			
		if (NodeHeight(node->child[LEFT]->child[LEFT]) >= 
			NodeHeight(node->child[LEFT]->child[RIGHT]))
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
		if (NodeHeight(node->child[RIGHT]->child[RIGHT]) >= 
			NodeHeight(node->child[RIGHT]->child[LEFT]))
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
	if (NULL != node->child[LEFT])
	{
		balance = IsBalancedRecursive(node->child[LEFT], balance);
	}

	if (balance > 1 || balance < -1)
	{
		return (balance);
	}
	
	balance = Balance(node);

	if (NULL != node->child[RIGHT])
	{
		balance = IsBalancedRecursive(node->child[RIGHT], balance);
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
	if (NULL != node->child[LEFT])
	{
		InOrderTraversal(node->child[LEFT]);
	}
	
	printf("%d\n", *(int*)node->data);

	if (NULL !=node->child[RIGHT])
	{
		InOrderTraversal(node->child[RIGHT]);
	}
}

static void PreOrderTraversal(avl_node_t *node)
{
	printf("%d\n", *(int*)node->data);

	if (NULL != node->child[LEFT])
	{
		PreOrderTraversal(node->child[LEFT]);
	}

	if (NULL !=node->child[RIGHT])
	{
		PreOrderTraversal(node->child[RIGHT]);
	}
}

static void PostOrderTraversal(avl_node_t *node)
{
	if (NULL != node->child[LEFT])
	{
		PostOrderTraversal(node->child[LEFT]);
	}	

	if (NULL !=node->child[RIGHT])
	{
		PostOrderTraversal(node->child[RIGHT]);
	}

	printf("%d\n", *(int*)node->data);
}

