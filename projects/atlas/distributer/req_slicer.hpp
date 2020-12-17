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


/************************   Classes declarations    **************************/

struct Task
{
    int m_iot;
    std::vector<uint32_t> m_iot_fd;
};


class ReqSlicer
{
public:
    explicit ReqSlicer(int bio_fd, uint32_t reqID);
    ~ReqSlicer();

    ReqSlicer(const ReqSlicer& other) = delete;
    ReqSlicer& operator=(const ReqSlicer& other) = delete;

    static int GetRequestID(int iot_fd);
    void HandleRequest(const Task &task);
    bool HandleReply(int iot_fd); // returns status indicating whether it 
                                  // was the last reply or not
    uint64_t GetOffset();                              

private:
    std::set<int> m_bufSlices; // indices
    BioRequest *m_bioReq;
    uint32_t m_reqID;
};

/*---------------------------------------------------------------------------*/

} // namespace rd90
} // namespace ilrd






