#pragma once

#include "reactor.hpp"

namespace ilrd
{
namespace rd90
{


class TCPServer
{
public:
    explicit TCPServer(Reactor<Epoll> *reactor, const char *port);
    void Start();
private:
    Reactor<Epoll> *m_reactor;
    int m_tcpFd;

    void AcceptHandler(int);
    void ReadHadler(int);
};

} // rd90 
} // ilrd