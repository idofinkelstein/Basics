/* 


*/

#pragma once

#include <iostream>             // ostream
#include <set>                  // set
#include <memory>               // shared_ptr
#include <vector>               // std::vector

#include "distributor.hpp"      // distributer class
#include "bio_access.h"         // bio_request


/*---------------------------------------------------------------------------*/

namespace ilrd
{
namespace rd90
{

/*********************   Free Functions declarations    **********************/
struct AtlasHeader
{
    uint32_t    m_requestUid;   // not to be used by IoT; must be first field
    uint32_t    m_fragmentNum;  // not to be used by IoT
    uint32_t    m_alarmUid;     // not to be used by IoT
    uint32_t    m_iotOffset;
    uint32_t    m_type;
    uint32_t    m_len;          // how many bytes to write OR to read
};


/************************   Classes declarations    **************************/

struct Task
{
    int m_iotFd;
    std::vector<uint32_t> m_iot_indices;
};


class ReqSlicer
{
public:
    explicit ReqSlicer(int bio_fd, uint32_t reqID);
    ~ReqSlicer();

    ReqSlicer(const ReqSlicer& other) = delete;
    ReqSlicer& operator=(const ReqSlicer& other) = delete;

    static uint32_t GetRequestID(int iot_fd);
    void HandleRequest(Task &task);
    bool HandleReply(int iot_fd); // returns status indicating whether it 
                                  // was the last reply or not
    uint64_t GetOffset(); 
    uint32_t GetDataLen();
    uint32_t GetReqType();                            

private:
    std::set<int> m_indices; // indices
    std::shared_ptr<BioRequest> m_bioReq;
    uint32_t m_reqID;
    int m_bio_fd;

    void WriteFragment(int iotFd, int idx);
};

/*---------------------------------------------------------------------------*/

} // namespace rd90
} // namespace ilrd






