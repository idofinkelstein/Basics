/******************************************************************************
* Project name:					 	threadpool           ***     *******
* Developer: 						Ido Finkelstein       *      *
* Project Launch: 					Dec 03, 2020          *      ****
* Project completion				Dec 07, 2020          *      *
* Reviewer:                         unknown        		 ***  *  *
******************************************************************************/

#include <cstdio>
#include "threadpool.hpp"

namespace ilrd
{
namespace rd90
{



ThreadPool::ThreadPool(size_t nofThreads)
: m_maxThreads(nofThreads), 
  m_activeThreads(m_maxThreads),
  m_sem(nofThreads)
{
	for(int i = 0; i < m_maxThreads; ++i)
    {
        m_pool.push_back(std::thread(&ThreadPool::ThreadFunc, this, i));
    }
}

/*---------------------------------------------------------------------------*/

ThreadPool::~ThreadPool()
{	
    for(int i = 0; i < m_maxThreads; ++i)
    {
        m_pool[i].join();
    }
}

/*---------------------------------------------------------------------------*/

void ThreadPool::ThreadFunc(int debugging)
{
    std::shared_ptr<Task> currTask;

	while (1)
	{      
		m_tasks.Dequeue(currTask);
		currTask->Set(currTask->RunFunc());    
	}
}

/*---------------------------------------------------------------------------*/

void ThreadPool::Tune(int delta)
{

	int nofThreads = m_activeThreads + delta;

    if (delta > 0 && nofThreads < m_maxThreads)
    {
        while(delta--)
        {
            m_sem.Post();
        }
    }
    else if (delta < 0 && nofThreads > 0)
    {
        delta = -delta;
        while(delta--)
        {
            Async(Bind(&ThreadPool::WaitTask, this, 5), ThreadPool::HIGH);
        }
    }
}



ThreadPool::Future ThreadPool::Async(Function<int(void)> func, Priority pri)
{
    std::shared_ptr<Task> taskptr(new Task(func, pri));

    m_tasks.Enqueue(taskptr);

    return Future(taskptr);
}


ThreadPool::Task::Task(Function<int(void)> func, Priority pri)
: m_func(func), 
  m_pri(pri),
  m_sem(0) {}

int ThreadPool::Task::RunFunc()
{
    return m_func();
}

void ThreadPool::Task::Set(int retVal)
{
    m_retVal = retVal;
}

bool ThreadPool::Task::Compare::operator()(const std::shared_ptr<Task> &lhs, const std::shared_ptr<Task> &rhs)
{
    return (lhs->m_pri < rhs->m_pri);
}

int ThreadPool::WaitTask(int arg)
{
    (void)arg;

    m_sem.Wait();

    return 0;
}

int ThreadPool::Future::Wait()
{
    m_task->m_sem.Wait();
    return (m_task->m_retVal);
}

ThreadPool::Future::Future(std::shared_ptr<ThreadPool::Task> task) : m_task(task) {}

} // namespace rd90
} // namespace ilrd