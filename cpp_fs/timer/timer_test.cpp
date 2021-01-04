#include "timer_wheel.hpp"
#include "reactor.hpp"
#include <iostream>
using namespace ilrd::rd90;

TimerWheel<AlarmFd> *pTM;    
void foo(int a)
{
    (void)a;
    std::cout << "hi" << std::endl;
}

void Print1(int a)
{
    (void)a;
    std::cout << "1" << std::endl;
}
void Print2(int a)
{
    (void)a;
    std::cout << "2" << std::endl;
}
void Print3(int a)
{
    pTM->CancelAlarm(a);
    std::cout << "3" << std::endl;
}

    
int main()
{
    Reactor<Epoll> react(new Epoll(3));
    TimerWheel<AlarmFd> timerWheel(new AlarmFd(react));
    pTM = &timerWheel;

    timerWheel.SetAlarm(std::chrono::duration<int64_t, std::nano>(5l * ::G), Bind(&::foo, 5));
    timerWheel.SetAlarm(std::chrono::duration<int64_t, std::nano>(3l * ::G), Bind(&::Print1, 5));
    auto uid2 = timerWheel.SetAlarm(std::chrono::duration<int64_t, std::nano>(2l * ::G), Bind(&::Print2, 5));
    timerWheel.SetAlarm(std::chrono::duration<int64_t, std::nano>(1l * ::G), Bind(&::Print3, int(uid2)));

    

    react.Run();

    return 0;
}