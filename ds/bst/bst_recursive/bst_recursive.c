/********************************
File name: bst.c
Author: Ido Finkelstein
Reviewer: Ori Komemie
Date: 24/7/2020
*********************************/


#include <stdlib.h> /* malloc, free */
#include <assert.h>

#include "bst.h"

/* utility function declarations */
static void SetNode(bst_node_t *curr, bst_node_t *new);
static void DeleteChildrenlessNode(bst_iter_t curr);
static void Delete1ChildNode(bst_iter_t curr);
static bst_iter_t GetEnd(bst_iter_t iter);
void DeleteNode(bst_node_t *node);
size_t RecursiveSize(bst_node_t *node, size_t count, const bst_t *bst);
bst_node_t *RecursiveFind(const bst_t *bst, bst_node_t *node, const void *data);
bst_node_t *InsertNode(bst_t *bst, bst_node_t *node, void *data, bst_node_t *new);

struct bst
{
	bst_node_t *root;
	bst_node_t *end;
	void *param;
	bst_cmp_func_t cmp;
};

struct bst_node
{
	void *data;	
	bst_node_t *parent;
	bst_node_t *left;
	bst_node_t *right;
	
};

bst_t *BSTCreate(bst_cmp_func_t cmp, void *param)
{
	bst_t *bst = NULL;
	bst_iter_t dummy = {NULL};

	bst = (struct bst*)malloc(sizeof(bst_t));

	if (NULL == bst)
	{
		return (NULL);
	}

	bst->param = param;
	bst->cmp = cmp;
	
	dummy.node = (bst_node_t*)malloc(sizeof(bst_node_t));

	if (NULL == dummy.node)
	{
		free(bst);

		return (NULL);
	}

	bst->root = dummy.node;
	bst->end = dummy.node;

	dummy.node->parent = NULL;
	dummy.node->right = NULL;
	dummy.node->left = NULL; 
	dummy.node->data = bst; 

	return (bst);
}

void BSTDestroy(bst_t *bst)
{
	bst_node_t *curr = bst->root;

	assert(bst);

	DeleteNode(curr);

	free(bst);
}

void *BSTGetData(bst_iter_t iter)
{
	assert(iter.node);

	return (iter.node->data);
}

int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
	assert(iter1.node);
	assert(iter2.node);

	return (iter1.node == iter2.node);
}

int BSTIsEmpty(const bst_t *bst)
{
	assert(bst);

	return (bst->root == bst->end);
}

bst_iter_t BSTEnd(const bst_t *bst)
{
	bst_iter_t end = {NULL};

	assert(bst);

	end.node = bst->end;

	return (end);
}

bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_iter_t curr = {NULL};
	curr.node = bst->root;

	assert(bst);

	while (curr.node->left != NULL)
	{
		curr.node = curr.node->left;
	}

	return (curr);
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
	bst_iter_t curr = iter;

	assert(iter.node);

	if (curr.node->left != NULL)
	{
		curr.node = curr.node->left;
		
		while (curr.node->right != NULL)
		{
			curr.node = curr.node->right;
		}

		return (curr);
	}

	while (curr.node->parent && curr.node->parent->left == curr.node)
	{
		curr.node = curr.node->parent;
	}

	if (curr.node->parent && curr.node->parent->right == curr.node)
	{
		curr.node = curr.node->parent;

		return (curr);
	}

	return (iter);
}

bst_iter_t BSTNext(bst_iter_t iter)
{
	bst_iter_t curr = iter;

	assert(iter.node);

	if (curr.node->right != NULL)
	{
		curr.node = curr.node->right;
		
		while (curr.node->left != NULL)
		{
			curr.node = curr.node->left;
		}

		return (curr);
	}
	
	/* is curr a right child? */
	while (curr.node->parent && curr.node == curr.node->parent->right)
	{
		curr.node = curr.node->parent;
	}

	/* is curr a left child? */
	if (curr.node->parent && curr.node->parent->left == curr.node) 
	{
		curr.node = curr.node->parent;

		return (curr);
	}

	return (iter);
}

size_t BSTSize(const bst_t *bst)
{
	bst_node_t *curr = bst->root;

	size_t count = 0;

	assert(bst);

	if (!BSTIsEmpty(bst))
	{
		count =  RecursiveSize(curr, count, bst);
	}

	return count;
}

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_iter_t new_node = {NULL};
	bst_node_t *curr = NULL;
	bst_node_t *new = NULL;

	assert(bst);

	curr = bst->root;
	new_node.node = malloc(sizeof(bst_node_t));
	new = new_node.node;

	if (NULL == new_node.node)
	{
		new_node.node = bst->end;

		return (new_node);
	}
	
	new_node.node->data = data;

	/* case tree is empty */
	if (BSTIsEmpty(bst))
	{
		bst->root = new_node.node;
		new_node.node->right = bst->end;
		new_node.node->left = NULL;
		new_node.node->parent = NULL;
		bst->end->parent = new_node.node;

		return (new_node);
	}

	/* case new data is bigger than the biggest node data */
	if((bst->cmp(bst->end->parent->data, data, data) < 0))
	{
		new_node.node->left = NULL;
		new_node.node->parent = bst->end->parent;
		new_node.node->right  = bst->end;
		bst->end->parent->right = new_node.node;
		bst->end->parent = new_node.node;

		return (new_node);
	}

	new = InsertNode(bst, curr, data, new);

	new_node.node = new;

	return (new_node);
}

