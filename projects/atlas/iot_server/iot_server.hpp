#pragma once

#include <cstdio> 
#include <cstdlib> 
#include <unistd.h> 
#include <cstring>
#include <string> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <netdb.h>

namespace ilrd
{
namespace rd90
{
static const char *defaultPort = "29000;";

class IServer
{
    //TODO
public:
    virtual int Accept(){return 0;}
};

class TCPServer : public IServer
{
public:
    explicit TCPServer(std::string port = defaultPort);

    TCPServer(const TCPServer& other) = delete;
    void operator=(const TCPServer& other) = delete;

    int Accept();

private:
    addrinfo         m_hints;
    sockaddr_storage m_clientAddr;
    addrinfo*        m_servinfo;
    socklen_t        m_addr_size;
    int              m_sockFd;
    static int       globalPort;


};

}
}
