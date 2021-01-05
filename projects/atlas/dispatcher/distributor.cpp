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

#if 1

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
        std::cout << "tArr[i].m_iotFd = " << tArr[i].m_iotFd << std::endl;
        slicer->HandleRequest(tArr[i]);
    }

    std::cout << "num of tasks = " << nTasks << std::endl;
    std::cout << "num of iots = " << nIoTs << std::endl;
    std::cout << "firstIoT = " << firstIoT << std::endl;
    std::cout << "idxCount = " << idxCount << std::endl;
    //std::cout << "num of tasks = " << nTasks << std::endl;

    delete[] tArr;

#else

    int num_of_slices = slicer->GetDataLen() / SLICE_SIZE;
    int i = 0;
    int j = 0;
    int global_offset = slicer->GetOffset();
    int slices_given = 0;
    //int slices_per_curr_iot = num_of_slices / m_num_iot;
    // int slices_per_curr_iot = 1;

    // std::cout << "slices_per_curr_iot \n" << slices_per_curr_iot << "\n";
    std::cout << "num_of_slices \n" << num_of_slices<< "\n";
    std::cout << "m_num_iot \n" << m_fds.size() << "\n";
    int first_iot = (global_offset / SLICE_SIZE) % m_fds.size();

    for (i = 0; i < m_fds.size() && slices_given < num_of_slices; ++i)
    {
        std::shared_ptr<Task> t(new Task);
        // Task t;     // to be changed to Factory
        std::cout << "i: " << i << std::endl;

        t->iot = (first_iot + i) % m_fds.size();
        t->num_of_iot = m_num_iot;
        for (j = i; j < num_of_slices; j += m_num_iot)
        {
            std::cout << "j: " << j << std::endl;
            t->dataBuf_indexes.push_back(j);
            ++slices_given;
        }

        std::cout << "slices_given: " << slices_given << std::endl; 

        slicer->HandleRequest(t,iotFds);

#endif

}


} // namespace rd90
} // namespace ilrd
