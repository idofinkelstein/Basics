#include <iostream>
#include <unistd.h>

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

ReqSlicer::~ReqSlicer()
{
    BioRequestDone(m_bioReq, 0);
}

uint32_t ReqSlicer::GetRequestID(int iot_fd)
{
    uint32_t id;

    if (0 > read(iot_fd, &id, sizeof(uint32_t)))
    {
         throw("read\n");
    } 

    return id;
}

void ReqSlicer::HandleRequest(std::shared_ptr<Task> &task)
{
    while (!task->m_iotIndices.empty())
    {
        int idx = task->m_iotIndices.back();

        WriteFragment(task->m_iot, idx);

        task->m_iotIndices.pop_back();
    }
}

void ReqSlicer::WriteFragment(int iot, int idx)
{
    int iotFd = m_fds[iot];

    AtlasHeader atlas_header;    

    atlas_header.m_requestUid = m_reqID;
    atlas_header.m_fragmentNum = idx;
    atlas_header.m_alarmUid = 0;
    atlas_header.m_type = m_bioReq->reqType;
    atlas_header.m_len = SLICE_SIZE;

    atlas_header.m_iotOffset = (m_bioReq->offset + idx * SLICE_SIZE) / m_fds.size();
    
    std::cout << "iotFd = " << iotFd << std::endl;
    std::cout << "atlas_header.m_requestUid = " << atlas_header.m_requestUid << std::endl;
    std::cout << "atlas_header.m_fragmentNum = " << atlas_header.m_fragmentNum << std::endl;
    std::cout << "atlas_header->m_iotOffset = " << atlas_header.m_iotOffset << std::endl;


    if(-1 == write(iotFd, &atlas_header, sizeof(AtlasHeader)))
    {
        throw("write failed");
    }

    // If write request - send data
    if(atlas_header.m_type == NBD_CMD_WRITE)
    {
        if(-1 == write(iotFd, m_bioReq->dataBuf + idx * SLICE_SIZE, SLICE_SIZE))
        {
            throw("write failed");
        }
    }
}


bool ReqSlicer::HandleReply(int iot_fd)
{
#if 1
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
#else

    AtlasHeader IOT_return_message;

    IOT_return_message.m_requestUid = m_reqID;
    std::cout << "first\n";
    
    if (ReadAll(iot_fd, reinterpret_cast<char*>(&IOT_return_message) + sizeof(int), 
                                                       sizeof(AtlasHeader) - sizeof(int)) < 0)
    {
        throw("failed read \n");
    }
    std::cout << "second\n";

    if (NBD_CMD_READ == IOT_return_message.m_type)
    {
        if (ReadAll(iot_fd, m_bioReq->dataBuf + (IOT_return_message.m_fragmentNum *  SLICE_SIZE), IOT_return_message.m_len) < 0)
        {
            throw("failed read \n");
        }  
    }
    std::cout << "third\n";

    m_indices.erase(IOT_return_message.m_fragmentNum);
#endif

    if (m_indices.size() == 0)
    {
        return true;
    }

    return false;
}

uint64_t ReqSlicer::GetOffset()
{
    return m_bioReq->offset;
}

uint32_t ilrd::rd90::ReqSlicer::GetDataLen()
{
    return m_bioReq->dataLen;
}

uint32_t ilrd::rd90::ReqSlicer::GetReqType()
{
    return m_bioReq->reqType;
}

BioRequest *ReqSlicer::GetBioRequest()
{
    return m_bioReq;
}

} // namespace rd90
} // namespace ilrd
