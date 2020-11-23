
#include "function.hpp"
#include <cstdio>
#include <functional>

using namespace ilrd::rd90;
//------------------- excersize


//------------------- utility function

void for_each(int* vector, size_t size,  Function<int, int> action)
{
    for (size_t i = 0; i < size; ++i)
    {
       action(vector[i]);
    }

}

int Foo(int val)
{
    std::cout << "free function Foo" << std::endl;
    std::cout << "the value is: " << val << std::endl;
    return 0;
}

// -------------------- user code
class Widget
{
public:
    int Action1(/* Widget* const this, */ int data)
    {
        std::cout << "widget action1 " << data << std::endl;
        return 0;
    }

    int Action2(/* Widget* const this, */ int data)
    {
        std::cout << "widget action2 " << data << std::endl;
        return 0;
    }
};

class Gadget
{
public:
    int Action(/* Gadget* const this, */ int data)
    {
        std::cout << "gadget action " << data << std::endl;
        return 0;
    }
};



int main()
{
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Widget w1;
    Gadget g1;
    Function<int, int> f1(Foo);

    for_each(arr, 10, Function<int, int>(&Widget::Action1, &w1));
    for_each(arr, 10, Function<int, int>(&Widget::Action2, &w1));
    for_each(arr, 10, Function<int, int>(&Gadget::Action, &g1));
            
    f1(10);
    return 0;
}
