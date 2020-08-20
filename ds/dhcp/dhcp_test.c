#include <stdio.h>

#include "dhcp.h"

int main()
{
	dhcp_t *dhcp = NULL;
	uint32_t ip_address[20] = {0};
	uint32_t  new_ip = 0;

	dhcp = DhcpCreate("192.168.1.0", 27);

	DhcpGetAddress(dhcp, &ip_address[0]);
	
	DhcpGetAddress(dhcp, &ip_address[1]);
	
	DhcpGetAddress(dhcp, &ip_address[2]);

	DhcpGetAddress(dhcp, &ip_address[3]);

	DhcpGetAddress(dhcp, &ip_address[4]);

	DhcpGetAddress(dhcp, &ip_address[5]);

	DhcpGetAddress(dhcp, &ip_address[6]);

	DhcpGetAddress(dhcp, &ip_address[7]);

	DhcpGetAddress(dhcp, &ip_address[8]);

	DhcpGetAddress(dhcp, &ip_address[9]);

	DhcpGetAddress(dhcp, &ip_address[10]);

	DhcpGetAddress(dhcp, &ip_address[11]);

	DhcpGetAddress(dhcp, &ip_address[12]);

	DhcpGetAddress(dhcp, &ip_address[13]);

	DhcpGetAddress(dhcp, &ip_address[14]);

	DhcpGetAddress(dhcp, &ip_address[15]);
	
	DhcpReleaseAddress(dhcp, ip_address[5]);
	DhcpReleaseAddress(dhcp, ip_address[2]);
	DhcpReleaseAddress(dhcp, ip_address[5]);
	DhcpReleaseAddress(dhcp, ip_address[2]);

	DhcpGetAddress(dhcp, &new_ip);

	DhcpGetAddress(dhcp, &ip_address[16]);

	DhcpGetAddress(dhcp, &ip_address[17]);

	DhcpGetAddress(dhcp, &ip_address[18]);

	DhcpGetAddress(dhcp, &ip_address[19]);

	DhcpDestroy(dhcp);

	return 0;
}
