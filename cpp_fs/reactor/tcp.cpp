#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <netdb.h>

#include "tcp.hpp"



namespace ilrd
{
namespace rd90
{

TCPServer::TCPServer(Reactor<Select> *reactor, const char *port)
: m_reactor(reactor)
{
    struct addrinfo hints;
    struct addrinfo *servinfo;
    
    socklen_t addr_size;
    int status;

    if ((status = getaddrinfo("127.0.0.1", port, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    /* Creating socket file descriptor */
    if (-1 == (m_tcpFd = socket(servinfo->ai_family, servinfo->ai_socktype, 0))) /* TCP protocol */
    { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    }

    if (-1 == bind(m_tcpFd, servinfo->ai_addr, servinfo->ai_addrlen))
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (-1 == listen(m_tcpFd, 5))
    {
        perror("listen"); 
        exit(EXIT_FAILURE);
    }
}

void TCPServer::AcceptHandler(int tcpFd)
{
    int new_fd;
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(struct sockaddr_storage);

    if (-1 == (new_fd = accept(m_tcpFd, (struct sockaddr *)&their_addr, &addr_size)))
    {
        perror("accept"); 
        exit(EXIT_FAILURE);
    }
    m_reactor->Add(new_fd,Bind(ReadHadler, this));
    
}

void TCPServer::ReadHadler(int readFd)
{
    char *pong = "pong";
    char len = 5;  
    char *buff;
    size_t buff_size, bytes_read;
    /* get size in buffer to allocate */
    if (-1 == ioctl(readFd, FIONREAD, &buff_size))
    {
        perror("tcp ioctl");
        return;
    }

    buff = new char[buff_size];

    bytes_read = recv(readFd, buff, buff_size, 0);
    if(-1 == bytes_read)
    {
        perror("recv");
        delete[] buff;
        close(m_tcpFd);
        close(readFd);
        exit(EXIT_FAILURE);
    }
    else if (bytes_read > 0)
    {
        write(1, buff, buff_size);
        

        bytes_read = send(readFd, pong, len, 0);
        if (-1 == bytes_read)
        {
            perror("tcp send");
            delete[] buff;
            close(m_tcpFd);
            close(readFd);
            exit(EXIT_FAILURE);
        }
    }

    sleep(1);
}

void TCPServer::Start()
{
    m_reactor->Add(m_tcpFd, Bind(AcceptHandler, this));
}


} // rd90 
} // ilrd
