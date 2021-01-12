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

const char *defaultPort = "29000;";

namespace ilrd
{
namespace rd90
{

class Server
{
public:
    explicit Server();

    Server(const Server& other) = delete;
    void operator=(const Server& other) = delete;

    void EstablishConnection(std::string port = defaultPort);
    void Run();

private:
    int m_sockFd;
    int m_communicationFd;
    static int globalPort;


};

}
}
