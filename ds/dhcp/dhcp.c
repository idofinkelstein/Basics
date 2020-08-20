#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <assert.h>

#include "dhcp.h"

char str[INET_ADDRSTRLEN] = {0};


enum node_state
{
	OCCUPIED = 0,
	VACANT
};

enum node_side
{
	LEFT = 0,
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

unsigned EndianMirror(unsigned num);
unsigned SetBit(unsigned num, int index, int state);
dhcp_node_t *CreateAddress(dhcp_node_t *node, int height, uint32_t *ip_address);
dhcp_node_t *CreateReservedAddress(dhcp_node_t *node, int height, int first_bit, int last_bit);
dhcp_node_t *CreateNode(dhcp_node_t *node);
int HasAvailableAddress(dhcp_t *dhcp);
int Height(dhcp_t *dhcp);
dhcp_node_t *ReleaseAddress(dhcp_t *dhcp, dhcp_node_t *node, int height, uint32_t ip_address);
int IsAddressExist(dhcp_node_t *node, int height, uint32_t ip_address, int status);
void DestroyNode(dhcp_node_t *node);

dhcp_t *DhcpCreate(const char *net_address, unsigned int mask_bits_size)
{
	dhcp_t *dhcp = NULL;
	
	dhcp = (dhcp_t*)malloc(sizeof(dhcp_t));

	if (NULL == dhcp)
	{
		return (NULL);
	}

	inet_pton(AF_INET, net_address, &dhcp->net_address);

	dhcp->root = malloc(sizeof(dhcp_node_t));
	
	dhcp->mask_bit_size = mask_bits_size;
	
	dhcp->root->child[0] = dhcp->root->child[1] = NULL;
	dhcp->root->node_state = VACANT;

	inet_ntop(AF_INET, &dhcp->net_address, str, INET_ADDRSTRLEN);

	/* allocates reserved addresses */
	CreateReservedAddress(dhcp->root, Height(dhcp), 0, 0);
	CreateReservedAddress(dhcp->root, Height(dhcp), 1, 0);
	CreateReservedAddress(dhcp->root, Height(dhcp), 1, 1);
	
	return (dhcp);
}

void DhcpDestroy(dhcp_t *dhcp)
{
	assert(dhcp);

	DestroyNode(dhcp->root);
	free(dhcp);
}

int DhcpGetAddress(dhcp_t *dhcp, uint32_t* ip_address)
{	
	assert(dhcp);

	if (HasAvailableAddress(dhcp))
	{	
		CreateAddress(dhcp->root, Height(dhcp), ip_address);

		/**ip_address = *ip_address + (*ip_address & ((1u << Height(dhcp)) - 1));*/
		
		*ip_address = EndianMirror(*ip_address) | dhcp->net_address;
	
		inet_ntop(AF_INET, ip_address, str, INET_ADDRSTRLEN);
	
		printf("%s\n", str);

		return 0;
	}

	return 1;
}

void DhcpReleaseAddress(dhcp_t *dhcp, uint32_t ip_address)
{
	int status = 0;

	assert(dhcp);

	inet_ntop(AF_INET, &ip_address, str, INET_ADDRSTRLEN);

	ip_address = EndianMirror(ip_address);

	ip_address = ip_address & ((1u << Height(dhcp)) - 1);

	if (IsAddressExist(dhcp->root, Height(dhcp), ip_address, status))
	{
		ReleaseAddress(dhcp, dhcp->root, Height(dhcp), ip_address);
	}

	return;
}

unsigned int DhcpRenewAddress(dhcp_t *dhcp, uint32_t ip_address)
{
	(void)ip_address;
	(void)dhcp;

	return 0xFFFFFFFF;
}

void DestroyNode(dhcp_node_t *node)
{
	if (node == NULL)
	{
		return;	
	}

	DestroyNode(node->child[0]);
	DestroyNode(node->child[1]);
	free(node);
}

dhcp_node_t *CreateAddress(dhcp_node_t *node, int height, uint32_t *ip_address)
{
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
		 
		node->child[LEFT] = CreateAddress(node->child[LEFT], height - 1, ip_address);		
	}

	/* goes right if it's vacant or it doesn't exist */
	else if (!node->child[RIGHT] || node->child[RIGHT]->node_state == VACANT)		
	{
		if (!node->child[RIGHT])
		{
			node->child[RIGHT] = CreateNode(node->child[RIGHT]);
		}

		*ip_address = SetBit(*ip_address << 1, 0, RIGHT);

		node->child[RIGHT] = CreateAddress(node->child[RIGHT], height - 1, ip_address);		
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

dhcp_node_t *ReleaseAddress(dhcp_t *dhcp, dhcp_node_t *node, int height, uint32_t ip_address)
{
	uint32_t side = !!(ip_address & (1u << ((uint32_t)height - 1)));
	
	if (height == 0)
	{
		node->node_state = VACANT;
		free(node);
		return (NULL);
	}
	
	node->child[side] = ReleaseAddress(dhcp, node->child[side], height - 1, ip_address);
	
	if (node != dhcp->root && !node->child[LEFT] && !node->child[RIGHT])
	{
		free(node);
		return (NULL);
	}

	node->node_state = VACANT;

	return (node);	
}

int IsAddressExist(dhcp_node_t *node, int height, uint32_t ip_address, int status)
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

dhcp_node_t *CreateNode(dhcp_node_t *node)
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

dhcp_node_t *CreateReservedAddress(dhcp_node_t *node, int height, int first_bit, int last_bit)
{
	if (height == 0)
	{
		node->node_state = OCCUPIED;

		return (node);
	}

	if (height == 1)
	{
		if (!node->child[last_bit])
		{
			node->child[last_bit] = CreateNode(node->child[last_bit]);
		}

		node->child[last_bit] = CreateReservedAddress(node->child[last_bit], height - 1, first_bit, last_bit);
	}
	else
	{
		if (!node->child[first_bit])
		{
			node->child[first_bit] = CreateNode(node->child[first_bit]);
		}

		node->child[first_bit] = CreateReservedAddress(node->child[first_bit], height - 1, first_bit, last_bit);
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

int Height(dhcp_t *dhcp)
{
	return (32 - dhcp->mask_bit_size);
}

int HasAvailableAddress(dhcp_t *dhcp)
{
	return (dhcp->root->node_state);
}

unsigned SetBit(unsigned num, int index, int state)
{
	return ((num & ~(1ul << index)) | (state << index));
} 

unsigned EndianMirror(unsigned num)
{
	num = ((num << 16) | (num >> 16));

	num = (((num & 0x00FF00FF) << 8)) | (((num & 0xFF00FF00) >> 8));

	return (num);
}
