/*
    DHCP API to support DHCP server application for creating, destroying, receiving and releasing IP addresses to hosts in the network.

    Functionality includes:
        - GetAddress: returns a new IP address to assign to host
        - ReleaseAddress: releases a given IP address and returns it to the   
                          pool
        - RenewAddress: TBD - renews a lease of IP address of a client 
*/

#ifndef ILRD_DHCP_H
#define ILRD_DHCP_H

#include <stdint.h>	    /* uint32_t */

/*version 1.0  mentor approval */

typedef struct dhcp dhcp_t;

/*---------------------------------------------------------------------------*/
/* DhcpCreate:
*   - creates a new dhcp.
*
* Args:
*	- net_address - the base IP address prefix for all addresses in the pool
*   - net_mask - number of bits set in the IP address to assign.
*
* Return Value:
*   - returns a hanlde to the dhcp, or NULL if failed.
*
* Comments:
*   - see example of use: 
*       dhcp_t *dhcp = DhcpCreate("192.168.0.0", 24);
*     the prefix address is 192.168.0.X, number of bits in prefix is 24.
*/
dhcp_t *DhcpCreate(const char *net_address, unsigned int mask_bits_size);

/*---------------------------------------------------------------------------*/
/* HashDestroy:
*   - destroys the dhcp.
*
* Args:
*   - dhcp - handle to the dhcp to be destroyed
*
*/
void DhcpDestroy(dhcp_t *dhcp);

/*---------------------------------------------------------------------------*/
/* DhcpGetAddress:
*   - returns new IP address.
* 
* Args:
*   - dhcp - handle to the dhcp
	- ip_address - the returned ip address
*  
* Return Value:
*   - 0 if function succeeded
*   - 1 if function failed
*
*/
int DhcpGetAddress(dhcp_t *dhcp, uint32_t* ip_address);

/*---------------------------------------------------------------------------*/
/* DhcpReleaseAddress:
*   - releases a given IP address.
* 
* Args:
*   - dhcp - handle to the dhcp 
*   - ip_address - the IP address to release
*
*/
void DhcpReleaseAddress(dhcp_t *dhcp, uint32_t ip_address);

/*---------------------------------------------------------------------------*/
/* TBD */
/* DhcpRenewAddress:
*   - renews the lease for the given IP address
* 
* Args:
*   - dhcp - handle to the dhcp 
*   - ip_address - the IP address to renew
*  
* Return Value:
*   - TBD if function returns address or if return value is void
*
*/
unsigned int DhcpRenewAddress(dhcp_t *dhcp, uint32_t ip_address);

/*---------------------------------------------------------------------------*/

#endif /* ILRD_DHCP_H */
