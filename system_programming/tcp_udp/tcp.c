/* File Name   : tcp.c
 * Developer   : Ido Finkelstein
 * Reviewer    : 
 * Review Date : 9.11.20
 */

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
#define MAXLINE 1024

int main(int argc, char const *argv[])
{
    int sockfd; 
    char buffer[MAXLINE]; 
    char *ping = "ping";
    char *pong = "pong"; 
    struct sockaddr_in server_addr, client_addr;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    int status;
    int n;
    unsigned int len;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;


if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0)
{
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
}

    /* Creating socket file descriptor */
    if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0))) /* TCP protocol */
    { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    }



    return 0;
}