void BSTRemove(bst_iter_t iter)
{
	bst_iter_t curr = iter;
	bst_t *bst = NULL;

	assert(iter.node);

	curr = GetEnd(curr);
	bst = curr.node->data;

	/* case only 1 element in the tree */
	if (BSTSize(bst) == 1)
	{
		free(curr.node->parent);
		curr.node->parent = NULL;
		bst->root = curr.node;

		return;
	}

	curr = iter;

	/* case node to remove is root node */
	if (bst->root == curr.node)
	{
		if (BSTPrev(curr).node != curr.node)
		{
			curr = BSTPrev(curr);
			iter.node->data = curr.node->data;
		}
		else if (BSTNext(curr).node != curr.node)
		{
			curr = BSTNext(curr);
			iter.node->data = curr.node->data;
		}
	}


	/* has no children */
	if (curr.node->left == NULL && curr.node->right == NULL)
	{
		DeleteChildrenlessNode(curr);
	}
	/* has 1 child */
	else if (((curr.node->right && curr.node->left == NULL) || 
			  (curr.node->left && curr.node->right == NULL)))
	{
		Delete1ChildNode(curr);
	}
	else /* has 2 children */
	{
		curr.node->data = BSTGetData(BSTNext(curr));
		curr = BSTNext(curr);

		if (curr.node->left == NULL && curr.node->right == NULL)
		{
			DeleteChildrenlessNode(curr);
		}
		else
		{
			Delete1ChildNode(curr);
		}
	}
}

bst_iter_t BSTFind(const bst_t *bst, const void *data)
{
	bst_iter_t curr = {NULL};
	bst_node_t *node = bst->root;

	assert(bst);

	if (!BSTIsEmpty(bst))
	{
		node = RecursiveFind(bst, node, data);
	}

	curr.node = node;

	return (curr);
}

int BSTForEach(bst_iter_t from, bst_iter_t to, 
			   bst_do_action_func_t do_action,
			   void *param)
{
	bst_iter_t curr = from;

	assert(from.node);
	assert(to.node);

	while (!BSTIterIsEqual(curr, to))
	{
		if (NULL == curr.node)	
		{
			return do_action(curr.node->data, param);
		}

		do_action(curr.node->data, param);
	
		curr = BSTNext(curr);	
	}

	return 0;
}

static void SetNode(bst_node_t *curr, bst_node_t *new)
{
	new->parent = curr;
	new->left = NULL;	
	new->right = NULL;
}

static void DeleteChildrenlessNode(bst_iter_t curr)
{
	if (curr.node->parent->left == curr.node)
		{
			curr.node->parent->left = NULL;
		}
		else
		{
			curr.node->parent->right = NULL;
		}
		
		free(curr.node);
}

static void Delete1ChildNode(bst_iter_t curr)
{
	if (curr.node->left)
		{
			if (curr.node->parent->left == curr.node)
			{
				curr.node->parent->left = curr.node->left;
			}
			else
			{
				curr.node->parent->right = curr.node->left;
			}

			curr.node->left->parent = curr.node->parent;
		}
		else
		{
			if (curr.node->parent->right == curr.node)
			{
				curr.node->parent->right = curr.node->right;
			}
			else
			{
				curr.node->parent->left = curr.node->right;
			}

			curr.node->right->parent = curr.node->parent;
		}

		free(curr.node);
}

static bst_iter_t GetEnd(bst_iter_t iter)
{
	while (iter.node->parent)
	{
		iter.node = iter.node->parent;
	}

	while (iter.node->right)
	{
		iter.node = iter.node->right;
	}

	return (iter);
}

void DeleteNode(bst_node_t *node)
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

size_t RecursiveSize(bst_node_t *node, size_t count, const bst_t *bst)
{
	if (node->left != NULL)
	{			
		count = RecursiveSize(node->left, count, bst);			
	}
	if (node->right != bst->end && node->right != NULL)
	{
		count = RecursiveSize(node->right, count, bst);		
	}

	return ++count;	
}

bst_node_t *InsertNode(bst_t *bst, bst_node_t *node, void *data, bst_node_t *new)
{
	if (bst->cmp(node->data, data, data) != 0)
	{
		if (bst->cmp(node->data, data, data) > 0 && 
			node->left != NULL)
		{
			node = InsertNode(bst, node->left, data, new);
		}
		else if (bst->cmp(node->data, data, data) < 0 && 
				 node->right != NULL)
		{
			node = InsertNode(bst, node->right, data, new);
		}
		else if (bst->cmp(node->data, data, data) > 0)
		{
			node->left = new;
			SetNode(node, new);

			return (new);
		}
		else if (bst->cmp(node->data, data, data) < 0)
		{
			node->right = new;
			SetNode(node, new);

			return (new);
		}

		return (new);
	}
	
	free(new);
	new = bst->end;
	return (new);
}

bst_node_t *RecursiveFind(const bst_t *bst, bst_node_t *node, const void *data)
{
	if (bst->cmp(node->data, data, NULL) != 0) 
	{
		if (bst->cmp(node->data, data, NULL) > 0 &&
		    node->left != NULL)
		{
			node = RecursiveFind(bst, node->left, data);
		}
		else if (node->right != bst->end && 
				 bst->cmp(node->data, data, NULL) < 0 && 
				 node->right != NULL)
		{
			node = RecursiveFind(bst, node->right, data);
		}
		else
		{
			node = bst->end;

			return (node);
		}
	}
	
	return node;
}
