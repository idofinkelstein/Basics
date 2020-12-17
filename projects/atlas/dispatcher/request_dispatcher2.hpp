/*
int main(void)
{
    // open connection to nbd 
    int bio_fd = BioDevOpen();

    // create reactor 
    Reactor<Epoll> react(new Epoll(3));

    // create ReqDisp 
    RequestDispatcher disp(react);
    
    // Register IoTs
    disp.RegisterIoT("4.5.5.2");
    disp.RegisterIoT("4.5.5.3");
    disp.RegisterIoT("4.5.5.4");

    // register handlers ? 

    // run
    react.Run();
    // disp.Start(); ? 
}
*/

#pragma once

#include <vector>           // vector
#include <string>           // string

#include "reactor.hpp"      // reactor
#include "function.hpp"     // function
#include "monitor.hpp"     // epoll
#include "distributor.hpp"      // distributer class


/*---------------------------------------------------------------------------*/

namespace ilrd
{
namespace rd90
{

/*********************   Free Functions declarations    **********************/

/************************   Classes declarations    **************************/

class RequestDispatcher
{
public:
    // if also registers handler of bio_fd, needs to pass as a paremeter
    explicit RequestDispatcher(Reactor<Epoll> &react, int bio_fd); 

    void RegisterIoT(const std::string& ip_addr); 
                                                  
    // void RegisterHandler(int bio_fd);   

    RequestDispatcher(const RequestDispatcher&) = delete;
    RequestDispatcher& operator=(const RequestDispatcher&) = delete;
    ~RequestDispatcher() = default;

private:
    void RequestHandler(int bio_fd);
    void ReplyHandler(int iot_fd);
    int InitIPSocket(const std::string& ip_addr);

    IDistributor *dist;
    std::vector<int>m_iotFds;
    Reactor<Epoll>& m_react;
};


/*---------------------------------------------------------------------------*/

} // namespace rd90
} // namespace ilrd
