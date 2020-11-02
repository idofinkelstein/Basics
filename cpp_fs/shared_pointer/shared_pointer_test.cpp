#include <string>
#include <iostream>

#include "SmartPointers.hpp"
using namespace ilrd::rd90;

int main()
{
    SharedPtr<std::string> sPtr(new std::string("hello"));

    SharedPtr<int> ptr1(new int(4));

    SharedPtr<int> ptr2(ptr1);

    sPtr->compare("ello");

    std::cout << *sPtr << std::endl;

    return 0;
}