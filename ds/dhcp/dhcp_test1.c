#include <stddef.h> /* NULL */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* exit */
#include <arpa/inet.h>  /* inet_pton */

#include "dhcp.h"

static void TestCreateAndDestroy(void);
static void TestGetAddress(void);
static void TestReleaseAddress(void);


static void TestCase1(void);
static void TestCase2(void);


#define EXIT_IF_FAILED(COND, MSG, RET) if (COND) {printf(MSG); exit(RET);}
#define MESSAGE_IF_FAILED(COND, MSG) if (COND) {printf(MSG);}

int main()
{
    TestCreateAndDestroy();
    TestGetAddress();
    TestReleaseAddress();
    
    TestCase1();    
    TestCase2();    

    return (0);
}

static void TestCreateAndDestroy(void)
{
    dhcp_t *dhcp = NULL;
        
    dhcp = DhcpCreate("186.2.85.0", 30);
    EXIT_IF_FAILED(NULL == dhcp, "creation failed!", 1);
    
    DhcpDestroy(dhcp);
}

static void TestGetAddress(void)
{
    dhcp_t *dhcp = NULL;
    uint32_t ip_address1 = 0;    
    uint32_t ip_address2 = 0;    
    uint32_t ip_address3 = 0;    
    char *base_address = "186.161.33.0";

    char str1[16] = {0};
    char str2[16] = {0};
    char str3[16] = {0};
    
    dhcp = DhcpCreate(base_address, 29);
    
    printf("base ip address is: %s\n", base_address);
    EXIT_IF_FAILED(NULL == dhcp, "creation failed!", 1);

    MESSAGE_IF_FAILED(1 == DhcpGetAddress(dhcp, &ip_address1), 
                     "didn't get address\n");

    inet_ntop(AF_INET, &ip_address1, str1, INET_ADDRSTRLEN);
    printf("ip allocated      : %s\n", str1);

    MESSAGE_IF_FAILED(1 == DhcpGetAddress(dhcp, &ip_address2), 
                     "didn't get address\n");

    inet_ntop(AF_INET, &ip_address2, str2, INET_ADDRSTRLEN);
    printf("next ip allocated : %s\n", str2);
    
    MESSAGE_IF_FAILED(1 == DhcpGetAddress(dhcp, &ip_address3),
                     "didn't get address\n");
    inet_ntop(AF_INET, &ip_address3, str3, INET_ADDRSTRLEN);
    printf("next ip allocated : %s\n", str3);
    
    DhcpDestroy(dhcp); 

}

static void TestReleaseAddress(void)
{
    dhcp_t *dhcp = NULL;
    uint32_t ip_address1 = 0;    

    dhcp = DhcpCreate("255.2.85.0", 30);
    EXIT_IF_FAILED(NULL == dhcp, "creation failed!", 1);
    
    MESSAGE_IF_FAILED(1 == DhcpGetAddress(dhcp, &ip_address1), 
                      "didn't get address\n");
    
    
    DhcpReleaseAddress(dhcp, ip_address1);

    DhcpDestroy(dhcp);

}

/* this test case only checking functionality of dhcp */
static void TestCase1(void)
{
    int status = 0;
    dhcp_t *dhcp = NULL;
    uint32_t ip_address = 0;

    dhcp = DhcpCreate("192.168.168.0", 30);
    EXIT_IF_FAILED(NULL == dhcp, "creation failed!", 1);
    
    status = DhcpGetAddress(dhcp, &ip_address);
    MESSAGE_IF_FAILED(1 == status, "didn't get address");
    
    DhcpReleaseAddress(dhcp, ip_address);

    DhcpDestroy(dhcp);
}


/* this test case check what happen when tring to assign more addresses 
   than the user allowed */
   
static void TestCase2(void)
{
    int status = 0;
    int i = 0;
    dhcp_t *dhcp = NULL;
    uint32_t ip_address = 0;

    dhcp = DhcpCreate("192.168.168.0", 28);
    EXIT_IF_FAILED(NULL == dhcp, "creation failed!", 1);
    printf(" next test should print didn't get address twice:\n\n");
    /* asign 15 addresses from 13 available (3 already reserved) */
    for(i = 0; i < 15; ++i)
    {
        status = DhcpGetAddress(dhcp, &ip_address);
        MESSAGE_IF_FAILED(1 == status, "didn't get address\n");
    }

    /* destroy dhcp without releasing addresses*/
    DhcpDestroy(dhcp);
}


/* need to add test what is the pool is not large enough only for 
   permanent addresses??? is it undefined behivor? */
