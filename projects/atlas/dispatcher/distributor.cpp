#include <iostream>

#include "distributor.hpp"

namespace ilrd
{
namespace rd90
{

const int BLOCK_SIZE = 1024;


void DistModulu::Distribute(const std::shared_ptr<ReqSlicer> &slicer, std::vector<int>& m_fds)
{
#if 0

    uint64_t offset = slicer->GetOffset();
    int nIoTs = m_fds.size();
    int firstIoT = (offset / BLOCK_SIZE) % nIoTs;
    int idxCount = slicer->GetDataLen() / BLOCK_SIZE;
    int nTasks = 0;

    

    if (idxCount >= nIoTs)
    {
        nTasks = m_fds.size();
    }
    else
    {
        nTasks = idxCount;
    }

    Task *tArr = new Task[nTasks + firstIoT];

     //for (int i = 0; i < nTasks; ++i)
     //   tArr[i].m_iot_indices.reserve(nTasks);

    for (int i = 0; i < idxCount + firstIoT; ++i)
    {
        //tArr[i].m_iot_indices.push_back((firstIoT + i) % nIoTs);
        
        tArr[(firstIoT + i) % nIoTs].m_iot_indices.push_back(i);
        std::cout << "tArr[" << (firstIoT + i) % nIoTs << "].m_iot_indices[" << i << "] = " << tArr[(firstIoT + i) % nIoTs].m_iot_indices[i] << std::endl;
    }
    
    for (int i = 0; i < nTasks + firstIoT; ++i)
    {
        tArr[i].m_iotFd = m_fds.operator[]((firstIoT + i) % nIoTs);
        std::cout << "tArr["<<i<<"].m_iotFd = " << tArr[i].m_iotFd << std::endl;
        
        slicer->HandleRequest(tArr[i]);
    }

    for (int i = 0; i < nTasks; ++i)
    //    slicer->HandleRequest(tArr[i]);

    std::cout << "num of tasks = " << nTasks << std::endl;
    std::cout << "num of iots = " << nIoTs << std::endl;
    std::cout << "firstIoT = " << firstIoT << std::endl;
    std::cout << "idxCount = " << idxCount << std::endl;
    //std::cout << "num of tasks = " << nTasks << std::endl;

    //delete[] tArr;

#else

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

        slicer->HandleRequest(task);
    }
#endif

}


} // namespace rd90
} // namespace ilrd
