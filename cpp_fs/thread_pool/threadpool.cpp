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

/*-------------------------class ThreadPool: Definition--------------------------*/

ThreadPool::ThreadPool(size_t nofThreads)
: m_maxThreads(nofThreads), 
  m_activeThreads(m_maxThreads),
  m_noMore(false),
  m_sem(0, nofThreads)
{
	for(int i = 0; i < m_maxThreads; ++i)
    {
        m_pool.push_back(std::thread(&ThreadPool::ThreadFunc, this, i));
    }
}

/*---------------------------------------------------------------------------*/

ThreadPool::~ThreadPool()
{	    
    m_noMore = true;

    Tune(m_maxThreads);

    for(int i = 0; i < m_maxThreads; ++i)
    {
        AsyncProxy(Bind(&ThreadPool::BadApple, this, 5), ThreadPool::SUPER_LOW);
    }
    
    for(int i = 0; i < m_maxThreads; ++i)
    {
        m_pool[i].join();
    }
}

/*---------------------------------------------------------------------------*/

void ThreadPool::ThreadFunc(int debugging)
{
    std::shared_ptr<Task> currTask;

    try
    {
        while (true)
        {      
            m_tasks.Dequeue(currTask);
            currTask->Set(currTask->RunTask());    
        }  
    }
    catch(...)
    {
        std::cout << "ThreadPool terminated" << std::endl;
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
            puts("hi delta > 0");
            m_sem.Post();
        }
    }
    else if (delta < 0 && nofThreads >= 0)
    {
        delta = -delta;
        while(delta--)
        {
            puts("hi delta < 0");
            Async(Bind(&ThreadPool::WaitTask, this, 5), ThreadPool::SUPER_HIGH);
        }
    }

    m_activeThreads = Min(m_maxThreads, Max(nofThreads, 0));
}
/*---------------------------------------------------------------------------*/

ThreadPool::Future ThreadPool::Async(Function<int(void)> func, Priority pri)
{
    if (m_noMore == true)
    {
        throw -1;
    }

    return AsyncProxy(func, pri);
}
/*---------------------------------------------------------------------------*/
ThreadPool::Future ThreadPool::AsyncProxy(Function<int(void)> func, Priority pri)
{
    std::shared_ptr<Task> taskptr(new Task(func, pri));

    m_tasks.Enqueue(taskptr);

    return Future(taskptr);
}


int ThreadPool::WaitTask(int arg)
{
    (void)arg;

    m_sem.Wait();

    return 0;
}
/*---------------------------------------------------------------------------*/

int ThreadPool::BadApple(int)
{
    throw -1;
}

/*-------------------------class Task: Definition--------------------------*/
ThreadPool::Task::Task(Function<int(void)> func, Priority pri)
: m_func(func), 
  m_pri(pri),
  m_sem(1, 1) {} // binary semaphore starts from 0
/*---------------------------------------------------------------------------*/

int ThreadPool::Task::RunTask()
{
    return m_func();
}
/*---------------------------------------------------------------------------*/

void ThreadPool::Task::Set(int retVal)
{
    m_retVal = retVal;
    m_sem.Post(); // task has returned
}
/*-------------------------class Future: Definition--------------------------*/

int ThreadPool::Future::Wait()
{
    m_task->m_sem.Wait();
    return (m_task->m_retVal);
}
/*---------------------------------------------------------------------------*/

ThreadPool::Future::Future(std::shared_ptr<ThreadPool::Task> task) : m_task(task) {}


/*-------------------------class Compare: Definition--------------------------*/

bool ThreadPool::Task::Compare::operator()(const std::shared_ptr<Task> &lhs,
                                           const std::shared_ptr<Task> &rhs)
{
    return (lhs->m_pri < rhs->m_pri);
}
/*---------------------------------------------------------------------------*/
} // namespace rd90
} // namespace ilrd