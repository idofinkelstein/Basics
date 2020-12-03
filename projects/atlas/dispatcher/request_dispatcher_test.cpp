/* File Name   : request_dispatcher_test.cpp
 * Developer   : Janna Torbilo
 * Reviewer    : 
 * Review Date : 2.12.20
 */

#include "request_dispatcher.hpp"
#include "bio_access.h"
#include "reactor.hpp"

using namespace ilrd::rd90;

int main()
{
    const int storage_size = 1024 * 1024 * 256;
    static const char *dev_name = "/dev/nbd2";
    int bio_fd = BioDevOpen(dev_name, storage_size);

    Reactor<Epoll> reactor(new Epoll(5));
    RequestDispatcher disp(reactor, bio_fd);

    disp.RegisterIoT("127.0.0.1");

    reactor.Run();

    return (0);
}