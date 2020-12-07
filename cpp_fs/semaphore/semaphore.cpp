#include "semaphore.hpp"

Semaphore::Semaphore(int numOfResources)
: m_resources(numOfResources), 
  m_maxResources(m_resources) {}

int Semaphore::Get()
{
    std::unique_lock<std::mutex> ul(m_mutex);
    return (m_resources);
}

void Semaphore::Wait()
{
    std::unique_lock<std::mutex> ul(m_mutex);
    
    while (m_resources == 0)
    {
        m_cv.wait(ul);
    }

    --m_resources; 
}

void Semaphore::Post()
{
    std::unique_lock<std::mutex> ul(m_mutex);

    if (m_resources < m_maxResources)
    {
        m_cv.notify_one();
        ++m_resources;
    }
}