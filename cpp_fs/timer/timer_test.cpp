#include "timer_wheel.hpp"
#include "reactor.hpp"

using namespace ilrd::rd90;

int main()
{
    Reactor<Epoll> react(new Epoll(3));

    return 0;
}