#include "observer.hpp"

namespace ilrd
{
namespace rd90
{

/*************************** Class Dispatcher *********************************/

void Dispatcher::Subscribe(CallBack *cb)
{
    m_callbacks.insert(size_t(cb));
}

void Dispatcher::Unsubscribe(ilrd::rd90::CallBack *cb)
{
    m_callbacks.erase(size_t(cb));
}

/*************************** Class CallBack ***********************************/
CallBack::CallBack(const Function<void ()> &on_update_func) : m_on_update_func(on_update_func)
{
     
}

CallBack::~CallBack()
{
    m_disp->Unsubscribe(this);
}

void CallBack::operator()()
{
    m_on_update_func();
}


void Dispatcher::Notify()
{
    std::set<size_t>::iterator it = m_callbacks.begin();
    CallBack *cb;

    for(;it != m_callbacks.end(); it++)
    {
        cb = reinterpret_cast<CallBack*>(*it);
        cb->operator();
    }
}

/*---------------------------------------------------------------------------*/


}// rd90
}// ilrd