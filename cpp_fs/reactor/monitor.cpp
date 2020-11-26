#include "monitor.hpp"

namespace ilrd
{
namespace rd90
{

Select::Select() : m_max_fd(0)
{
    FD_ZERO(&m_master);
}

Select::~Select()
{
}

void Select::Add(int fd)
{
    m_max_fd = Max(fd, m_max_fd);
    FD_SET(fd, &m_master);
}

void Select::Remove(int fd)
{
    FD_CLR(fd, &m_master);
}

int Select::WaitForEvent()
{
    m_work = m_master;
    int num_of_fds;

    num_of_fds = select(m_max_fd + 1, &m_work, NULL, NULL, NULL);
}

int Select::GetNextFd()
{

}






} // rd90
} // ilrd