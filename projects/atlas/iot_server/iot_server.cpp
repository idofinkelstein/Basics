#include "iot_server.hpp"

namespace ilrd
{
namespace rd90
{

Server::Server()
{
    memset(&m_hints, 0, sizeof(m_hints));
    m_hints.ai_family = AF_INET;
    m_hints.ai_socktype = SOCK_STREAM;
    m_hints.ai_flags = AI_PASSIVE;
}

void Server::EstablishConnection(std::string port)
{
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

void Server::Run()
{

}


}
}