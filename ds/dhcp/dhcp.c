/**************************
File name: dhcp_test.c
Author: Ido Finkelstein
Date: 21/8/2020
Reviewer: Ori Komemie
***************************/

#include <stdlib.h> 	/* malloc, free */
#include <arpa/inet.h>  /* inet_ntop, inet_pton	*/
#include <assert.h>

#include "dhcp.h"

enum status
{
	SUCCESS = 0,
	FAILURE
};

enum node_state
{
	OCCUPIED = 0,
	VACANT
};

enum node_side
{
	LEFT = 0, /* do NOT change these values */
	RIGHT
};

typedef struct dhcp_node dhcp_node_t;

struct dhcp
{
	uint32_t net_address;
	uint32_t mask_bit_size;
	dhcp_node_t *root;
};

struct dhcp_node
{
	dhcp_node_t *child[2];
    int node_state;	  
};

/*-----------------------------Utility functions declaration----------------------------*/

static unsigned EndianMirror(unsigned num);
static unsigned SetBit(unsigned num, int index, int state);
static void DestroyNode(dhcp_node_t *node);
static dhcp_node_t *CreateNode(dhcp_node_t *node);
static int HasAvailableAddress(dhcp_t *dhcp);
static int Height(dhcp_t *dhcp);

static dhcp_node_t *CreateReservedAddress(dhcp_node_t *node, 
								   		  int height, 
								   		  int first_bit, 
								   		  int last_bit,
										  int *status);

static dhcp_node_t *CreateAddress(dhcp_node_t *node,
								  int height,
								  uint32_t *ip_address);

static dhcp_node_t *ReleaseAddress(dhcp_t *dhcp,
								   dhcp_node_t *node,
						    	   int height,
						    	   uint32_t ip_address);

static int IsAddressExist(dhcp_node_t *node,
						  int height,
						  uint32_t ip_address,
						  int status);

dhcp_node_t *ReleaseBranch(dhcp_t *dhcp, 
						   dhcp_node_t *node,
						   int height,
						   uint32_t ip_address);

/*-----------------------------------------------------------------------------*/

dhcp_t *DhcpCreate(const char *net_address, unsigned int mask_bits_size)
{
	dhcp_t *dhcp = NULL;
	int status = 0;
	
	dhcp = (dhcp_t*)malloc(sizeof(dhcp_t));

	if (NULL == dhcp)
	{
		return (NULL);
	}

	inet_pton(AF_INET, net_address, &dhcp->net_address);

	dhcp->root = (dhcp_node_t*)malloc(sizeof(dhcp_node_t));

	if (NULL == dhcp->root)
	{
		free(dhcp);
		return (NULL);
	}
	
	dhcp->mask_bit_size = mask_bits_size;
	
	dhcp->root->child[0] = dhcp->root->child[1] = NULL;
	dhcp->root->node_state = VACANT;

	/* allocates reserved addresses (first and last two) */
	CreateReservedAddress(dhcp->root, Height(dhcp), 0, 0, &status);
	CreateReservedAddress(dhcp->root, Height(dhcp), 1, 0, &status);
	CreateReservedAddress(dhcp->root, Height(dhcp), 1, 1, &status);

	if (FAILURE == status)
	{
		DhcpDestroy(dhcp);
		dhcp = NULL;
	}
	
	return (dhcp);
}

/*-----------------------------------------------------------------------------*/

void DhcpDestroy(dhcp_t *dhcp)
{
	assert(dhcp);

	DestroyNode(dhcp->root);
	free(dhcp);
}

/*-----------------------------------------------------------------------------*/

int DhcpGetAddress(dhcp_t *dhcp, uint32_t* ip_address)
{	
	int status = 0;

	assert(dhcp);

	if (!HasAvailableAddress(dhcp))
	{	
		return (FAILURE);
	}

	CreateAddress(dhcp->root, Height(dhcp), ip_address);
		
	*ip_address = EndianMirror(*ip_address) | dhcp->net_address;
	
	/* in case address allocation failed, releases the nodes along the branch
	   if possible */ 			
	if (!IsAddressExist(dhcp->root, Height(dhcp), *ip_address, status))
	{
		ReleaseBranch(dhcp, dhcp->root, Height(dhcp), *ip_address);

		return (FAILURE);
	}

	return (SUCCESS);
}

/*-----------------------------------------------------------------------------*/

void DhcpReleaseAddress(dhcp_t *dhcp, uint32_t ip_address)
{
	int status = 0;

	assert(dhcp);

	ip_address = EndianMirror(ip_address) & ((1u << Height(dhcp)) - 1);

	if (IsAddressExist(dhcp->root, Height(dhcp), ip_address, status))
	{
		ReleaseAddress(dhcp, dhcp->root, Height(dhcp), ip_address);
	}
}

/*-----------------------------------------------------------------------------*/

unsigned int DhcpRenewAddress(dhcp_t *dhcp, uint32_t ip_address)
{
	(void)ip_address;
	(void)dhcp;

	return (0xFFFFFFFF);
}

/*-----------------------------------------------------------------------------*/

static void DestroyNode(dhcp_node_t *node)
{
	if (node == NULL)
	{
		return;	
	}

	DestroyNode(node->child[LEFT]);
	DestroyNode(node->child[RIGHT]);
	free(node);
}

/*-----------------------------------------------------------------------------*/

