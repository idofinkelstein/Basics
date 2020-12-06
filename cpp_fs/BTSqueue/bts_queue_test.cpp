#include <thread>
#include <iostream>
#include "bts_queue.hpp"

using namespace ilrd::rd90;
BTSQueue<int> queue;

void task()
{
    int item;
    for (int i = 0; i < 1000; ++i)
    {
        queue.Dequeue(item);
        std::cout << item << std::endl;
    }
}

int main()
{
    //std::thread t[10];

    for (int i = 0; i < 10000; ++i)
    {
        queue.Enqueue(i); 
    }

    for(int i = 0; i < 10; i++)
    {
        std::thread t (task);
        t.join();
    }

    


    return 0;
}