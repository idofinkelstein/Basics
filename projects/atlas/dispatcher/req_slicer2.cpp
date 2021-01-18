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
    
    /* std::cout << "iotFd = " << iotFd << std::endl;
    std::cout << "atlas_header.m_requestUid = " << atlas_header.m_requestUid << std::endl;
    std::cout << "atlas_header.m_fragmentNum = " << atlas_header.m_fragmentNum << std::endl;
    std::cout << "atlas_header->m_iotOffset = " << atlas_header.m_iotOffset << std::endl; */

    // Assigns 2 buffers if it's WRITE request or 1 for READ.
    message.msg_iovlen = ((atlas_header.m_type == NBD_CMD_WRITE) ? 2 : 1);

    message.msg_iov = new struct iovec[message.msg_iovlen];

    message.msg_iov[0].iov_base = &atlas_header;
    message.msg_iov[0].iov_len = sizeof(atlas_header);

    if (atlas_header.m_type == NBD_CMD_WRITE)
    {
        message.msg_iov[1].iov_base = m_bioReq->dataBuf + idx * SLICE_SIZE;
        message.msg_iov[1].iov_len = SLICE_SIZE;
    }
   
    if (-1 == (sendmsg(iotFd, &message, 0)))
    {
        throw("sendmsg() failed");
    }

    delete[] message.msg_iov;
}
/*---------------------------------------------------------------------------*/

bool ReqSlicer::HandleReply(int iot_fd)
{
    AtlasHeader ReplayFromIoT;

	read(iot_fd, reinterpret_cast<char*>(&ReplayFromIoT) + sizeof(uint32_t), sizeof(AtlasHeader) - sizeof(uint32_t));

    std::cout << "m_bioReq->dataLen = " << m_bioReq->dataLen << std::endl;
    std::cout << "m_bioReq->offset = " << m_bioReq->offset << std::endl;

    std::cout << "ReplayFromIoT.m_iotOffset = " << ReplayFromIoT.m_iotOffset << std::endl;

	if (m_bioReq->reqType == NBD_CMD_READ)
    {
        ReadAll(iot_fd, m_bioReq->dataBuf + ReplayFromIoT.m_fragmentNum * SLICE_SIZE, ReplayFromIoT.m_len);
    }

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
uint32_t ilrd::rd90::ReqSlicer::GetDataLen()
{
    return m_bioReq->dataLen;
}
/*---------------------------------------------------------------------------*/
uint32_t ilrd::rd90::ReqSlicer::GetReqType()
{
    return m_bioReq->reqType;
}
/*---------------------------------------------------------------------------*/

} // namespace rd90
} // namespace ilrd
