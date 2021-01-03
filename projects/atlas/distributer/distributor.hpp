
#pragma once

#include <iostream>     // ostream
#include <memory>       // std::shared_ptr

#include "req_slicer.hpp"   // class ReqSlicer
/*---------------------------------------------------------------------------*/

namespace ilrd
{
namespace rd90
{

struct Task;

/************************   Classes declarations    **************************/

class IDistributor
{
public:  
    explicit IDistributor() = default;
    virtual ~IDistributor() = default;
    IDistributor(const IDistributor&) = delete;
    IDistributor& operator=(const IDistributor&) = delete;

    virtual void Distribute(const std::shared_ptr<ReqSlicer>& slicer, std::vector<int>& m_fds) = 0;

private:
};

/*---------------------------------------------------------------------------*/

class DistModulu : public IDistributor
{
public:
    explicit DistModulu(); // or int numIoTs?
    
    virtual ~DistModulu() = default;
    virtual void Distribute(const std::shared_ptr<ReqSlicer>& slicer, std::vector<int>& m_fds); 

private:
    int m_numOfIoTs;
};



/*---------------------------------------------------------------------------*/

} // namespace rd90
} // namespace ilrd





