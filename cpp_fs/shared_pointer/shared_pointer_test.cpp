#include <string>
#include <iostream>

#include "SmartPointers.hpp"
using namespace ilrd::rd90;

class Widget {int w;};
class Gadget : public Widget {int g;};

int main()
{
    SharedPtr<std::string> sPtr(new std::string("hello"));

    SharedPtr<int> ptr1(new int(4));
    SharedPtr<int> ptr3(new int(5));

    ptr3 = ptr1;
    SharedPtr<int> ptr2(ptr1);

    sPtr->compare("ello");

    std::cout << *sPtr << std::endl;

    SharedPtr<Gadget> ptr4(new Gadget);
    SharedPtr<Widget> ptr5(new Widget);

    SharedPtr<Widget> ptr6(ptr4);
    ptr5 = ptr4;
    //ptr5 = ptr4;  base = derived

    return 0;
}