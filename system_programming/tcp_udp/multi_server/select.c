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
#define MAX_LINE 256
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct data data_t;
typedef struct select_reactor select_reactor_t;
typedef void (*fd_oper_t)(data_t *, select_reactor_t *);

struct data
{
    int sockfd;
    fd_oper_t action;
};

struct select_reactor
{
    int max_fd;
    avl_t *dict;
    fd_set master;
};


static struct timeval InitTimeVal(long seconds, long microseconds);
static void InitAddrInfo(struct addrinfo* hints, int socktype);
static void ReactorAddHandler(select_reactor_t *reactor_handle,
											  int sockfd, 
											  fd_oper_t action_func);

static void ReactorRemoveHandler(select_reactor_t *reactor_handle, data_t *data);
static void ReactorInit(select_reactor_t *reactor_handle);
static data_t *InitData(int sockfd, fd_oper_t action_func);
int Compare(const void *fd1, const void *fd2, void *param);

static void TCPHandler(data_t *data, select_reactor_t *reactor_handle);
static void UDPHandler(data_t *data, select_reactor_t *reactor_handle);
static void TCPAcceptHandler(data_t *data, select_reactor_t *reactor_handle);
static void StdInHandler(data_t *data, select_reactor_t *reactor_handle);

static void DestroyAllData(avl_t *dict);
static int DestroyData(void *data, void *param);
static void ErrorHandler(data_t *data, select_reactor_t *reactor_handle, const char *str);

struct sockaddr_storage their_addr;

