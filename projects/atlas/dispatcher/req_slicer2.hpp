/* 


*/

#pragma once

#include <iostream>             // ostream
#include <set>                  // set
#include <memory>               // shared_ptr
#include <vector>               // std::vector

#include "distributor.hpp"      // distributer class
#include "bio_access.h"         // bio_request
#include "atlas.hpp"            // struct AtlasHeader


/*---------------------------------------------------------------------------*/

namespace ilrd
{
namespace rd90
{


static const int SLICE_SIZE = 1024;
/************************   Classes declarations    **************************/

struct Task
{
    int m_iot;
    std::vector<uint32_t> m_iotIndices;
};


class ReqSlicer
{
public:
    explicit ReqSlicer(int bio_fd, uint32_t reqID, std::vector<int> &fds);
    ~ReqSlicer();

    ReqSlicer(const ReqSlicer& other) = delete;
    ReqSlicer& operator=(const ReqSlicer& other) = delete;

    static uint32_t GetRequestID(int iot_fd);
    //void HandleRequest(std::shared_ptr<Task>& task);
    int HandleRequest(Task task);
    bool HandleReply(int iot_fd); // returns status indicating whether it 
                                  // was the last reply or not
    uint64_t GetOffset(); 
    uint32_t GetDataLen();
    uint32_t GetReqType();



private:
    std::set<int>               m_indices; 
    std::vector<int>&           m_fds;
    BioRequest*                 m_bioReq;
    uint32_t                    m_reqID;
    int                         m_bio_fd;

    void WriteFragment(int iotFd, int idx);
};

/*---------------------------------------------------------------------------*/

} // namespace rd90
} // namespace ilrd



/* 
sudo sh -c "echo 4 > /sys/block/nbd0/queue/max_sectors_kb"
 */


