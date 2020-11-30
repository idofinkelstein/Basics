

#pragma once

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

namespace ilrd
{
namespace rd90
{

class IMonitor
{
public:
    virtual void Add(int fd) = 0;
    virtual void Remove(int fd) = 0;
    virtual int WaitForEvent() = 0;
    virtual int GetNextFd() = 0;
    virtual ~IMonitor() = default;
};

class Select : public IMonitor
{
public:
    Select();
    ~Select() = default;

    void Add(int fd);
    void Remove(int fd);
    int WaitForEvent();
    int GetNextFd();
private:
    fd_set m_master;
    fd_set m_work;
    int m_max_fd;

    int UpdateMax();
};

class Epol : public IMonitor
{
public:
    Epol();
    ~Epol() = default;

    void Add(int fd);
    void Remove(int fd);
    int WaitForEvent();
    int GetNextFd();
private:
    
};




inline int Max(int a, int b)
{
    return ((a) > (b) ? (a) : (b));
}

} // rd90
} // ilrd