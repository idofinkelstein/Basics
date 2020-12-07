
#include "threadpool.hpp"

namespace ilrd
{
namespace rd90
{


ThreadPool::ThreadPool(size_t nofThreads) : m_nOfThreads(nofThreads)
{
	for(int i = 0; i < m_nOfThreads; ++i)
    {
        m_pool.push_back(std::thread(ThreadFunc, i));
    }
}

/*---------------------------------------------------------------------------*/

ThreadPool::~ThreadPool()
{
	// block new tasks from entering queue
	// when queue is empty, signal to threads to break out of their loop
	// join all threads

    for(int i = 0; i < m_nOfThreads; ++i)
    {
        m_pool[i].join();
    }
}

/*---------------------------------------------------------------------------*/

void ThreadPool::ThreadFunc(int debugging)
{
    Task currTask;

	while (1)
	{      
		m_tasks.Dequeue(currTask);
		currTask.RunFunc();
	}
}

/*---------------------------------------------------------------------------*/

void ThreadPool::SetActiveThreads(size_t nof_threads)
{
	m_activeThreads = nof_threads;
}

void ThreadPool::Async(Function<int(void)> func, Priority pri)
{
    m_tasks.Enqueue(Task(func, pri));
}


ThreadPool::Task::Task(Function<int(void)> func, Priority pri)
: m_func(func), 
  m_pri(pri) {}

int ThreadPool::Task::RunFunc()
{
    return m_func();
}

} // namespace rd90
} // namespace ilrd