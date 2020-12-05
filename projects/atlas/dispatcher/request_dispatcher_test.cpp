/************************************************/
// File Name   : request_dispatcher_test.cpp
// Developer   : Ido Finkelstein
// Reviewer    : 
// Review Date : 
/************************************************/

#include <cstdio> 		/* perror, printf */
#include <cstdlib> 		

#include "request_dispatcher.hpp"
#include "bio_access.h"
#include "reactor.hpp"
#include "monitor.hpp"

static const int NUM_OF_CONNECTIONS = 5;
static const std::string SELF_IP("127.0.0.1");

using namespace ilrd::rd90;

int main()
{
    const int storage_size = 1024 * 1024 * 256;
    static const char *dev_name = "/dev/nbd2";
    int bio_fd = BioDevOpen(dev_name, storage_size);

    Reactor<Epoll> reactor(new Epoll(NUM_OF_CONNECTIONS));
    RequestDispatcher disp(reactor, bio_fd);

    disp.RegisterIoT(SELF_IP);

    reactor.Run();

    return 0;
}
