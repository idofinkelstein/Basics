/* File Name   : request_dispatcher.cpp
 * Developer   : Janna Torbilo
 * Reviewer    : 
 * Review Date : 2.12.20
 */

#include <sys/socket.h> //socket
#include <netdb.h>      //socket
#include <string.h>     //memset
#include <stdlib.h>     //exit
#include <cstdio>       //printf
#include <unistd.h>     //read_all, write

#include "request_dispatcher.hpp"
#include "bio_access.h"

#define PORT "29000"

namespace ilrd
{
namespace rd90
{

struct AtlasHeader
{
    uint32_t    m_requestUid;   // not to be used by IoT; must be first field
    uint32_t    m_fragmentNum;  // not to be used by IoT
    uint32_t    m_alarmUid;     // not to be used by IoT
    uint32_t    m_iotOffset;
    uint32_t    m_type;
    uint32_t    m_len;          // how many bytes to write OR to read
};

static void InitHints(struct addrinfo* hints, int family, int socktype, int flags);

RequestDispatcher::RequestDispatcher(Reactor<Epoll>& react, int bio_fd) : m_react(react)
{
    m_react.Add(bio_fd, Function<void(int)>(&RequestDispatcher::RequestHandler, this));
}

int RequestDispatcher::RegisterIoT(const std::string& ip_addr)
{
    int socket = 0;

    socket = InitIPSocket(ip_addr);
    m_react.Add(socket, Function<void(int)>(&RequestDispatcher::ReplyHandler, this));
    m_iotFds.push_back(socket);

    return (socket);
}

int RequestDispatcher::RequestHandler(int bio_fd)
{
    int status = 0;
    AtlasHeader atlas = {0, 0, 0, 0 , 0, 0};
    AtlasHeader atlas_receive = {0, 0, 0, 0 , 0, 0};
    BioRequest *request = BioRequestRead(bio_fd);

    /* process request into atlas header */
    atlas.m_type = request->reqType;
    atlas.m_len = request->dataLen;
    atlas.m_iotOffset = request->offset;

    if (request->reqType == NBD_CMD_READ)
    {
        write(m_iotFds[0], reinterpret_cast<char *>(&atlas), sizeof(AtlasHeader));
        read(m_iotFds[0], reinterpret_cast<char *>(&atlas_receive), sizeof(AtlasHeader));
        read(m_iotFds[0], request->dataBuf, request->dataLen);

    }
    else
    {
        write(m_iotFds[0], reinterpret_cast<char *>(&atlas), sizeof(AtlasHeader));
        write(m_iotFds[0], request->dataBuf, request->dataLen);
        read(m_iotFds[0], reinterpret_cast<char *>(&atlas_receive) ,sizeof(AtlasHeader));
    }
    
    BioRequestDone(request, 0);

    return (0);
}

int RequestDispatcher::ReplyHandler(int iot_fd)
{
    (void)iot_fd;

    return (0);
}

int RequestDispatcher::InitIPSocket(const std::string& ip_addr)
{
    struct addrinfo *tcp_server_info;
    struct addrinfo tcp_hints;
    int tcp_sockfd = 0;
    int socket_opt = 1;

    /***** TCP socket handling *****/
    InitHints(&tcp_hints, AF_INET, SOCK_STREAM, AI_PASSIVE);

    if (0 != getaddrinfo(ip_addr.data(), PORT, &tcp_hints, &tcp_server_info))
    {
        printf("tcp getaddrinfo failed"); 
    }

    /* creates socket file descriptor */
    if ((tcp_sockfd = socket(tcp_server_info->ai_family, 
            tcp_server_info->ai_socktype, 
            tcp_server_info->ai_protocol)) == -1)
    {
        printf("tcp socket creation failed"); 
    }

    /* make port reusable */
    if (setsockopt(tcp_sockfd, SOL_SOCKET, SO_REUSEADDR, 
                    &socket_opt, sizeof(socket_opt)) == -1)
    {
        printf("tcp setsockopt failed");
    }

    /*  */
    if (connect(tcp_sockfd, tcp_server_info->ai_addr, 
                tcp_server_info->ai_addrlen) == -1) 
    { 
        printf("tcp connect failed"); 
    }

    return (tcp_sockfd);
}

/* inits the hints struct */
static void InitHints(struct addrinfo* hints, int family, int socktype, int flags)
{
    memset(hints, 0, sizeof(*hints));

    hints->ai_family = family;     /* Allow IPv4 */
    hints->ai_socktype = socktype; /* socket stream */
    hints->ai_flags = flags;       /* assign the address of my local host */ 
}

} // namespace rd90
} // namespace ilrd