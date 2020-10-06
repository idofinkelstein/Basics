/*************************************
* 									 *			
* file name - bst.c					 *
* writer - Anna Poryadkov		 	 *
* reviewer - Ido Finkelstein		 *
* date -27.07.2020					 *
* topic - DS - BST					 *
*									 *
**************************************/

#include <stdio.h> /* size_t */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "bst.h"

#define DEAD_BEFF (void *)0xBADC0FFEE0DDF00D
 
struct bst
{
	/* pointer to a dummy in the tree */
	struct bst_node *end;
	bst_cmp_func_t cmp_func; 
	void *param;
};

struct bst_node
{
	struct bst *bst;
    struct bst_node *left;
    struct bst_node *right;
	struct bst_node *parent;	
	void *data;
};
/*typedef struct bst_node bst_node_t;*/

/*------------------------- Utility function --------------------------------*/

static bst_node_t *CreateNode(bst_node_t *left, bst_node_t *right, 
					   bst_node_t *parent, void *data, bst_t *bst);

static bst_node_t *GetTreeRoot(const bst_t *bst);
static bst_node_t *RightNode(bst_node_t *node);
static bst_node_t *LeftNode(bst_node_t *node);
static bst_node_t *ParentNode(bst_node_t *node);
static bst_iter_t RightIter(bst_node_t *node);
static bst_iter_t LeftIter(bst_node_t *node);
static bst_iter_t ParentIter(bst_node_t *node);

/*---------------------------------------------------------------------------*/

bst_t *BSTCreate(bst_cmp_func_t cmp, void *param)
{
	bst_t *new_bst = NULL;
	bst_node_t *head_node = NULL;

	new_bst = (bst_t *) malloc (sizeof(bst_t));
	if (NULL == new_bst)
	{
		return (NULL);
	}

	head_node = CreateNode(NULL, NULL, NULL, DEAD_BEFF, new_bst);
	if (NULL == head_node)
	{
		free(new_bst);
		new_bst = NULL;
		return (NULL);
	}

	new_bst->cmp_func = cmp;
	new_bst->param = param;
	new_bst->end = head_node;

	return (new_bst);
}

/*---------------------------------------------------------------------------*/

void BSTDestroy(bst_t *bst)
{
	bst_iter_t iter = BSTBegin(bst);
	bst_iter_t iter_to_destroy = {0};
	
	assert(bst);

	while (!BSTIterIsEqual(iter, BSTEnd(bst)))
	{
		iter_to_destroy = iter;
    	iter = BSTNext(iter);
	
    	BSTRemove(iter_to_destroy);
	}

	free(bst->end);
	bst->end = NULL;

	free(bst);
	bst = NULL;
}
 
/*---------------------------------------------------------------------------*/

size_t BSTSize(const bst_t *bst)
{
	size_t count = 0;
	bst_iter_t iter = {NULL};

	assert(bst);

	if (BSTIsEmpty(bst))
    {
        return (0);
    }

	iter = BSTBegin(bst);

	while (!BSTIterIsEqual(iter, BSTEnd(bst)))
	{
		++count;
		iter = BSTNext(iter);
	}

	return (count);
}

/*---------------------------------------------------------------------------*/

/* Return boolean Value: 1 - empty (TRUE), 0 - not empty. (FALSE) */
int BSTIsEmpty(const bst_t *bst)
{
	assert(bst);

	return (GetTreeRoot(bst) == NULL);
}

