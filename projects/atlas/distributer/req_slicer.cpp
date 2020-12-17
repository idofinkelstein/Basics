
#include "distributor.hpp"

namespace ilrd
{
namespace rd90
{

ReqSlicer::ReqSlicer(int bio_fd, uint32_t reqID)
{

}

ReqSlicer::~ReqSlicer()
{

}

int ReqSlicer::GetRequestID(int iot_fd)
{

}

void ReqSlicer::HandleRequest(const ilrd::rd90::Task &task)
{

}

bool ReqSlicer::HandleReply(int iot_fd)
{
    m_bufSlices.erase(iot_fd);

    if (m_bufSlices.size() == 0)
    {
        return true;
    }

    return false;
}

uint64_t ReqSlicer::GetOffset()
{
    return m_bioReq->offset;
}

} // namespace rd90
} // namespace ilrd