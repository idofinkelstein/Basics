#include <cstring>
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
    int status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((status = getaddrinfo("127.0.0.1" , port, &hints, &servinfo)) != 0)
    {
        throw("getaddrinfo");
    }

    /* Creating socket file descriptor */
    if (-1 == (m_tcpFd = socket(servinfo->ai_family, servinfo->ai_socktype, 0))) /* TCP protocol */
    { 
        throw("socket");
    }

    if (-1 == bind(m_tcpFd, servinfo->ai_addr, servinfo->ai_addrlen))
    {
        throw("bind");
    }

    if (-1 == listen(m_tcpFd, 5))
    {
        throw("listen");
    }
}

void TCPServer::AcceptHandler(int tcpFd)
{
    int new_fd;
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(struct sockaddr_storage);
    (void)tcpFd;

    if (-1 == (new_fd = accept(m_tcpFd, 
                               reinterpret_cast<struct sockaddr *>(&their_addr),
                               &addr_size)))
    {
        throw("accept");
    }
    m_reactor->Add(new_fd,Bind(&TCPServer::ReadHadler, this));
    
}

void TCPServer::ReadHadler(int readFd)
{
    char pong[] = "pong";
    char len = 5;  
    char *buff;
    long buff_size, bytes_read;
    /* get size in buffer to allocate */
    if (-1 == ioctl(readFd, FIONREAD, &buff_size))
    {
        throw("ioctl");
    }

    buff = new char[buff_size];
    
    bytes_read = recv(readFd, buff, buff_size, 0);
    
    if(-1 == bytes_read)
    {
        throw("recv");
    }
    else if (bytes_read > 0)
    {
        write(1, buff, buff_size);
        
        bytes_read = send(readFd, pong, len, 0);
        if (-1 == bytes_read)
        {
            throw("send");
        }
    }

    sleep(1);
}

void TCPServer::Start()
{
    m_reactor->Add(m_tcpFd, Bind(&TCPServer::AcceptHandler, this));
}


} // rd90 
} // ilrd
