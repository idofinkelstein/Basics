
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

}

uint32_t ReqSlicer::GetRequestID(int iot_fd)
{
    uint32_t id;

    read(iot_fd,&id, sizeof(uint32_t)); 

    return id;
}

void ReqSlicer::HandleRequest(const ilrd::rd90::Task &task)
{
    while (!task.m_iot_indices.empty())
    {
        task.m_iot_indices.back()
    }
}

void ReqSlicer::WriteFragment(int iotFd)
{

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
   
	BioRequestDone(ReplayToNBD, 0);

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