/*---------------------------------------------------------------------------*/

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_iter_t new_iter = {NULL};
	bst_node_t *node = NULL;
	bst_node_t *tmp_node = NULL;
	bst_node_t *parent_node = NULL;
	bst_iter_t biggest_iter = BSTPrev(BSTEnd(bst));

	assert(bst);

	node = CreateNode(NULL, NULL, NULL, data, bst);
	if (NULL == node)
	{
		return (BSTEnd(bst));
	}

	/* insert for the first element, the root element */
	if (BSTIsEmpty(bst))
	{
		node->parent = BSTEnd(bst).node;
		BSTEnd(bst).node->parent = node;
		BSTEnd(bst).node->left = node;
		new_iter.node = node;
		return (new_iter);
	}

	tmp_node = GetTreeRoot(bst);

	while (NULL != tmp_node)
	{
		parent_node = tmp_node;

		if (bst->cmp_func(tmp_node->data ,data ,bst->param) > 0)	
		{
			tmp_node = LeftNode(tmp_node);
		}
		else
		{
			tmp_node = RightNode(tmp_node);
		}	
	}
	
	if (bst->cmp_func(parent_node->data ,node->data ,bst->param) > 0)	
	{
		parent_node->left = node;
	}
	else
	{
		parent_node->right = node;
	}	
	node->parent = parent_node;
	/* update for the end if new element is biggesr then biggest element in
	 bst*/
	if (parent_node == biggest_iter.node && node == RightNode(parent_node))
	{
		BSTEnd(bst).node->left = node;
	}

	new_iter.node = node;
	return (new_iter);
}

/*---------------------------------------------------------------------------*/
void BSTRemove(bst_iter_t iter)
{
    bst_iter_t prev_iter = {NULL};
    bst_iter_t son = {NULL};

	assert(iter.node);
    
	/* if node have no children */
    if (NULL == LeftNode(iter.node) && NULL == RightNode(iter.node))
    {
         son.node = NULL;
    }
    /* if node have one right child */
    else if (NULL == LeftNode(iter.node) && NULL != RightNode(iter.node))
    {
        son = RightIter(iter.node);    
    }
	/* if node have one left child */
    else if (NULL != LeftNode(iter.node) && NULL == RightNode(iter.node))
    {
        son = LeftIter(iter.node);
    }
    /* if node have two children */
    else 
    {
        son = LeftIter(iter.node);
        prev_iter = BSTPrev(iter);
        prev_iter.node->right = iter.node->right;
        iter.node->right->parent = prev_iter.node;    
    }
    
    /* connect the son node to the parent iter node */
    if(son.node)
    {
        son.node->parent = ParentNode(iter.node);
    }
    /* connect the parent iter to the son node */
    if(ParentNode(iter.node)->right == iter.node)
    {
        ParentNode(iter.node)->right = son.node;
    }
    else
    {
        ParentNode(iter.node)->left = son.node;
    }        
    
    free(iter.node);
    iter.node = NULL;
}
/*
void BSTRemove(bst_iter_t iter)
{
	bst_iter_t Parent_iter = ParentIter(iter.node);
	bst_node_t *Right_node = NULL;
	bst_node_t *left_node = LeftNode(iter.node);
	
	assert(iter.node);

	/* if node have two children 
	if (NULL != RightNode(iter.node) && NULL != LeftNode(iter.node))
	{
		Right_node = left_node;

		if (NULL != RightNode(left_node))
		{
			Right_node = RightNode(left_node);

			while (NULL != RightNode(Right_node))
			{
				Right_node = RightNode(Right_node);
			}
		}

        if (iter.node == RightNode(Parent_iter.node))
        {
            Parent_iter.node->right = left_node;
        }
        else
        {
            Parent_iter.node->left = left_node;
        }

		left_node->parent = Parent_iter.node;

		iter.node->right->parent = Right_node;
		Right_node->right = RightNode(iter.node);

		/* if iter is root 
		if (BSTIterIsEqual(iter, BSTPrev(BSTEnd(iter.node->bst))))
		{
			BSTEnd(iter.node->bst).node->left = Parent_iter.node;
		}
	}
	/* if node have one right child 
	else if (NULL != RightNode(iter.node))
	{
		Right_node = RightNode(iter.node);

        if(iter.node == RightNode(Parent_iter.node))
        {
            Parent_iter.node->right = Right_node;
        }
        else
        {
            Parent_iter.node->left = Right_node;
        }

		Right_node->parent = Parent_iter.node;
	}
	/* if node have one left child 
	else if (NULL != LeftNode(iter.node))
	{
		left_node = LeftNode(iter.node);

        if(iter.node == RightNode(Parent_iter.node))
        {
            Parent_iter.node->right = left_node;
        }
        else
        {
            Parent_iter.node->left = left_node;
        }

		left_node->parent = Parent_iter.node;

		if (BSTIterIsEqual(iter, BSTPrev(BSTEnd(iter.node->bst))))
		{
			BSTEnd(iter.node->bst).node->left = Parent_iter.node;
		}
	}
	/* if node have no children 
	else if (NULL == RightNode(iter.node) && NULL == LeftNode(iter.node))
	{
        if(iter.node == RightNode(Parent_iter.node))
        {
            Parent_iter.node->right = NULL;
        }
        else
        {
            Parent_iter.node->left = NULL;
        }

		if (BSTIterIsEqual(iter, BSTPrev(BSTEnd(iter.node->bst))))
		{
			BSTEnd(iter.node->bst).node->left = Parent_iter.node;
		}
	}

	/* if iter is root , update the end->parent 
	if ((iter.node == GetTreeRoot(iter.node->bst)))
	{
		BSTEnd(iter.node->bst).node->parent = left_node;
	}

	free(iter.node);
	iter.node = NULL;
}
*/
/*---------------------------------------------------------------------------*/

bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_node_t *tmp_node = NULL;
	bst_iter_t tmp_iter = {NULL};

	assert(bst);

	if (BSTIsEmpty(bst))
	{	
		return (BSTEnd(bst));
	}

	tmp_node = GetTreeRoot(bst);

	while (NULL != tmp_node && LeftNode(tmp_node))
	{
		tmp_node = LeftNode(tmp_node);
	}

	tmp_iter.node = tmp_node;

	return (tmp_iter);
}

/*---------------------------------------------------------------------------*/

bst_iter_t BSTEnd(const bst_t *bst)
{
	bst_iter_t tmp_iter = {NULL};
	assert(bst);

	tmp_iter.node = bst->end;

	return (tmp_iter);
}

/*---------------------------------------------------------------------------*/

bst_iter_t BSTPrev(bst_iter_t iter)
{
	bst_iter_t parent_iter = {NULL};

	assert(iter.node);

	parent_iter = ParentIter(iter.node);

	if(BSTIsEmpty(iter.node->bst))
    {
    	return (BSTEnd(iter.node->bst));
    }

	/* If the node has left child, move down the left subtree to get the max
	 node */
	if (NULL != LeftNode(iter.node))
	{
		iter.node = LeftNode(iter.node);

		while (NULL != RightNode(iter.node))
		{
			iter.node = RightNode(iter.node);
		}
	}
	/* If the node is a right child, return its parent */
	else if (BSTIterIsEqual(iter, RightIter(parent_iter.node)))
	{
		iter.node = parent_iter.node;
	}
	/* If the node is a left child, move up the tree until you are a right
	 child and return its parent */
	else if (BSTIterIsEqual(iter, LeftIter(parent_iter.node)))
	{	
		/* If its the smallest node in tree, return end */
		if (BSTIterIsEqual(iter, BSTBegin(iter.node->bst)))
		{
			return (BSTEnd(iter.node->bst));
		}
		
    	while (!BSTIterIsEqual(parent_iter, BSTEnd(iter.node->bst))  && 
			    BSTIterIsEqual(iter, LeftIter(parent_iter.node)))
		{
        	iter.node = parent_iter.node; 
        	parent_iter.node = ParentNode(parent_iter.node); 
		}

		iter.node = parent_iter.node;
	}

	return (iter);
}

/*---------------------------------------------------------------------------*/