int main()
{
    int i, udp_sockfd, tcp_sockfd, stdin_fd = 0; 
    struct addrinfo udp_hints, tcp_hints;
    struct addrinfo *udp_servinfo, *tcp_servinfo;
	struct timeval time = {0, 0};
    int status, socket_opt = 1;
	select_reactor_t reactorBlockHandler;
    fd_set work;

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

    /* Creating UDP socket file descriptor */
    if (-1 == (udp_sockfd = socket(udp_servinfo->ai_family, udp_servinfo->ai_socktype, 0))) /* TCP protocol */
    { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    }
    /* Creating TCP socket file descriptor */
    if (-1 == (tcp_sockfd = socket(tcp_servinfo->ai_family, tcp_servinfo->ai_socktype, 0))) /* TCP protocol */
    { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    }

    if (-1 == setsockopt(udp_sockfd, SOL_SOCKET, SO_REUSEADDR, 
                         &socket_opt, sizeof(socket_opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE); 
    }

    if (-1 == setsockopt(tcp_sockfd, SOL_SOCKET, SO_REUSEADDR, 
                         &socket_opt, sizeof(socket_opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE); 
    }

    if (-1 == bind(udp_sockfd, udp_servinfo->ai_addr, udp_servinfo->ai_addrlen))
    {
        perror("udp bind");
        exit(EXIT_FAILURE);
    }

    if (-1 == bind(tcp_sockfd, tcp_servinfo->ai_addr, tcp_servinfo->ai_addrlen))
    {
        perror("tcp bind");
        exit(EXIT_FAILURE);
    }

    if (-1 == listen(tcp_sockfd, 5))
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

   
	ReactorInit(&reactorBlockHandler);

    ReactorAddHandler(&reactorBlockHandler, stdin_fd, StdInHandler);
    ReactorAddHandler(&reactorBlockHandler, udp_sockfd, UDPHandler);
    ReactorAddHandler(&reactorBlockHandler, tcp_sockfd, TCPAcceptHandler);

	 while(1)
    {
        int stat = 0;

        work = reactorBlockHandler.master;
        stat = select(reactorBlockHandler.max_fd + 1, &work, NULL, NULL, &time);

        if(stat == -1)
        {
            printf("select failed\n");
            DestroyAllData(reactorBlockHandler.dict);
            close(tcp_sockfd); 
            exit(EXIT_FAILURE); 
        }
        else if(stat == 0)
        {
            printf("timeout\n");
        }

        time = InitTimeVal(5, 0);

        for(i = 0; i <= reactorBlockHandler.max_fd && stat > 0; ++i)
        {   
            if(FD_ISSET(i, &work))
            {
                data_t *data = (data_t *)AVLFind(reactorBlockHandler.dict, (data_t *)&i);
                data->action(data, &reactorBlockHandler);
            }
        }
    }
    DestroyAllData(reactorBlockHandler.dict);

    return 0;
}

void InitAddrInfo(struct addrinfo* hints, int socktype)
{
    memset(hints, 0, sizeof(*hints));
    hints->ai_family = AF_INET;
    hints->ai_socktype = socktype;
    hints->ai_flags = AI_PASSIVE;
}

static void ReactorAddHandler(select_reactor_t *reactor_handle, int sockfd, fd_oper_t action_func)
{
    data_t *data = NULL;

    data = InitData(sockfd, action_func);
    AVLInsert(reactor_handle->dict, data);
    FD_SET(sockfd, &reactor_handle->master);
    reactor_handle->max_fd = MAX(sockfd, reactor_handle->max_fd);
}

static data_t *InitData(int sockfd, fd_oper_t action_func)
{
    data_t *data = (data_t *)malloc(sizeof(data_t));
    if(NULL == data)
    {
        return NULL;
    }
    data->sockfd = sockfd;
    data->action = action_func;

    return (data);
}

static void ReactorRemoveHandler(select_reactor_t *reactor_handle, data_t *data)
{
    close(data->sockfd);
    FD_CLR(data->sockfd, &reactor_handle->master);

    free(data);
    data = NULL;
}

static void ReactorInit(select_reactor_t *reactor_handle)
{
    reactor_handle->dict = AVLCreate(Compare, NULL);
	if (reactor_handle->dict == NULL)
	{
		/* TODO */
	}
    FD_ZERO(&reactor_handle->master);
    reactor_handle->max_fd = 0;
}

static void StdInHandler(data_t *data, select_reactor_t *reactor_handle)
{
    char buff[BUFF_SIZE];
    int n = 0;

    (void) reactor_handle; /* not used */

    n = read(data->sockfd, buff, BUFF_SIZE);

    if (n == - 1)
    {
        ErrorHandler(data, reactor_handle, "fail\n");
    }

    buff[n] = '\0';
    printf("stdin: %s", buff);
}

static void TCPAcceptHandler(data_t *data, select_reactor_t *reactor_handle)
{
    int len = sizeof(their_addr);
    int sockfd_tcp_accept = accept(data->sockfd, (struct sockaddr *)&their_addr, (socklen_t *)&len); /* blocking */
    if(sockfd_tcp_accept == -1)
    {
        ErrorHandler(data, reactor_handle, "accept failed\n");
    }
    ReactorAddHandler(reactor_handle, sockfd_tcp_accept, TCPHandler);
}

static void TCPHandler(data_t *data, select_reactor_t *reactor_handle)
{
    int n = 0; 
    char buffer[MAX_LINE]; 
    const char *pong = "pong";

    n = recv(data->sockfd, (char *)buffer, MAX_LINE,  0); 
    if (n == -1)
    {
        ErrorHandler(data, reactor_handle, "recv failed\n"); 
    } 
    else if (n != 0)
    {
        buffer[n] = '\0'; 
        printf("%s\n", buffer); 
        sleep(1);
        n = send(data->sockfd, pong, strlen(pong), 0);

        if (n == -1)
        {
            ErrorHandler(data, reactor_handle, "sendto failed\n");
        }
    }
    else /* n == 0*/
    {
        ReactorRemoveHandler(reactor_handle, data);
    }
}


static void UDPHandler(data_t *data, select_reactor_t *reactor_handle)
{
    int n = 0; 
    char buffer[MAX_LINE]; 
    const char *pong = "pong";
    socklen_t len = sizeof(their_addr);

    n = recvfrom(data->sockfd, 
					  (char *)buffer, 
					   MAX_LINE,  
					   MSG_WAITALL, 
					   (struct sockaddr *)&their_addr,
					   &len); 

    if (n == -1)
    {
        ErrorHandler(data, reactor_handle, "recvfrom failed\n");
    }

    buffer[n] = '\0'; 
    printf("%s\n", buffer); 

    sleep(1);

    n = sendto(data->sockfd, 
					pong, strlen(pong), 
					MSG_CONFIRM,
				    (const struct sockaddr *)&their_addr, 
					sizeof(struct sockaddr_storage));

    if(n == -1)
    {
        ErrorHandler(data, reactor_handle, "sendto failed\n");
    }
}

static struct timeval InitTimeVal(long seconds, long microseconds)
{
    struct timeval time = {0, 0};
    time.tv_sec = seconds;
    time.tv_usec = microseconds;
    return (time);
}


int Compare(const void *fd1, const void *fd2, void *param)
{
    data_t *data1 = (data_t *)fd1;
    data_t *data2 = (data_t *)fd2;
    (void)param;
    
    return(data1->sockfd - data2->sockfd);

}

static void DestroyAllData(avl_t *dict)
{
    AVLForEach(dict, DestroyData, NULL);
    AVLDestroy(dict);
}

static int DestroyData(void *data, void *param)
{
    (void) param;
    free(data);
    data = NULL;

    return (0);
}

static void ErrorHandler(data_t *data, select_reactor_t *reactor_handle, const char *str)
{
        printf("%s", str);
        close(data->sockfd); 
        DestroyAllData(reactor_handle->dict);
        exit(EXIT_FAILURE); 
}

