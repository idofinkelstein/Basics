#pragma once

#include <cstdint>

namespace ilrd
{
namespace rd90
{

static const int SLICE_SIZE = 1024;

struct AtlasHeader
{
    uint32_t    m_requestUid;   // not to be used by IoT; must be first field
    uint32_t    m_fragmentNum;  // not to be used by IoT
    uint32_t    m_alarmUid;     // not to be used by IoT
    uint32_t    m_iotOffset;
    uint32_t    m_type;
    uint32_t    m_len;          // how many bytes to write OR to read
};

}
}