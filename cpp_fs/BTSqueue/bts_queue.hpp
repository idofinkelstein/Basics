#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>

namespace ilrd
{
namespace rd90
{

template<typename T, typename U>
class BTSQueue
{
public:
    explicit BTSQueue();
    ~BTSQueue();
    BTSQueue(const BTSQueue &other) = delete;
    void operator=(const BTSQueue &other) = delete;

    void Dequeue(T &element);
    void Enqueue(const T &element);
    size_t Size();
    bool IsEmpty();


private:
    std::priority_queue<T, std::vector<T>, U> m_queue;
    std::mutex m_mtx;
    std::condition_variable m_conVar;
};

template<typename T, typename U>
BTSQueue<T, U>::BTSQueue()
{
}

template<typename T, typename U>
BTSQueue<T, U>::~BTSQueue()
{
}


template<typename T, typename U>
void BTSQueue<T, U>::Dequeue(T &element)
{
    std::unique_lock<std::mutex> mlock(m_mtx);
    while (m_queue.empty())
    {
      m_conVar.wait(mlock);
    }
    element = m_queue.top();
    m_queue.pop();
}


template<typename T, typename U>
void BTSQueue<T, U>::Enqueue(const T &element)
{
    std::unique_lock<std::mutex> mlock(m_mtx);
    m_queue.push(element);
    mlock.unlock();
    m_conVar.notify_one();
}

template<typename T, typename U>
size_t BTSQueue<T, U>::Size()
{
    std::unique_lock<std::mutex> mlock(m_mtx);

    return m_queue.size();
}

template<typename T, typename U>
bool BTSQueue<T, U>::IsEmpty()
{
    std::unique_lock<std::mutex> mlock(m_mtx);

    return m_queue.empty();
}


} // rd90
} // ilrd