static dhcp_node_t *CreateAddress(dhcp_node_t *node, int height, uint32_t *ip_address)
{
	/* allocation failed */
	if (NULL == node)
	{
		return (node);
	}

	/* address was created */
	if (height == 0)
	{
		node->node_state = OCCUPIED;

		return (node);
	}
	
	/* goes left if it's vacant or it doesn't exist */
	if (!node->child[LEFT] || node->child[LEFT]->node_state == VACANT)		
	{
		if (!node->child[LEFT])
		{
			node->child[LEFT] = CreateNode(node->child[LEFT]);
		}

		*ip_address = SetBit(*ip_address << 1, 0, LEFT);
		 
		node->child[LEFT] = CreateAddress(node->child[LEFT],
										  height - 1,
										  ip_address);		
	}

	/* goes right if it's vacant or it doesn't exist */
	else if (!node->child[RIGHT] || node->child[RIGHT]->node_state == VACANT)		
	{
		if (!node->child[RIGHT])
		{
			node->child[RIGHT] = CreateNode(node->child[RIGHT]);
		}

		*ip_address = SetBit(*ip_address << 1, 0, RIGHT);

		node->child[RIGHT] = CreateAddress(node->child[RIGHT],
										   height - 1,
										   ip_address);		
	}
		
	/* sets the branch to OCCUPIED if both children are OCCUPIED */
	if ((node->child[LEFT] && node->child[RIGHT]) &&
		 node->child[LEFT]->node_state == OCCUPIED && 
		 node->child[RIGHT]->node_state == OCCUPIED)
	{
		node->node_state = OCCUPIED;
	}

	return (node);
}

/*-----------------------------------------------------------------------------*/

static dhcp_node_t *ReleaseAddress(dhcp_t *dhcp, 
								   dhcp_node_t *node,
								   int height,
								   uint32_t ip_address)
{
	uint32_t side = !!(ip_address & (1u << ((uint32_t)height - 1)));
	
	if (height == 0)
	{
		free(node);
		return (NULL);
	}
	
	node->child[side] = ReleaseAddress(dhcp,
									   node->child[side],
									   height - 1,
									   ip_address);
	
	if (node != dhcp->root && !node->child[LEFT] && !node->child[RIGHT])
	{
		free(node);
		return (NULL);
	}

	node->node_state = VACANT;

	return (node);	
}

/*-----------------------------------------------------------------------------*/

static int IsAddressExist(dhcp_node_t *node,
						  int height,
						  uint32_t ip_address,
						  int status)
{
	uint32_t side = !!(ip_address & (1u << ((uint32_t)height - 1)));

	if (height == 0 && node)
	{		
		return (1);
	}

	if(node->child[side])
	{
		return  (IsAddressExist(node->child[side], height - 1, ip_address, status));
	}

	return 0;
}

/*-----------------------------------------------------------------------------*/

static dhcp_node_t *CreateNode(dhcp_node_t *node)
{
	node = malloc(sizeof(dhcp_node_t));

	if (NULL == node)
	{
		return (NULL);
	}

	node->child[RIGHT] = node->child[LEFT] = NULL;
	node->node_state = VACANT;	

	return (node);		
}

/*-----------------------------------------------------------------------------*/

static dhcp_node_t *CreateReservedAddress(dhcp_node_t *node,
								   		  int height,
								   		  int first_bit,
								   		  int last_bit,
										  int *status)
{
	if (NULL == node)
	{
		*status = FAILURE;
		return (node);
	} 

	if (height == 0)
	{
		node->node_state = OCCUPIED;

		return (node);
	}

	/* goes in same direction until the last turn */
	if (height == 1)
	{
		if (!node->child[last_bit])
		{
			node->child[last_bit] = CreateNode(node->child[last_bit]);
		}

		node->child[last_bit] = CreateReservedAddress(node->child[last_bit],
													  height - 1,
													  first_bit,
													  last_bit,
													  status);
	}
	else
	{
		if (!node->child[first_bit])
		{
			node->child[first_bit] = CreateNode(node->child[first_bit]);
		}

		node->child[first_bit] = CreateReservedAddress(node->child[first_bit],
													   height - 1,
													   first_bit,
													   last_bit,
													   status);
	}

	/* sets the branch to OCCUPIED if both children are OCCUPIED */
	if ((node->child[LEFT] && node->child[RIGHT]) &&
		 node->child[LEFT]->node_state == OCCUPIED && 
		 node->child[RIGHT]->node_state == OCCUPIED)
	{
		node->node_state = OCCUPIED;
	}

	return (node);
}

/*-----------------------------------------------------------------------------*/

dhcp_node_t *ReleaseBranch(dhcp_t *dhcp, 
						   dhcp_node_t *node,
						   int height,
						   uint32_t ip_address)
{
	uint32_t side = !!(ip_address & (1u << ((uint32_t)height - 1)));

	if (node == NULL)
	{
		return (node);
	}

	node->child[side] = ReleaseBranch(dhcp,
									  node->child[side],
									  height - 1,
									  ip_address);
	
	/* releases the node if it's not the root or it has no children */
	if (node != dhcp->root && !node->child[LEFT] && !node->child[RIGHT])
	{
		free(node);
		return (NULL);
	}

	node->node_state = VACANT;

	return (node);	
}

/*-----------------------------------------------------------------------------*/

static int Height(dhcp_t *dhcp)
{
	return (32 - dhcp->mask_bit_size);
}

/*-----------------------------------------------------------------------------*/

static int HasAvailableAddress(dhcp_t *dhcp)
{
	return (dhcp->root->node_state);
}

/*-----------------------------------------------------------------------------*/

static unsigned SetBit(unsigned num, int index, int state)
{
	return ((num & ~(1ul << index)) | (state << index));
} 

/*-----------------------------------------------------------------------------*/

static unsigned EndianMirror(unsigned num)
{
	num = ((num << 16) | (num >> 16));

	num = (((num & 0x00FF00FF) << 8)) | (((num & 0xFF00FF00) >> 8));

	return (num);
}


