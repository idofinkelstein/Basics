#include <iostream>
#include <unistd.h>
#include <sys/types.h>  // sendmsg
#include <sys/socket.h> // sendmsg
#include <cstring>      // memset

#include "distributor.hpp"
#include "req_slicer.hpp"

namespace ilrd
{
namespace rd90
{

static Factory<ICommand, int, CommandData*> fact = ReqSlicer::InitFactory();

ReqSlicer::ReqSlicer(int bio_fd, uint32_t reqID, std::vector<int> &fds)
:  m_fds(fds), m_reqID(reqID), m_bio_fd(bio_fd)
{
    m_bioReq = BioRequestRead(bio_fd);
    if (NULL == m_bioReq)
    {
        std::cout << "cant read request" << std::endl;
        throw("BioRequestRead");
    }

    size_t numOfSlices = m_bioReq->dataLen / SLICE_SIZE;
    
    for(size_t i = 0; i < numOfSlices; ++i)
    {
        m_indices.insert(i);
    }

}
/*---------------------------------------------------------------------------*/
ReqSlicer::~ReqSlicer()
{
    BioRequestDone(m_bioReq, 0);
}
/*---------------------------------------------------------------------------*/
uint32_t ReqSlicer::GetRequestID(int iot_fd)
{
    uint32_t id;

    if (0 > read(iot_fd, &id, sizeof(uint32_t)))
    {
         throw("read\n");
    } 

    return id;
}
/*---------------------------------------------------------------------------*/
/* void ReqSlicer::HandleRequest(std::shared_ptr<Task> &task)
{
    while (!task->m_iotIndices.empty())
    {
        int idx = task->m_iotIndices.back();

        WriteFragment(task->m_iot, idx);

        task->m_iotIndices.pop_back();
    }
} */
/*---------------------------------------------------------------------------*/
int ReqSlicer::HandleRequest(Task task)
{
    while (!task.m_iotIndices.empty())
    {
        int idx = task.m_iotIndices.back();

        WriteFragment(task.m_iot, idx);

        task.m_iotIndices.pop_back();
    }    

    return 0;
}

/*---------------------------------------------------------------------------*/
void ReqSlicer::WriteFragment(int iot, int idx)
{
    int iotFd = m_fds[iot];
    AtlasHeader atlas_header;   
    msghdr message;

    memset(&message, 0, sizeof(message));

    atlas_header.m_requestUid = m_reqID;
    atlas_header.m_fragmentNum = idx;
    atlas_header.m_alarmUid = 0;
    atlas_header.m_type = m_bioReq->reqType;
    atlas_header.m_len = SLICE_SIZE;
    atlas_header.m_iotOffset = (m_bioReq->offset + idx * SLICE_SIZE) / m_fds.size();
    
    CommandData data(atlas_header, m_bioReq, iotFd, idx);
 
    std::shared_ptr<ICommand> command(fact.Create(m_bioReq->reqType, &data));

    command->ExecuteRequest();

}
/*---------------------------------------------------------------------------*/

bool ReqSlicer::HandleReply(int iot_fd)
{
    AtlasHeader ReplayFromIoT;

	read(iot_fd, reinterpret_cast<char*>(&ReplayFromIoT) + sizeof(uint32_t), sizeof(AtlasHeader) - sizeof(uint32_t));

    std::cout << "m_bioReq->dataLen = " << m_bioReq->dataLen << std::endl;
    std::cout << "m_bioReq->offset = " << m_bioReq->offset << std::endl;

    std::cout << "ReplayFromIoT.m_iotOffset = " << ReplayFromIoT.m_iotOffset << std::endl;


    CommandData data(ReplayFromIoT, m_bioReq, iot_fd, 0);

    std::shared_ptr<ICommand> command(fact.Create(m_bioReq->reqType, &data));

    command->ExecuteReplay();

    m_indices.erase(ReplayFromIoT.m_fragmentNum);

    if (m_indices.size() == 0)
    {
        return true;
    }

    return false;
}
/*---------------------------------------------------------------------------*/
uint64_t ReqSlicer::GetOffset()
{
    return m_bioReq->offset;
}
/*---------------------------------------------------------------------------*/
uint32_t ReqSlicer::GetDataLen()
{
    return m_bioReq->dataLen;
}
/*---------------------------------------------------------------------------*/
uint32_t ReqSlicer::GetReqType()
{
    return m_bioReq->reqType;
}
/*---------------------------------------------------------------------------*/
Factory<ICommand, int, CommandData*> ReqSlicer::InitFactory()
{
    Factory<ICommand, int, CommandData*> fact;

    fact.Register<Read>(NBD_CMD_READ);
    fact.Register<Write>(NBD_CMD_WRITE);

    return fact;
}


} // namespace rd90
} // namespace ilrd
