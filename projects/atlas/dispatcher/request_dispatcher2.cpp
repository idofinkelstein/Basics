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

#include "request_dispatcher2.hpp"
#include "bio_access.h"
#include "req_slicer.hpp"

static const char *PORT = "29000";

namespace ilrd
{
namespace rd90
{

int RequestDispatcher::m_ReqUID = 0;


static void InitHints(struct addrinfo* hints, int family, int socktype, int flags);

RequestDispatcher::RequestDispatcher(Reactor<Epoll>& react, int bio_fd, IDistributor *dist) :
 m_dist(dist),
 m_react(react)
{
    std::cout << "in RequestDispatcher::RequestDispatcher\n";

    m_react.Add(bio_fd, Bind(&RequestDispatcher::RequestHandler, this, bio_fd));
}

void RequestDispatcher::RegisterIoT(const std::string& ip_addr)
{
    std::cout << "in RequestDispatcher::RegisterIoT\n";

    int socket = InitIPSocket(ip_addr);

    m_react.Add(socket, Bind(&RequestDispatcher::ReplyHandler, this, socket));
    m_iotFds.push_back(socket);
}
/*---------------------------------------------------------------------------*/
void RequestDispatcher::RequestHandler(int bio_fd)
{
    std::cout << "in RequestDispatcher::RequestHandler\n";

    std::shared_ptr<ReqSlicer> slicer(new ReqSlicer(bio_fd, m_ReqUID, m_iotFds));
    m_slicers[m_ReqUID++] = slicer;
    m_dist->Distribute(slicer, m_iotFds);
    




#if 0
    BioRequest *requestFromNBD = BioRequestRead(bio_fd);
    AtlasHeader requestToIoT;

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
#endif
}
/*---------------------------------------------------------------------------*/
void RequestDispatcher::ReplyHandler(int iot_fd)
{
    std::cout << "in RequestDispatcher::ReplyHandler\n";

    uint32_t ID = ReqSlicer::GetRequestID(iot_fd);

    std::shared_ptr<ReqSlicer> slicer = m_slicers[ID];

    if (slicer->HandleReply(iot_fd))
    {
        m_slicers.erase(ID);
        BioRequestDone(slicer->GetBioRequest(), 0);
        std::cout << "in RequestDispatcher::ReplyHandler - after BioRequestDone\n";
    }




	
}
/*---------------------------------------------------------------------------*/
int RequestDispatcher::InitIPSocket(const std::string& ip_addr)
{
    struct addrinfo *tcp_server_info;
    struct addrinfo tcp_hints;
    int tcp_sockfd = 0;
    static int portNum = atoi(PORT);
    char curr_port[6];
    
    sprintf(curr_port, "%d", portNum++);


    /***** TCP socket handling *****/
    InitHints(&tcp_hints, AF_INET, SOCK_STREAM, AI_PASSIVE);

    if (0 != getaddrinfo(ip_addr.data(), curr_port, &tcp_hints, &tcp_server_info))
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

std::vector<int> &RequestDispatcher::GetFDs()
{
    return m_iotFds;
}


} // namespace rd90
} // namespace ilrd
