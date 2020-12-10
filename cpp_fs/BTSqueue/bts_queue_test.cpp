#include <thread>
#include <iostream>
#include <unistd.h>
#include "bts_queue.hpp"
#include <mutex>

using namespace ilrd::rd90;
class Compare;

void Producer(BTSQueue<int, Compare> *queue);
void Consumer(BTSQueue<int, Compare> *queue);
void Filler(BTSQueue<int, Compare> *queue);
void GetSize(BTSQueue<int, Compare> *queue);

class Compare
{
public:
    bool operator()(int a, int b)
    {
        return a > b;
    }
};

void Task2();

static const int N_THREADS = 5;
std::mutex mutex;

void Task1(BTSQueue<int, Compare> *queue)
{
    int item;
    for (int i = 0; i < 1000; ++i)
    {
        queue->Dequeue(item);
        std::cout << item << std::endl;
    }
}

int main()
{
    BTSQueue<int, Compare> queue;
    std::thread t[10];

    for (int i = 0; i < 10000; ++i)
    {
        queue.Enqueue(i); 
    }

    for(int i = 0; i < 10; i++)
    {
        t[i] = std::thread(Task1, &queue);
    }
    for(int i = 0; i < 10; i++)
        t[i].join();
    
    Task2();

    return 0;
}

void Task2()
{
    BTSQueue<int, Compare> queue;
    std::thread consum_thrd[N_THREADS];
    std::thread produc_thrd[N_THREADS];

    for(int i = 0; i < N_THREADS; ++i)
    {
        produc_thrd[i] = std::thread(Producer, &queue);
    }

    for(int i = 0; i < N_THREADS; ++i)
    {
        consum_thrd[i] = std::thread(Consumer, &queue);
    }

    std::thread filler(Filler, &queue);
    std::thread getSize(GetSize, &queue);

    for(int i = 0; i < N_THREADS; ++i)
    {
        consum_thrd[i].join();
        produc_thrd[i].join();
    }
    filler.join();
    getSize.join();

}

void Producer(BTSQueue<int, Compare> *queue)
{
    int i = 0;

    while(true)
    {
        queue->Enqueue(i++);

        sleep(1);
    }
}

void Consumer(BTSQueue<int, Compare> *queue)
{
    while(true)
    {
        int item;
        queue->Dequeue(item);
        mutex.lock();
        std::cout << "item = " << item << std::endl;  
        mutex.unlock();
    }
}

void Filler(BTSQueue<int, Compare> *queue)
{
    int j = 3;

    while(true)
    {
        if (queue->Size() < 100)
        {
            queue->Enqueue(++j);
            mutex.lock();
            std::cout << "filler :)" << std::endl;
            mutex.unlock();
        }
    }
}

void GetSize(BTSQueue<int, Compare> *queue)
{
    while(true)
    {
        mutex.lock();
        std::cout << "size = " << queue->Size() << std::endl;
        mutex.unlock();
    }
}