#include <iostream>

#include "d_vector.hpp"

using namespace ilrd::rd90;

int main()
{
    DVector<int> v1(4);

    for(size_t i = 0; i < 100; ++i)
    {
        v1.PushBack(5);
    }
    return 0;
}