

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

    static int Max(int a, int b)
    {
        return ((a) > (b) ? (a) : (b));
    }
};

class Epoll : public IMonitor
{
public:
    Epoll(int max_events);
    ~Epoll();

    void Add(int fd);
    void Remove(int fd);
    int WaitForEvent();
    int GetNextFd();
private:
    int m_max_events;
    int m_fd;
    int m_curr_event;
    // TODO: vector instead of array
    struct epoll_event *m_events;

};



} // rd90
} // ilrd