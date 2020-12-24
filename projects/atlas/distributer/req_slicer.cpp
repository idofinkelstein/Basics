
#include "distributor.hpp"
#include "request_dispatcher2.hpp"
#include <unistd.h>

namespace ilrd
{
namespace rd90
{

ReqSlicer::ReqSlicer(int bio_fd, uint32_t reqID)
: m_bio_fd(bio_fd), m_reqID(reqID)
{
    m_bioReq = std::shared_ptr<BioRequest>(BioRequestRead(bio_fd));
    if (NULL == m_bioReq)
    {
        throw("BioRequestRead");
    }
}

ReqSlicer::~ReqSlicer()
{
    BioRequestDone(&(*m_bioReq), 0);
}

uint32_t ReqSlicer::GetRequestID(int iot_fd)
{
    uint32_t id;

    if (0 > read(iot_fd,&id, sizeof(uint32_t)))
    {
         throw("read\n");
    } 

    return id;
}

void ReqSlicer::HandleRequest(Task &task)
{
    while (!task.m_iot_indices.empty())
    {
        int idx = task.m_iot_indices.back();

        WriteFragment(task.m_iotFd, idx);

        task.m_iot_indices.pop_back();
    }
}

void ReqSlicer::WriteFragment(int iotFd, int idx)
{
    AtlasHeader atlas_header;    

    atlas_header.m_fragmentNum = idx;


    atlas_header.m_alarmUid = 0;

    atlas_header.m_type = m_bioReq->reqType;

    atlas_header.m_len = m_bioReq->dataLen;

    atlas_header.m_iotOffset = (m_bioReq->offset + idx * SLICE_SIZE) / iotNum;

    if(-1 == write(iotFd, &atlas_header, sizeof(AtlasHeader)))
    {
        throw("write failed");
    }

    // If write request - send data
    if(atlas_header.m_type == NBD_CMD_WRITE)
    {
        if(-1 == write(iotFd, m_bioReq->dataBuf, m_bioReq->dataLen))
        {
            throw("write failed");
        }
    }
}


bool ReqSlicer::HandleReply(int iot_fd)
{
    AtlasHeader ReplayFromIoT;
	BioRequest *ReplayToNBD = NULL;

	read(iot_fd, reinterpret_cast<char *>(&ReplayFromIoT), sizeof(AtlasHeader));
	ReplayToNBD = *reinterpret_cast<BioRequest**>(&ReplayFromIoT);

	//processes reply
    ReplayToNBD->dataLen = ReplayFromIoT.m_len;
    ReplayToNBD->offset = ReplayFromIoT.m_iotOffset;
    ReplayToNBD->reqType = ReplayFromIoT.m_type;

	if (ReplayToNBD->reqType == NBD_CMD_READ)
    {
        ReadAll(iot_fd, ReplayToNBD->dataBuf, ReplayToNBD->dataLen);
    }
   

    m_indices.erase(iot_fd);

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

} // namespace rd90
} // namespace ilrd