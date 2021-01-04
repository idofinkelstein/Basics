/******************************************************************************
* Project name:					 	alarm                     
* Developer: 						Ido Finkelstein        
* Project Lauch: 					Dec 30, 2020          
* Project completion				Jan 03, 2021          
* Reviewer:                                              
******************************************************************************/
#pragma once

#include <memory>           /* shared_ptr */
#include <queue>            /* priority_queue */
#include <chrono>           /* duration, time_point */
#include <unordered_map>    /* unordered_map */
#include "function.hpp"     /* Function, Bind */
#include <sys/timerfd.h>    /* timerfd API */

#include "reactor.hpp"      /* reactor */

const int G = 1000000000;

namespace ilrd 
{
namespace rd90 
{

using Duration = std::chrono::duration<double>;
using System_Clock = std::chrono::system_clock;
using TimePoint = std::chrono::time_point<System_Clock>;

/*********************** Abstract Class Ialarm  *******************************/

class IAlarm
{
public:
    virtual void Arm(Duration delta) = 0;
    virtual void RegisterOnEvent(Function<void(void)> func) = 0;
    virtual ~IAlarm() = default;
};

/*****************************************************************************/

class AlarmFd : public IAlarm
{
public:
    AlarmFd(Reactor<Epoll> &react);
    ~AlarmFd();

    /* UNCOPYABLE */
    AlarmFd(const AlarmFd&) = delete;
    AlarmFd& operator=(const AlarmFd&) = delete;

    void Arm(Duration delta);
    void RegisterOnEvent(Function<void(void)> func);

private:   
    Reactor<Epoll>&      m_react;
    int                  m_timerFd;
    Function<void(void)> m_timerFunc;
    
    void OnTimerHandler(int fd); // read + call m_timer_func
};

/*---------------------------------------------------------------------------*/

AlarmFd::AlarmFd(Reactor<Epoll> &react): m_react(react), m_timerFd(timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC))
{
    m_react.Add(m_timerFd, Bind(&AlarmFd::OnTimerHandler, this, m_timerFd));
}
/*---------------------------------------------------------------------------*/
AlarmFd::~AlarmFd()
{
    m_react.Remove(m_timerFd);
    close(m_timerFd);
}
/*---------------------------------------------------------------------------*/
void AlarmFd::Arm(Duration delta)
{
    itimerspec ts;
    auto nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(delta).count();

    auto second = nanoSec / ::G;
    nanoSec %= ::G;

    ts.it_value.tv_sec = second;
    ts.it_value.tv_nsec = nanoSec;
    ts.it_interval.tv_sec = 0;
    ts.it_interval.tv_nsec = 0;

    if (-1 == timerfd_settime(m_timerFd, 0, &ts, NULL))
    {
        throw ("timerfd_settime");
    }
}
/*---------------------------------------------------------------------------*/
void AlarmFd::RegisterOnEvent(ilrd::rd90::Function<void ()> func)
{
    m_timerFunc = func;
}
/*---------------------------------------------------------------------------*/
void AlarmFd::OnTimerHandler(int notUsed)
{
    (void)notUsed;
    uint64_t numExp = 0;
    int64_t n = read(m_timerFd, &numExp, sizeof(uint64_t));
    if (n != sizeof(uint64_t))
    {
        exit(EXIT_FAILURE);
    }
    m_timerFunc();
}

} // namespace rd90
} // namespace ilrd

/*
-------------------------------------------
-----------chrono example------------------
-------------------------------------------

long fibonacci(unsigned n)
{
    if (n < 2) return n;} // namespace rd90
    return fibonacci(n-1} // namespace ilrd fibonacci(n-2);
}
 
int main()
{
    auto start = std::chrono::steady_clock::now();
    std::cout << "f(42) = " << fibonacci(42) << '\n';
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}

Possible output:
struct itimerspec ts;
f(42) = 267914296
elapsed time: 1.88232s

*/

/* auto nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(interval).count();  */
