/******************************************************************************
* Project name:					 	threadpool           ***     *******
* Developer: 						Ido Finkelstein       *      *
* Project Launch: 					Dec 03, 2020          *      ****
* Project completion				Dec 07, 2020          *      *
* Reviewer:                         unknown        		 ***  *  *
******************************************************************************/

#include "threadpool.hpp"

using namespace ilrd::rd90;
typedef int(*fPtr_t)(int);


int Foo(int a);
int Bar(int a);
int FooBar(int a);
int Fifi(int a);

int main()
{
    ThreadPool tp(8);
    ThreadPool::Future fArr[8];
    fPtr_t funcArr[8];
    int size = sizeof(funcArr) / sizeof(funcArr[0]);

    funcArr[0] = Foo;
    funcArr[1] = Bar;
    funcArr[2] = FooBar;
    funcArr[3] = Fifi;
    funcArr[4] = Foo;
    funcArr[5] = Bar;
    funcArr[6] = FooBar;
    funcArr[7] = Fifi;

    for (int i = 0; i < size; ++i)
    {
        fArr[i] = tp.Async(Bind(funcArr[i], i), ThreadPool::HIGH);
    }


    for (int i = 0; i < size; ++i)
    {
        fArr[i] = tp.Async(Bind(funcArr[i], i), ThreadPool::MID);
    }

    //tp.Tune(1);
   //tp.Tune(-2);

    for (int i = 0; i < size; ++i)
    {
        std::cout << fArr[i].Wait() << std::endl;
    }
    
    //tp.Tune(4);

    return (0);
}


int Foo(int a)
{
    std::cout << "Foo!" << std::endl;
    return a;
}

int Bar(int a)
{
    std::cout << "Bar!" << std::endl;
    return a;
}

int FooBar(int a)
{
    std::cout << "FooBar!!" << std::endl;
    return a;
}

int Fifi(int a)
{
    std::cout << "Fifi!" << std::endl;
    return a;
}