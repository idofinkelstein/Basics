#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>

namespace ilrd
{
namespace rd90
{

template<typename T>
class BTSQueue
{
public:
    BTSQueue(/* args */);
    ~BTSQueue();
    BTSQueue(const BTSQueue &other) = delete;
    operator=(const BTSQueue &other) = delete;

    T &Dequeue();
    void Enqueue(const T &element);
    size_t Size();
    int IsEmpty();

private:
    std::priority_queue<T> m_queue;
    std::mutex m_mtx;
    std::condition_variable m_conVar;
    std::unique_lock<T> m_uLock;
};

template<typename T>
BTSQueue<T>::BTSQueue(/* args */)
{
}

template<typename T>
BTSQueue<T>::~BTSQueue()
{
}

template<class T> T &BTSQueue<T>::Dequeue()
{

}


} // rd90
} // ilrd