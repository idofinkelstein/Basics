#include "semaphore.hpp"

int main()
{
    Semaphore mySem(16, 16);

    mySem.Wait();
    mySem.Post();
    mySem.Get();

    return 0;
}