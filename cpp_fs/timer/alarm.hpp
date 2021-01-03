/******************************************************************************
* Project name:					 	timer                ***     *******
* Developer: 						Inbal Elmalech        *      *
* Project Lauch: 					Dec 30, 2020          *      ****
* Project completion				Jan 03, 2021          *      *
* Reviewer:                                              ***  *  *******
******************************************************************************/
#pragma once
#include <memory> /* shared_ptr */
#include <queue> /* priority_queue */
#include <chrono> /* duration, time_point */
#include <unordered_map> /* unordered_map */
#include "function.hpp" /* Function */
#include <sys/timerfd.h>
#include <cstring>

#include "reactor.hpp"

namespace ilrd 
{
namespace rd90 
{

using SysClock = std::chrono::system_clock;
using TimePoint = std::chrono::time_point<SysClock>;
using Duration = std::chrono::duration<double>;
/*
Questions:
1. TimerWheel::SetAlarm - what type does it receive?
*/
/******************************   Class Timer   ******************************/

class IAlarm
{
public:
    virtual void Arm(Duration delta) = 0;
    virtual void RegisterOnEvent(Function<void(void)> func) = 0;
};

/*****************************************************************************/

class AlarmFd : public IAlarm
{
/* To calculate the nanosecs required for the itimerspec struct:
nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>
                                    (interval).count()
*/
public:
    AlarmFd(Reactor<Epoll>& react);
    ~AlarmFd();
    AlarmFd(const AlarmFd&) = delete;/* UNCOPYABLE */
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


/*****************************************************************************/

/*
int main()
{
    Reactor<Epoll> react;
    TimerWheel<TimerFd> tw(new TimerFd(react));

    TimerWheel::TimerId id = tw.SetAlarm(duration, Bind(my_handler));
    // my_handler will be return void

    tw.CancelAlarm(id);

    react.Run();
    return (0);   
}

TimerWheel - has its own hpp file with the implementation
TimerFd is a separate hpp and cpp file
std::chrono::system_clock::now(); -> is how we get current time
This function's return value also can be used with +/- operators
std::chrono::nanoseconds is the duration paramater
// nanosec is the type name, the units can be seconds or milliseconds etc.
std::chrono::time_point<std::chrono::system_clock> -> is the way we keep the time

*/

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

AlarmFd::AlarmFd(Reactor<Epoll> &react): m_react(react), m_timerFd(timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC))
{
    m_react.Add(m_timerFd, Bind(&AlarmFd::OnTimerHandler, this, m_timerFd));
}

AlarmFd::~AlarmFd()
{
    m_react.Remove(m_timerFd);
}

void AlarmFd::Arm(ilrd::rd90::Duration delta)
{
    struct itimerspec ts;
    memset(&ts, 0, sizeof(itimerspec));

    if (-1 == timerfd_settime(m_timerFd, 0, &ts, NULL))
    {
        throw ("timerfd_settime");
    }
}

void AlarmFd::RegisterOnEvent(ilrd::rd90::Function<void ()> func)
{
    m_timerFunc = func;
}

void AlarmFd::OnTimerHandler(int fd)
{
    read(fd, )

    m_timer_func();
}

} // namespace rd90
} // namespace ilrd

/* auto nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(interval).count();  */

/* using TimePoint = std::chrono::time_point<std::chrono::system_clock>;  */