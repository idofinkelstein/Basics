/* File Name   : tcp.c
 * Developer   : Ido Finkelstein
 * Reviewer    : 
 * Review Date : 9.11.20
 */
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
    int sockfd, new_fd; 
    char *buffer; 
    char *ping = "ping\n";
    char *pong = "hi janna!!!\n"; 
    
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct sockaddr_storage their_addr;
    socklen_t addr_size;
    int status;
    unsigned int len = strlen(pong);

    if (argc != 2)
    {
        return 0;
    }


    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;


    if ((status = getaddrinfo("127.0.0.1", "9998", &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    /* Creating socket file descriptor */
    if (-1 == (sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, 0))) /* TCP protocol */
    { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    }

    buffer = malloc(BUFF_SIZE);
    if(NULL == buffer)
    {
        perror("malloc failed"); 
        close(sockfd);
        exit(EXIT_FAILURE); 
    }

    if (0 == strcmp(argv[1], "server")) /* we are the server */
    {
        if (-1 == bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen))
        {
            perror("bind");
            free(buffer); 
            exit(EXIT_FAILURE);
        }

        if (-1 == listen(sockfd, 5))
        {
            perror("listen"); 
            free(buffer); 
            exit(EXIT_FAILURE);
        }

        addr_size = sizeof(struct sockaddr_storage);

        if (-1 == (new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size)))
        {
            perror("accept"); 
            free(buffer); 
            exit(EXIT_FAILURE);
        }

        while (1)
        {

            if(-1 == recv(new_fd, buffer, BUFF_SIZE, 0))
            {
                perror("recv");
                free(buffer);  
                close(sockfd);
                close(new_fd);
                exit(EXIT_FAILURE);
            }

            sleep(1);
            write(1, buffer, len);

            if (-1 == send(new_fd, pong, len, 0))
            {
                perror("send");
                free(buffer); 
                close(sockfd);
                close(new_fd);
                exit(EXIT_FAILURE);
            }
        }
    }
    else if (0 == strcmp(argv[1], "client")) /* we are the client */
    {
        if (-1 == connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen))
        {
            perror("connect");
            free(buffer); 
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        while(1)
        {
            if (-1 == send(sockfd, ping, len, 0))
            {
                perror("send");
                free(buffer); 
                close(sockfd);
                exit(EXIT_FAILURE);
            }
            if(-1 == recv(sockfd, buffer,len, 0))
            {
                perror("recv");
                free(buffer); 
                close(sockfd);
                exit(EXIT_FAILURE);
            }

            sleep(1);
            write(1, buffer, len);
        }

        close(sockfd);

    }
    return 0;
}
