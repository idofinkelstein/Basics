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
        //TODO: use shared pointer
        //std::shared_ptr<Task> task(new Task);
        Task task;

        //task->m_iot = (firstIot + i) % nIoTs;
        task.m_iot  = (firstIot + i) % nIoTs;

        for (int j = i; j < numOfSlices; j += nIoTs)
        {
            //task->m_iotIndices.push_back(j);
            task.m_iotIndices.push_back(j);
            ++readySlices;
        }
        
        m_threadPool.Async(Bind(&ReqSlicer::HandleRequest, slicer.get(), task), ThreadPool::Priority::MID);
    }
}


} // namespace rd90
} // namespace ilrd
