#pragma once

#include <cstdlib> 
#include <set> // std::set

#include "function.hpp" // Function

/*---------------------------------------------------------------------------*/

namespace ilrd
{
namespace rd90
{

/*************************** Class Dispatcher *********************************/

class CallBack;

class Dispatcher
{
public:
    void Subscribe(CallBack*);
    void UnSubscribe(CallBack*);
    

    void Notify();

private:
    std::set<CallBack*> m_callbacks;
};
/*************************** Class CallBack ***********************************/

class CallBack
{
public:
    CallBack(const Function<void(void)>& on_update_func);
    ~CallBack();
    void operator()();

    void RegisterDispacher(Dispatcher *disp);

private:
    Function<void(void)> m_on_update_func;
    Dispatcher* m_disp;
};

/*---------------------------------------------------------------------------*/
 

} // namespace rd90
} // namespace ilrd
