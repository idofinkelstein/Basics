/************************************************/
// File Name   : request_dispatcher.cpp
// Developer   : Ido Finkelstein
// Reviewer    : 
// Review Date : 
/************************************************/

#include <sys/socket.h> //socket
#include <netdb.h>      //socket
#include <cstring>     //memset
#include <cstdlib>     //exit
#include <cstdio>       //printf
#include <unistd.h>     //read_all, write

#include "request_dispatcher.hpp"
#include "bio_access.h"

static const char *PORT = "29000";

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
    m_react.Add(bio_fd, Bind(&RequestDispatcher::RequestHandler, this));
}

void RequestDispatcher::RegisterIoT(const std::string& ip_addr)
{
    int socket = InitIPSocket(ip_addr);

    m_react.Add(socket, Bind(&RequestDispatcher::ReplyHandler, this));
    m_iotFds.push_back(socket);
}

void RequestDispatcher::RequestHandler(int bio_fd)
{
    AtlasHeader requestToIoT;
    BioRequest *requestFromNBD = BioRequestRead(bio_fd);

    /* processes request into atlas header */
    requestToIoT.m_type = requestFromNBD->reqType;
    requestToIoT.m_len = requestFromNBD->dataLen;
    requestToIoT.m_iotOffset = requestFromNBD->offset;
	*reinterpret_cast<BioRequest**>(&requestToIoT) = requestFromNBD;

	if (-1 == write(m_iotFds[0], reinterpret_cast<char *>(&requestToIoT), sizeof(AtlasHeader)))
	{
		puts("RequestHandler: write header");
		throw("write to IoT failed");
	}

	if (requestFromNBD->reqType == NBD_CMD_WRITE)
	{
		if (-1 == (write(m_iotFds[0], requestFromNBD->dataBuf, requestFromNBD->dataLen)))
		{
			puts("RequestHandler: write data");
			throw("write to IoT failed");
		}
	}
}

void RequestDispatcher::ReplyHandler(int iot_fd)
{
	AtlasHeader ReplayFromIoT;
	BioRequest *ReplayToNBD = NULL;

	read(iot_fd, reinterpret_cast<char *>(&ReplayFromIoT), sizeof(AtlasHeader));
	ReplayToNBD = *reinterpret_cast<BioRequest**>(&ReplayFromIoT);

	//processes reply
    ReplayToNBD->dataLen = ReplayFromIoT.m_len;
    ReplayToNBD->offset = ReplayFromIoT.m_iotOffset;
    ReplayToNBD->reqType = ReplayFromIoT.m_type;

	if (ReplayToNBD->reqType == NBD_CMD_READ)
    {
        ReadAll(iot_fd, ReplayToNBD->dataBuf, ReplayToNBD->dataLen);
    }
   
	BioRequestDone(ReplayToNBD, 0);
}

int RequestDispatcher::InitIPSocket(const std::string& ip_addr)
{
    struct addrinfo *tcp_server_info;
    struct addrinfo tcp_hints;
    int tcp_sockfd = 0;

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
    hints->ai_socktype = socktype; /* TCP stream */
    hints->ai_flags = flags;       /* assign the address of my local host */ 
}

} // namespace rd90
} // namespace ilrd
