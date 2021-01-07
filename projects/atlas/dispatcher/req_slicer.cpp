#include <iostream>
#include "distributor.hpp"
#include "req_slicer.hpp"
//#include "request_dispatcher2.hpp"
#include <unistd.h>

namespace ilrd
{
namespace rd90
{

ReqSlicer::ReqSlicer(int bio_fd, uint32_t reqID, std::vector<int> &fds)
:  m_fds(fds), m_reqID(reqID), m_bio_fd(bio_fd)
{
        std::cout << "in ReqSlicer::ReqSlicer\n";


    m_bioReq = BioRequestRead(bio_fd);
    if (NULL == m_bioReq)
    {
        throw("BioRequestRead");
    }

    std::cout << "m_bioReq->dataLen = " << m_bioReq->dataLen << std::endl;
    for(size_t i = 0; i < m_bioReq->dataLen / SLICE_SIZE; ++i)
    {
        m_indices.insert(i);
        std::cout << i << std::endl;
    }
}

ReqSlicer::~ReqSlicer()
{
    std::cout << "in ReqSlicer::~ReqSlicer\n";
    BioRequestDone(m_bioReq, 0);
}

uint32_t ReqSlicer::GetRequestID(int iot_fd)
{
    std::cout << "in GetRequestID slicer\n";

    uint32_t id;

    if (0 > read(iot_fd, &id, sizeof(uint32_t)))
    {
         throw("read\n");
    } 

    std::cout << "in GetRequestID slicer, ID = " << id << std::endl;

    return id;
}

void ReqSlicer::HandleRequest(Task &task)
{
    std::cout << "in HandleRequest slicer\n";

    while (!task.m_iot_indices.empty())
    {
        int idx = task.m_iot_indices.back();

        WriteFragment(task.m_iotFd, idx);

        task.m_iot_indices.pop_back();
    }
}

void ReqSlicer::WriteFragment(int iotFd, int idx)
{
    std::cout << "in WriteFragment\n";

    AtlasHeader atlas_header;    

    atlas_header.m_requestUid = m_reqID;
    atlas_header.m_fragmentNum = idx;
    atlas_header.m_alarmUid = 0;
    atlas_header.m_type = m_bioReq->reqType;
    atlas_header.m_len = SLICE_SIZE;

    atlas_header.m_iotOffset = (m_bioReq->offset + idx * SLICE_SIZE) /* / SLICE_SIZE */ / m_fds.size();
    
    std::cout << "iotFd = " << iotFd << std::endl;
    std::cout << "atlas_header.m_requestUid = " << atlas_header.m_requestUid << std::endl;
    std::cout << "atlas_header.m_fragmentNum = " << atlas_header.m_fragmentNum << std::endl;
    std::cout << "atlas_header->m_type = " << atlas_header.m_type << std::endl;
    std::cout << "atlas_header->m_len = " << atlas_header.m_len << std::endl;
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
        std::cout << "in ReqSlicer::HandleReply\n";

#if 1
    AtlasHeader ReplayFromIoT;

	read(iot_fd, reinterpret_cast<char*>(&ReplayFromIoT) + sizeof(uint32_t), sizeof(AtlasHeader) - sizeof(uint32_t));


    std::cout << "m_bioReq->dataLen = " << m_bioReq->dataLen << std::endl;
    std::cout << "m_bioReq->offset = " << m_bioReq->offset << std::endl;
    std::cout << "m_bioReq->reqType = " << m_bioReq->reqType << std::endl;

    std::cout << "ReplayFromIoT.m_len = " << ReplayFromIoT.m_len << std::endl;
    std::cout << "ReplayFromIoT.m_iotOffset = " << ReplayFromIoT.m_iotOffset << std::endl;
    std::cout << "ReplayFromIoT.m_type = " << ReplayFromIoT.m_type << std::endl;

	if (m_bioReq->reqType == NBD_CMD_READ)
    {
        ReadAll(iot_fd, m_bioReq->dataBuf + ReplayFromIoT.m_fragmentNum * SLICE_SIZE, /* m_bioReq->dataLen */ReplayFromIoT.m_len);
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
