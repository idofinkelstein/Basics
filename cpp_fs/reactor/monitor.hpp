

#pragma once

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

namespace ilrd
{
namespace rd90
{

class Select
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




inline int Max(int a, int b)
{
    return ((a) > (b) ? (a) : (b));
}

} // rd90
} // ilrd