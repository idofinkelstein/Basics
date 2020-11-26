#include <cstdlib>
#include "reactor.hpp"

using namespace ilrd::rd90;

int main()
{
    Reactor<Select> reactor(new Select);

    return 0;
}
