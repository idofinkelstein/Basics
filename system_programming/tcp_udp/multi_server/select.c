#define _DEFAULT_SOURCE
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <netdb.h>

#define PORT 9000
#define BUFF_SIZE 1024

void InitAddrInfo(struct addrinfo* hints, int socktype);


int main()
{
    int udp_sockfd, tcp_sockfd, new_fd; 
    char *tcp_buff, *udp_buff; 
    char *ping = "ping\n";
    char *pong = "hi janna!!!\n"; 
    
    struct addrinfo udp_hints, tcp_hints;
    struct addrinfo *udp_servinfo, *tcp_servinfo;
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    int status;
    unsigned int len = strlen(pong);

    InitAddrInfo(&tcp_hints, SOCK_STREAM);
    InitAddrInfo(&udp_hints, SOCK_DGRAM);


    if ((status = getaddrinfo(NULL, "9000", &udp_hints, &udp_servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }
    if ((status = getaddrinfo(NULL, "9000", &tcp_hints, &tcp_servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    /* Creating socket file descriptor */
    if (-1 == (udp_sockfd = socket(udp_servinfo->ai_family, udp_servinfo->ai_socktype, 0))) /* TCP protocol */
    { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    }
    if (-1 == (tcp_sockfd = socket(tcp_servinfo->ai_family, tcp_servinfo->ai_socktype, 0))) /* TCP protocol */
    { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    }

    if (-1 == bind(udp_sockfd, udp_servinfo->ai_addr, udp_servinfo->ai_addrlen))
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (-1 == bind(tcp_sockfd, tcp_servinfo->ai_addr, tcp_servinfo->ai_addrlen))
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (-1 == listen(tcp_sockfd, 5))
    {
        perror("listen"); 
        exit(EXIT_FAILURE);
    }

    return 0;
}

void InitAddrInfo(struct addrinfo* hints, int socktype)
{
    memset(hints, 0, sizeof(hints));
    hints->ai_family = AF_INET;
    hints->ai_socktype = socktype;
    hints->ai_flags = AI_PASSIVE;
}
