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

int main(int argc, char const *argv[])
{
    int udp_sockfd, tcp_sockfd, new_fd; 
    char *buffer; 
    char *ping = "ping\n";
    char *pong = "hi janna!!!\n"; 
    
    struct addrinfo udp_hints, tcp_hints;
    struct addrinfo *udp_servinfo, tcp_servinfo;
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    int status;
    unsigned int len = strlen(pong);

    if (argc != 2)
    {
        return 0;
    }


   

    return 0;
}

void InitAddrInfo()
{
     memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo("10.1.0.33", "9000", &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

}
