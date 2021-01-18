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

class ICommand
{
public:
    virtual void ExecuteRequest(AtlasHeader& header, BioRequest *bio, int iotFd, int idx) = 0;
    virtual void ExecuteReplay(const AtlasHeader& header, BioRequest *bio, int iotFd) = 0;

    virtual ~ICommand() = default;

};

class Read : public ICommand
{
public:
    explicit Read(int a){(void)a;}
    void ExecuteRequest( AtlasHeader& header, BioRequest *bio, int iotFd, int idx);
    void ExecuteReplay(const AtlasHeader& header, BioRequest *bio, int iotFd);

    Read(const Read&) = delete;
    void operator=(const Read&) = delete;
};

class Write : public ICommand
{
public:
    explicit Write(int a){(void)a;}
    void ExecuteRequest( AtlasHeader& header, BioRequest *bio, int iotFd, int idx);
    void ExecuteReplay(const AtlasHeader& header, BioRequest *bio, int iotFd);

    Write(const Write&) = delete;
    void operator=(const Write&) = delete;
};

}// rd90
}// ilrd