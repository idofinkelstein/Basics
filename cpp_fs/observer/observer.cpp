#include "observer.hpp"

namespace ilrd
{
namespace rd90
{

/*************************** Class Dispatcher *********************************/

void Dispatcher::Subscribe(CallBack *cb)
{
    m_callbacks.insert(cb);
    cb->RegisterDispacher(this);
}

void Dispatcher::UnSubscribe(CallBack *cb)
{
    m_callbacks.erase(cb);
}

/*************************** Class CallBack ***********************************/
CallBack::CallBack(const Function<void ()> &on_update_func) : m_on_update_func(on_update_func)
{}

CallBack::~CallBack()
{
    m_disp->UnSubscribe(this);
}

void CallBack::operator()()
{
    m_on_update_func();
}


void Dispatcher::Notify()
{
    std::set<CallBack*>::iterator it = m_callbacks.begin();

    for(;it != m_callbacks.end(); it++)
    {
        (*it)->operator()();
    }
}

/*---------------------------------------------------------------------------*/

void CallBack::RegisterDispacher(Dispatcher *disp)
{
    m_disp = disp;
}



}// rd90
}// ilrd