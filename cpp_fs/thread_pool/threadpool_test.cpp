/******************************************************************************
* Project name:					 	threadpool           ***     *******
* Developer: 						Ido Finkelstein       *      *
* Project Launch: 					Dec 03, 2020          *      ****
* Project completion				Dec 07, 2020          *      *
* Reviewer:                         unknown        		 ***  *  *
******************************************************************************/


#include "threadpool.hpp"

/*******************************   MAIN   ************************************/
int Foo(int a)
{
    std::cout << a << std::endl;
    return a;
}


using namespace ilrd::rd90;

int main()
{
    ThreadPool tp(size_t(8));
    
    ThreadPool::Future f1 = tp.Async(Bind(Foo, 5), ThreadPool::HIGH);

    //f1.wait();
    
    tp.Tune(4);

    return (0);
}

/*****************************************************************************/