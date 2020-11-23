
#include "function.hpp"
#include <cstdio>
#include <functional>

using namespace ilrd::rd90;
//------------------- excersize


//------------------- utility function

void for_each(int* vector, size_t size,  Function action)
{
    for (size_t i = 0; i < size; ++i)
    {
       action(vector[i]);
    }

}

void Foo(int val)
{
    std::cout << "free function Foo" << std::endl;
    std::cout << "the value is: " << val << std::endl;
}

// -------------------- user code
class Widget
{
public:
    void Action1(/* Widget* const this, */ int data)
    {
        std::cout << "widget action1 " << data << std::endl;
    }

    void Action2(/* Widget* const this, */ int data)
    {
        std::cout << "widget action2 " << data << std::endl;
    }
};

class Gadget
{
public:
    void Action(/* Gadget* const this, */ int data)
    {
        std::cout << "gadget action " << data << std::endl;
    }
};



int main()
{
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Widget w1;
    Gadget g1;
    Function f1(Foo);

    for_each(arr, 10, Function(&Widget::Action1, &w1));
    for_each(arr, 10, Function(&Widget::Action2, &w1));
    for_each(arr, 10, Function(&Gadget::Action, &g1));

    f1(10);
    return 0;
}
