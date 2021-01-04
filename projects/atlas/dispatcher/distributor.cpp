#include <iostream>
#include "distributor.hpp"

namespace ilrd
{
namespace rd90
{

const int BLOCK_SIZE = 1024;

DistModulu::DistModulu()
{    std::cout << "in DistModulu::DistModulu\n";
}

void DistModulu::Distribute(const std::shared_ptr<ReqSlicer> &slicer, std::vector<int>& m_fds)
{
    std::cout << "in DistModulu::Distribute\n";

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

    Task *tArr = new Task[nTasks];

    for (int i = 0; i < idxCount; ++i)
    {
        tArr[(firstIoT + i) % nIoTs].m_iot_indices.push_back(i);
    }
    
    for (int i = 0; i < nTasks; ++i)
    {
        tArr[i].m_iotFd = m_fds.operator[](i);
        slicer->HandleRequest(tArr[i]);
    }

    std::cout << "num of tasks = " << nTasks << std::endl;
    std::cout << "num of iots = " << nIoTs << std::endl;
    std::cout << "firstIoT = " << firstIoT << std::endl;
    std::cout << "idxCount = " << idxCount << std::endl;
    //std::cout << "num of tasks = " << nTasks << std::endl;

    delete[] tArr;
}


} // namespace rd90
} // namespace ilrd