bst_iter_t BSTNext(bst_iter_t iter)
{
	bst_iter_t parent_iter = {NULL};

	assert(iter.node);

	if(BSTIsEmpty(iter.node->bst))
    {
    	return (BSTEnd(iter.node->bst));
    }

	parent_iter.node = iter.node->parent;

	/* If the node has right child, move down the right subtree to get the min 
	node */
	if (NULL != RightNode(iter.node))
	{
		iter.node = RightNode(iter.node);

		while (NULL != LeftNode(iter.node))
		{
			iter.node = LeftNode(iter.node);
		}
	}
	/* If its the biggest node in tree, return end */
	else if(BSTIterIsEqual(iter, BSTPrev(BSTEnd(iter.node->bst))))
	{
		return (BSTEnd(iter.node->bst));
	}
	/* If the node is a left child, return its parent */
	else if (BSTIterIsEqual(iter ,LeftIter(parent_iter.node)))
	{
		iter.node = parent_iter.node;
	}
	/* If the node is a right child, move up the tree until you are a left
	 child and return its parent */
	else if (BSTIterIsEqual(iter, RightIter(parent_iter.node)))
	{	
    	while (!BSTIterIsEqual(parent_iter, BSTEnd(iter.node->bst))  && 
			    BSTIterIsEqual(iter, RightIter(parent_iter.node)))
		{
        	iter.node = parent_iter.node; 
        	parent_iter.node = ParentNode(parent_iter.node); 
		}

		iter.node = parent_iter.node;
	}

	return (iter);
}

/*---------------------------------------------------------------------------*/

int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{


	return (iter1.node == iter2.node);
}

/*---------------------------------------------------------------------------*/

void *BSTGetData(bst_iter_t iter)
{
	assert(iter.node);

	return (iter.node->data);
}

/*---------------------------------------------------------------------------*/

bst_iter_t BSTFind(const bst_t *bst, const void *data)
{
	bst_iter_t iter = BSTBegin(bst);

	assert(bst);
	assert(data);

	while (!BSTIterIsEqual(iter, BSTEnd(bst)) && 
		   bst->cmp_func(iter.node->data ,data ,bst->param))
	{
		iter = BSTNext(iter);
	}

	return (iter);
}

/*---------------------------------------------------------------------------*/

int BSTForEach(bst_iter_t from, bst_iter_t to, 
				bst_do_action_func_t do_action ,void *param)
{
	bst_iter_t iter = {NULL};
	int do_action_status = 0;


	assert(from.node);
	assert(to.node);

	iter = from;

	while (!BSTIterIsEqual(iter, to) && 
		   1 != do_action_status)
	{
		do_action_status = do_action(BSTGetData(iter), param);
		iter = BSTNext(iter);
	}

	return (do_action_status);
}

/*-------------------------- Utility function -------------------------------*/

/* node creation function */
static bst_node_t *CreateNode(bst_node_t *left, bst_node_t *right, 
					   bst_node_t *parent, void *data, bst_t *bst)
{
	bst_node_t *new_node = NULL;

	new_node = (bst_node_t *) malloc (sizeof(bst_node_t));
	if (NULL == new_node)
	{
		return (NULL);
	}

	new_node->data = data;
	new_node->left = left;
	new_node->right = right;
	new_node->parent = parent;
	new_node->bst = bst;

	return (new_node);
}
/*---------------------------------------------------------------------------*/
static bst_node_t *GetTreeRoot(const bst_t *bst)
{
	assert(bst);

	return(bst->end->parent);
}
/*---------------------------------------------------------------------------*/
static bst_node_t *RightNode(bst_node_t *node)
{
	assert(node);
	return(node->right);
}
/*---------------------------------------------------------------------------*/
static bst_node_t *LeftNode(bst_node_t *node)
{
	assert(node);
	return(node->left);
}
/*---------------------------------------------------------------------------*/
static bst_node_t *ParentNode(bst_node_t *node)
{
	assert(node);
	return(node->parent);
}
/*---------------------------------------------------------------------------*/
static bst_iter_t RightIter(bst_node_t *node)
{
	bst_iter_t iter = {NULL};

	assert(node);

	iter.node = node->right;
	return(iter);
}
/*---------------------------------------------------------------------------*/
static bst_iter_t LeftIter(bst_node_t *node)
{
	bst_iter_t iter = {NULL};

	assert(node);

	iter.node = node->left;
	return(iter);
}
/*---------------------------------------------------------------------------*/
static bst_iter_t ParentIter(bst_node_t *node)
{
	bst_iter_t iter = {NULL};

	assert(node);

	iter.node = node->parent;
	return(iter);
}
