

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
    Select(/* args */);
    ~Select();

    void Add(int fd);
    void Remove(int fd);
    int WaitForEvent();
    int GetNextFd();
private:
    fd_set m_master;
    int m_max_fd;
};




inline int Max(int a, int b)
{
    return ((a) > (b) ? (a) : (b));
}

} // rd90
} // ilrd