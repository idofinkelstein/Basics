#include <iostream>

#include "distributor.hpp"

namespace ilrd
{
namespace rd90
{

const int BLOCK_SIZE = 1024;

DistModulu::DistModulu(int numOfThreads) : m_threadPool(numOfThreads) {}
/*---------------------------------------------------------------------------*/
void DistModulu::Distribute(const std::shared_ptr<ReqSlicer> &slicer, 
                            std::vector<int>& m_fds)
{
    int numOfSlices = slicer->GetDataLen() / SLICE_SIZE;
    int globalOffset = slicer->GetOffset();
    int nIoTs = m_fds.size();
    int readySlices = 0;
    int firstIot = (globalOffset / SLICE_SIZE) % nIoTs;

    for (int i = 0; i < nIoTs && readySlices < numOfSlices; ++i)
    {
        std::shared_ptr<Task> task(new Task);

        task->m_iot = (firstIot + i) % nIoTs;

        for (int j = i; j < numOfSlices; j += nIoTs)
        {
            task->m_iotIndices.push_back(j);
            ++readySlices;
        }
        std::vector<int> v;
        ReqSlicer sf(5,5,v);
        Task t;
        Bind(&ReqSlicer::HandleRequest, &sf,  task);
        //auto f = Bind(&ReqSlicer::HandleRequest, slicer.get(), /* std::cref(task) */ task);
        //m_threadPool.Async(Bind(&ReqSlicer::HandleRequest, &(*slicer), task), ThreadPool::MID);

        //slicer->HandleRequest(task);
    }
}


} // namespace rd90
} // namespace ilrd
