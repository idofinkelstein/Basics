
#pragma once

#include <iostream>     // ostream
#include <memory>       // std::shared_ptr

#include "req_slicer.hpp"   // class ReqSlicer
#include "threadpool.hpp"
#include "function.hpp"

/*---------------------------------------------------------------------------*/

namespace ilrd
{
namespace rd90
{

class IDistributor
{
public:  
    explicit IDistributor() = default;
    virtual ~IDistributor() = default;
    IDistributor(const IDistributor&) = delete;
    IDistributor& operator=(const IDistributor&) = delete;

    /* Interface */
    virtual void Distribute(const std::shared_ptr<ReqSlicer>& slicer, std::vector<int>& m_fds) = 0;
};

/*---------------------------------------------------------------------------*/

class DistModulu : public IDistributor
{
public:
    explicit DistModulu(int numOfThreads);
    virtual ~DistModulu() = default;
    virtual void Distribute(const std::shared_ptr<ReqSlicer>& slicer, std::vector<int>& m_fds);

private:
    ThreadPool  m_threadPool;
};


} // namespace rd90
} // namespace ilrd






