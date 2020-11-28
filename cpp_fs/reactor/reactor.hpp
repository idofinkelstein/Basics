
#pragma once
#include <map>
#include <iterator>
#include <memory>

#include "function.hpp"
#include "monitor.hpp"

namespace ilrd
{
namespace rd90
{

template <typename MONITOR_TYPE>
class Reactor
{
public:
    Reactor(MONITOR_TYPE *monitor);
    ~Reactor() = default;
    Reactor(const Reactor &other) = delete;
    Reactor operator=(const Reactor& other) = delete;

	void Add(int fd, Function<void(int)> action);
	void Remove(int fd);
	void Run();
private:
    std::shared_ptr<MONITOR_TYPE> m_monitor;
    std::map<int, Function<void(int)> > dict;
};

template<typename MONITOR_TYPE> 
Reactor<MONITOR_TYPE>::Reactor(MONITOR_TYPE *monitor) : m_monitor(monitor)
{}

template <typename MONITOR_TYPE>
void Reactor<MONITOR_TYPE>::Add(int fd, Function<void(int)> action)
{
	dict[fd] = action;
	m_monitor->Add(fd);
}

template <typename MONITOR_TYPE>
void Reactor<MONITOR_TYPE>::Remove(int fd)
{

}

template <typename MONITOR_TYPE>
void Reactor<MONITOR_TYPE>::Run()
{
	int num_of_events = 0;
	int event = 0;

	while (1)
	{
		num_of_events = m_monitor->WaitForEvent();

		for (int i = 0; i < num_of_events; ++i)
		{
			event = m_monitor->GetNextFd();
			dict[event](event);
		}
	}

}


} // rd90
} // ilrd
