/* 


*/

#pragma once

#include <iostream>     // ostream
#include <memory>       // std::shared_ptr

#include "req_slicer.hpp"   // class ReqSlicer
/*---------------------------------------------------------------------------*/

namespace ilrd
{
namespace rd90
{

/*********************   Free Functions declarations    **********************/

class Task;

/************************   Classes declarations    **************************/

class IDistributor
{
public:  
    explicit IDistributor() = default;
    virtual ~IDistributor() = default;
    IDistributor(const IDistributor&) = delete;
    IDistributor& operator=(const IDistributor&) = delete;

    virtual void Distribute(const std::shared_ptr<ReqSlicer>& slicer) = 0;

private:
};

/*---------------------------------------------------------------------------*/

class DistModulu : public IDistributor
{
public:
    explicit DistModulu(std::shared_ptr< std::vector<int> > fds); // or int numIoTs?
    
    virtual ~DistModulu() = default;
    virtual void Distribute(const std::shared_ptr<ReqSlicer>& slicer); 

private:
    std::shared_ptr< std::vector<int> > m_fds; // or int numIoTs?
};

/*************************   Class Implementation    *************************/


/***************************   Public functions    ***************************/


/*---------------------------------------------------------------------------*/

} // namespace rd90
} // namespace ilrd






