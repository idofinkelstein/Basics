
#include "function.hpp"
#include <cstdio>
#include <functional>

using namespace ilrd::rd90;
//------------------- excersize


//------------------- utility function

void for_each(Function<int(void)> action )
{
    action();
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
    Widget w1;
    Gadget g1;
    Function<int(void)> f1, f2;
    Function<int(void)> f3(Foo, 50);
    Function<int(void)> f4(&Widget::Action2, &w1,  50);

    for_each(Bind(&Widget::Action1, &w1, 10));
    for_each(Function<int(void)>(&Widget::Action2, &w1, 10));
    for_each(Function<int(void)>(&Gadget::Action, &g1, 10));
            
    f1 = Bind(Foo, 20);
    f2 = Bind(Foo, 20);
    f3();
    f2();
    f4();
    return 0;
}
