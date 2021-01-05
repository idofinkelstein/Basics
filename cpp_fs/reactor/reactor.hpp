
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

	void Add(int fd, const Function<void(void)> &action);
	void Remove(int fd);
	void Run();
private:
    std::shared_ptr<MONITOR_TYPE> m_monitor;
    std::map<int, Function<void(void)> > dict;
};

template<typename MONITOR_TYPE> 
Reactor<MONITOR_TYPE>::Reactor(MONITOR_TYPE *monitor) : m_monitor(monitor)
{
	// 
	(void)static_cast<IMonitor*>(monitor);
}

template <typename MONITOR_TYPE>
void Reactor<MONITOR_TYPE>::Add(int fd, const Function<void(void)> &action)
{
	dict[fd] = action;
	m_monitor->MONITOR_TYPE::Add(fd);
}

template <typename MONITOR_TYPE>
void Reactor<MONITOR_TYPE>::Remove(int fd)
{
	m_monitor->Remove(fd);
    dict.erase(fd);
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
			dict[event]();
		}
		std::cout << "react - while(1)" << std::endl;
	}

}


} // rd90
} // ilrd
