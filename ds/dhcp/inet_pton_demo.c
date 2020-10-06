/* IPv4 demo of inet_ntop() and inet_pton() */

#include <arpa/inet.h>
#include <stdio.h>

struct sockaddr_in sa;
char str[INET_ADDRSTRLEN];

unsigned BitArrMirror(unsigned num)
{
	num = ((num << 16) | (num >> 16));

	num = (((num & 0x00FF00FF) << 8)) | (((num & 0xFF00FF00) >> 8));

	num = (((num & 0x0F0F0F0F) << 4)) | (((num & 0xF0F0F0F0) >> 4));

	num = (((num & 0x33333333) << 2)) | (((num & 0xCCCCCCCC) >> 2));

	num = (((num & 0x55555555) << 1)) | (((num & 0xAAAAAAAA) >> 1));
	
	return (num);
}

int main()
{
	unsigned addr = 0;
	/* store this IP address in sa: */
	inet_pton(AF_INET, "255.0.0.0", &addr);
	printf("%u\n", addr);
	/* now get it back and print it */
	addr  =  addr | BitArrMirror(addr);
	inet_ntop(AF_INET, &addr, str, INET_ADDRSTRLEN);
	printf("%u\n", addr);
	printf("%s\n", str); /* prints "192.0.2.33" */	
	printf("%d\n", INET_ADDRSTRLEN);
	return 0;

}
