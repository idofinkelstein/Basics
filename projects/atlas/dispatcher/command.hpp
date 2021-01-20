#pragma once

#include <sys/types.h>  // sendmsg
#include <sys/socket.h> // sendmsg
#include <cstring>      // memset

#include "atlas.hpp"
#include "bio_access.h"

namespace ilrd
{
namespace rd90
{

struct CommandData;


class ICommand
{
public:
    virtual void ExecuteRequest() = 0;
    virtual void ExecuteReplay() = 0;

    virtual ~ICommand() = default;
protected:
    virtual void InitMsg(msghdr &message, AtlasHeader &header, int numOfFields);
};

class Read : public ICommand
{
public:
    explicit Read(CommandData* data);
    void ExecuteRequest();
    void ExecuteReplay();

    Read(const Read&) = delete;
    void operator=(const Read&) = delete;
private:
    AtlasHeader& m_header;
    BioRequest*  m_bio;
    int          m_iotFd;
    int          m_idx;
};

class Write : public ICommand
{
public:
    explicit Write(CommandData* data);
    void ExecuteRequest();
    void ExecuteReplay();

    Write(const Write&) = delete;
    void operator=(const Write&) = delete;
private:
    AtlasHeader& m_header;
    BioRequest*  m_bio;
    int          m_iotFd;
    int          m_idx;
};

struct CommandData
{
    explicit CommandData(AtlasHeader& header,
                         BioRequest*  bio,
                         int          iotFd,
                         int          idx);

    AtlasHeader& m_header;
    BioRequest*  m_bio;
    int          m_iotFd;
    int          m_idx;
};

}// rd90
}// ilrd