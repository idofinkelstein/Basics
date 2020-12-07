/******************************************************************************
* Project name:					 	threadpool           ***     *******
* Developer: 						Inbal Elmalech        *      *
* Project Lauch: 					Dec 03, 2020          *      ****
* Project completion				Dec 07, 2020          *      *
* Reviewer:                                              ***  *  *******
******************************************************************************/
/**********************   PREPROCESSOR DIRECTIVES   **************************/

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
    ThreadPool tp(8);
    
    tp.Async(Bind(Foo, 5), ThreadPool::HIGH);
    // urgent private logic
    tp.SetActiveThreads(4);

    return (0);
}

/*****************************************************************************/