#include "timer_wheel.hpp"
#include "reactor.hpp"
#include <iostream>
using namespace ilrd::rd90;

void foo(int a)
{
    (void)a;
    std::cout << "hi" << std::endl;
}

int main()
{
    Reactor<Epoll> react(new Epoll(3));
    TimerWheel<AlarmFd> timerWheel(new AlarmFd(react));

    timerWheel.SetAlarm(std::chrono::duration<int64_t, std::nano>(20l * ::G), Bind(&::foo, 5));

    react.Run();

    return 0;
}