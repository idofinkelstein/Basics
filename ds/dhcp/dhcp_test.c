/**************************
File name: dhcp_test.c
Author: Ido Finkelstein
Date: 21/8/2020
Reviewer:
***************************/

#include <stdio.h>		/* printf */
#include <arpa/inet.h>  /* inet_ntop	*/

#include "dhcp.h"

void TestCase1(void);

int main()
{
	TestCase1();	

	return 0;
}

/* allocates and deallocates ip addresses */
void TestCase1(void)
{
	dhcp_t *dhcp = NULL;
	uint32_t ip_address[100] = {0};
	uint32_t  new_ip = 0;
	size_t size = sizeof(ip_address) / sizeof(uint32_t);
	size_t i = 0;
	char str[INET_ADDRSTRLEN] = {0};
	int status = 0;

	dhcp = DhcpCreate("192.168.1.0", 26);

	/* allocates addresses until pool is full */
	for (i = 0; (i < size) && !status; ++i)
	{
		status = DhcpGetAddress(dhcp, &ip_address[i]);
		inet_ntop(AF_INET, &ip_address[i], str, INET_ADDRSTRLEN);
		puts(str);
	}

	DhcpReleaseAddress(dhcp, ip_address[5]);
	DhcpReleaseAddress(dhcp, ip_address[2]);
	
	/* tries to release already released addresses */
	DhcpReleaseAddress(dhcp, ip_address[5]);
	DhcpReleaseAddress(dhcp, ip_address[2]);

	DhcpGetAddress(dhcp, &new_ip);

	inet_ntop(AF_INET, &new_ip, str, INET_ADDRSTRLEN);
	puts(str);
	new_ip = 0;

	DhcpGetAddress(dhcp, &new_ip);

	inet_ntop(AF_INET, &new_ip, str, INET_ADDRSTRLEN);
	puts(str);
	
	DhcpDestroy(dhcp);
}
