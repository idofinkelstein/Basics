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

#include "avl.h"

#define PORT 9000
#define BUFF_SIZE 1024
#define MAX(a, b) ((a) > (b): (a) ? (b))

typedef int (*fd_oper_t)(int);

void InitAddrInfo(struct addrinfo* hints, int socktype);
int Compare(const void *data1, const void *data2, void *param);

typedef struct data
{
    int sockfd;
    fd_oper_t action;

}data_t;


typedef struct select_reactor
{
    int max_fd;
    avl_t *dict;
    fd_set *master;

}select_reactor_t;


int main()
{
    int udp_sockfd, tcp_sockfd, new_fd, stdin_fd = 0; 
    char *tcp_buff, *udp_buff; 
    char *ping = "ping\n";
    char *pong = "hi janna!!!\n";     
    struct addrinfo udp_hints, tcp_hints;
    struct addrinfo *udp_servinfo, *tcp_servinfo;
    struct sockaddr_storage their_addr;
    int status, socket_opt = 1;
    unsigned int len = strlen(pong);
    socklen_t addr_size;
    avl_t *fd_dict = NULL;
    fd_set work, master;

    InitAddrInfo(&tcp_hints, SOCK_STREAM);
    InitAddrInfo(&udp_hints, SOCK_DGRAM);

    fd_dict = AVLCreate(Compare, NULL);
    if (NULL == fd_dict)
    {
        return (1);
    }

    if ((status = getaddrinfo(NULL, "9000", &udp_hints, &udp_servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        AVLDestroy(fd_dict);
        exit(1);
    }
    if ((status = getaddrinfo(NULL, "9000", &tcp_hints, &tcp_servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        AVLDestroy(fd_dict);
        exit(1);
    }

    /* Creating UDP socket file descriptor */
    if (-1 == (udp_sockfd = socket(udp_servinfo->ai_family, udp_servinfo->ai_socktype, 0))) /* TCP protocol */
    { 
        perror("socket creation failed"); 
        AVLDestroy(fd_dict);
        exit(EXIT_FAILURE); 
    }
    /* Creating TCP socket file descriptor */
    if (-1 == (tcp_sockfd = socket(tcp_servinfo->ai_family, tcp_servinfo->ai_socktype, 0))) /* TCP protocol */
    { 
        perror("socket creation failed"); 
        AVLDestroy(fd_dict);
        exit(EXIT_FAILURE); 
    }

    if (-1 == setsockopt(udp_sockfd, SOL_SOCKET, SO_REUSEADDR, 
                         &socket_opt, sizeof(socket_opt)))
    {
        perror("setsockopt");
        AVLDestroy(fd_dict);
        exit(EXIT_FAILURE); 
    }

    if (-1 == setsockopt(tcp_sockfd, SOL_SOCKET, SO_REUSEADDR, 
                         &socket_opt, sizeof(socket_opt)))
    {
        perror("setsockopt");
        AVLDestroy(fd_dict);
        exit(EXIT_FAILURE); 
    }

    if (-1 == bind(udp_sockfd, udp_servinfo->ai_addr, udp_servinfo->ai_addrlen))
    {
        perror("udp bind");
        AVLDestroy(fd_dict);
        exit(EXIT_FAILURE);
    }

    if (-1 == bind(tcp_sockfd, tcp_servinfo->ai_addr, tcp_servinfo->ai_addrlen))
    {
        perror("tcp bind");
        AVLDestroy(fd_dict);
        exit(EXIT_FAILURE);
    }

    if (-1 == listen(tcp_sockfd, 5))
    {
        perror("listen");
        AVLDestroy(fd_dict);
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&master);
    FD_SET(tcp_sockfd, &master);
    FD_SET(udp_sockfd, &master);
    FD_SET(stdin_fd, &master);



    return 0;
}

void InitAddrInfo(struct addrinfo* hints, int socktype)
{
    memset(hints, 0, sizeof(*hints));
    hints->ai_family = AF_INET;
    hints->ai_socktype = socktype;
    hints->ai_flags = AI_PASSIVE;
}

int Compare(const void *data1, const void *data2, void *param)
{
    (void)param;
    return (*(int*)data1 - *(int*)data2);
}
