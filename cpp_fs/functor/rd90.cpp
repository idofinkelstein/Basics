
#include "function.hpp"
#include <cstdio>
#include <functional>

using namespace ilrd::rd90;
//------------------- excersize


//------------------- utility function

void for_each(int* vector, size_t size, Function<int> action)
{
    for (int i=0; i < size; ++i)
    {
       action(vector[i]);
    }

}


// -------------------- user code
class Widget
{
public:
    void Action1(/* Widget* const this, */ int data)
    {
        printf("DDD");
    }

    void Action2(/* Widget* const this, */ int data)
    {
        printf("Ddd");
    }
};

class Gadget
{
public:
    void Action(/* Gadget* const this, */ int data)
    {

    }
};



int main()
{
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Widget w1;
    Gadget g1;


    for_each(arr, 10, Function<Widget>(&Widget::Action1, &w1));
    for_each(arr, 10, Function<Widget>(&Widget::Action2, &w1));
    for_each(arr, 10, Function<Gadget>(&Gadget::Action, &g1));


    return 0;
}
