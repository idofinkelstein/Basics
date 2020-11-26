
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
    Reactor(/* args */);
    ~Reactor();
private:
    std::shared_ptr<MONITOR_TYPE> m_monitor;
    std::map<int, Function<int(int)> > dict;
};

template<typename MONITOR_TYPE> 
Reactor<MONITOR_TYPE>::Reactor()
{
}

template<typename MONITOR_TYPE> 
Reactor<MONITOR_TYPE>::~Reactor()
{
}

} // rd90
} // ilrd
