#pragma once

#include <mutex>
#include <condition_variable>

class Semaphore
{
public:
    explicit Semaphore(int numOfResources);
    Semaphore(const Semaphore &) = delete;
    void operator=(const Semaphore &) = delete;

    int Get();
    void Wait();
    void Post();
private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    int m_resources;
    const int m_maxResources;
};

