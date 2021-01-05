#include <sys/epoll.h>
#include <iostream>
#include <cstdio> // debugging perposes

#include "monitor.hpp"

namespace ilrd
{
namespace rd90
{

Select::Select() : m_max_fd(0)
{
    FD_ZERO(&m_master);
}


void Select::Add(int fd)
{
    m_max_fd = Max(fd, m_max_fd);
    FD_SET(fd, &m_master);
}

void Select::Remove(int fd)
{
    FD_CLR(fd, &m_master);
    m_max_fd = UpdateMax();
}

int Select::WaitForEvent()
{
    m_work = m_master;
    int num_of_fds;

    num_of_fds = select(m_max_fd + 1, &m_work, NULL, NULL, NULL);

	return (num_of_fds);
}

int Select::GetNextFd()
{

	for (int i = 0; i <= m_max_fd; ++i)
	{
		if (FD_ISSET(i, &m_work))
        {
            FD_CLR(i, &m_work);
            return (i);
        }
	}

	return -1;
}

int Select::UpdateMax()
{
    for (int i = m_max_fd; i >= 0; --i)
    {
        if (FD_ISSET(i, &m_master))
        {
            return (i);
        }
    }

	return 0;
}

/*-------------------------------------------------------------------------*/

Epoll::Epoll(int max_events)
: m_max_events(max_events),
  m_curr_event(0),
  m_events (new struct epoll_event[max_events])
{
    if (-1 == (m_fd = epoll_create1(0)))
    {
		puts("Epoll epoll_create");
        throw("epoll_create");
    }
}

Epoll::~Epoll()
{
    close(m_events->data.fd);
    std::cout << "Epoll::~Epoll" << std::endl;
    delete [] m_events;
}


void Epoll::Add(int fd)
{
    // EPOLLIN - The associated file is available for read
    m_events->events = EPOLLIN;
    m_events->data.fd = fd;

    if (-1 == epoll_ctl(m_fd, EPOLL_CTL_ADD, fd, m_events))
    {
		puts("Epoll::Add epoll_ctl");
        throw ("epoll_ctl: Add");
    }
}

void Epoll::Remove(int fd)
{
    if (-1 == epoll_ctl(m_fd, EPOLL_CTL_DEL, fd, m_events))
    {
		puts("Epoll::Remove epoll_ctl");
        throw("epoll_ctl: Remove");
    }
}

int Epoll::WaitForEvent()
{
    m_curr_event = 0;
    // returns num of available fd's
    return (epoll_wait(m_fd, m_events, m_max_events, -1));
}

int Epoll::GetNextFd()
{      
   return (m_events[m_curr_event++].data.fd);
}


} // rd90
} // ilrd


// sudo sh -c "echo 4 > /sys/block/nbd0/queue/max_sectors_kb" 
