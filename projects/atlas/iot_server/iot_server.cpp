#include <linux/nbd.h>
#include <iostream>

#include "iot_server.hpp"
#include "atlas.hpp"


namespace ilrd
{
namespace rd90
{

int TCPServer::globalPort = atoi(defaultPort);
/*----------------------------------------------------------------------------*/
TCPServer::TCPServer(std::string port)
{
    memset(&m_hints, 0, sizeof(m_hints));
    m_hints.ai_family = AF_INET;
    m_hints.ai_socktype = SOCK_STREAM;
    m_hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo("127.0.0.1", port.data(), &m_hints, &m_servinfo) != 0)
    {
        throw("getaddrinfo()");
    }

    /* Creating socket file descriptor */
    if (-1 == (m_sockFd = socket(m_servinfo->ai_family, m_servinfo->ai_socktype, 0))) /* TCP protocol */
    { 
        throw("sockrt()");
    }

    if (-1 == bind(m_sockFd, m_servinfo->ai_addr, m_servinfo->ai_addrlen))
    {
        throw("bind()");
    }

    if (-1 == listen(m_sockFd, 5))
    {
        throw("listen()");
    }
}
/*----------------------------------------------------------------------------*/
int TCPServer::Accept()
{
    int fd;
    m_addr_size = sizeof(sockaddr_storage);// initial size of address before returning from accept();

    if (-1 == (fd = accept(m_sockFd, reinterpret_cast<sockaddr*>(&m_clientAddr), &m_addr_size)))
    {
        puts("recv");
        throw("accept()");
    }

    return fd;
}

}
}