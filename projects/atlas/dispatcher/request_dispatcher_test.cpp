/************************************************/
// File Name   : request_dispatcher_test.cpp
// Developer   : Ido Finkelstein
// Reviewer    : 
// Review Date : 
/************************************************/

#include <cstdio> 		/* perror, printf */
#include <cstdlib> 		

#include "request_dispatcher2.hpp"
#include "bio_access.h"
#include "reactor.hpp"
#include "monitor.hpp"

static const int NUM_OF_CONNECTIONS = 10;
static const std::string SELF_IP("127.0.0.1");

using namespace ilrd::rd90;

int main()
{
    const int storageSize = 1024 * 1024 * 256;
    static const char *deviceName = "/dev/nbd0";
    int bioFd = BioDevOpen(deviceName, storageSize);

    DistModulu dist(4);
    Reactor<Epoll> reactor(new Epoll(NUM_OF_CONNECTIONS));
    RequestDispatcher disp(reactor, bioFd, &dist);

    disp.RegisterIoT(SELF_IP);
    //disp.RegisterIoT(SELF_IP);
    //disp.RegisterIoT(SELF_IP);
    //disp.RegisterIoT(SELF_IP);

    reactor.Run();

    return 0;
}
