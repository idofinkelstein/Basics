/* File Name   : udp.c
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

#define PORT 9000
#define MAXLINE 1024

int main(int argc, char *argv[]) 
{
    int sockfd; 
    char buffer[MAXLINE]; 
    char *ping = "ping";
    char *pong = "pong"; 
    struct sockaddr_in server_addr, client_addr;
    int n;
    unsigned int len;

    if (argc > 1)
    {
        /* Creating socket file descriptor */
        if (-1 == (sockfd = socket(AF_INET, SOCK_DGRAM, 0))) /* UDP protocol */
        { 
            perror("socket creation failed"); 
            exit(EXIT_FAILURE); 
        }

        memset(&server_addr, 0, sizeof(server_addr));
        memset(&client_addr, 0, sizeof(client_addr));

        /* Filling server information */
        server_addr.sin_family = AF_INET; 
        server_addr.sin_port = htons(PORT); 
        server_addr.sin_addr.s_addr = INADDR_ANY;

        /* enters client application */
        if (0 == strcmp(argv[1], "client"))
        {
            printf("client\n");  
            
            sendto(sockfd, (const char *)ping, strlen(ping), 
                   MSG_CONFIRM, (const struct sockaddr *) &server_addr,  
                   sizeof(server_addr)); 
            printf("Ping message sent.\n"); 
                
            n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                        MSG_WAITALL, (struct sockaddr *) &server_addr, 
                        &len); 
            buffer[n] = '\0'; 
            printf("Server : %s\n", buffer); 
        
            close(sockfd); 
        }
        /* enters server application */
        else if (0 == strcmp(argv[1], "server"))
        {
            printf("server\n");
            
            /* Bind the socket with the server address */
            if (-1 == bind(sockfd, 
                          (const struct sockaddr *)&server_addr, 
                           sizeof(server_addr))) 
            { 
                perror("bind failed"); 
                exit(EXIT_FAILURE); 
            } 
        
            len = sizeof(client_addr);
        
            n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                        MSG_WAITALL, ( struct sockaddr *) &client_addr, 
                        &len); 
            buffer[n] = '\0'; 
            printf("Client : %s\n", buffer); 
            sendto(sockfd, (const char *)pong, strlen(pong),  
                   MSG_CONFIRM, (const struct sockaddr *)&client_addr, 
                   len); 
            printf("Pong message sent.\n");  
        }
    }
    else
    {
        printf("change arguments and start again\n");
    }

    return (0);
}