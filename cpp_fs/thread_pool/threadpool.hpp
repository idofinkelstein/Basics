/******************************************************************************
* Project name:					 	threadpool           ***     *******
* Developer: 						Ido Finkelstein       *      *
* Project Launch: 					Dec 03, 2020          *      ****
* Project completion				Dec 07, 2020          *      *
* Reviewer:                         unknown        		 ***  *  *
******************************************************************************/
#pragma once

#include <vector>
#include <thread>
#include <memory> // shared pointer

#include "bts_queue.hpp"
#include "function.hpp"
#include "semaphore.hpp"

namespace ilrd
{
namespace rd90
{


class ThreadPool
{
private:
	// forward declaration
	class Task;
public:
	class Future;

	enum Priority
	{
		SUPER_LOW = 0, // Do not use this priority, saved for internal purposes.
		LOW,
		MID_LOW,
		MID,
		MID_HIGH,
		HIGH,
		SUPER_HIGH = 10 // Do not use this priority, saved for internal purposes.
	};

	explicit ThreadPool(size_t nofThreads = 1);
	~ThreadPool();

	// adds or removes available threads by delta
	void Tune(int delta);
	Future Async(Function<int(void)> func, Priority pri);

	// Deleted functions
	ThreadPool(const ThreadPool& other) = delete;
	ThreadPool& operator=(const ThreadPool& other) = delete;

	class Future
	{
	public:
		explicit Future() = default;
		explicit Future(std::shared_ptr<Task> task);
		//void operator=(const Future &) = default;
		int Wait();
	private:
		std::shared_ptr<Task> m_task;
	};

private:
	class Task
	{
	public:
		explicit Task(Function<int(void)> func, Priority pri);
		explicit Task() : m_sem(0, 1){}
		int RunTask();
		void Set(int retVal);
		friend class Future;

		class Compare
		{
		public:
			bool operator()(const std::shared_ptr<Task> &lhs,
						    const std::shared_ptr<Task> &rhs);
		};

	private:
		Function<int(void)> m_func;
		Priority 			m_pri;
		int 				m_retVal;
		Semaphore 			m_sem;
	};

	void ThreadFunc(int debugging);
	int WaitTask(int);
	int BadApple(int);

	int 											 m_maxThreads;
	int 											 m_activeThreads;
	Semaphore 										 m_sem;
	std::vector<std::thread> 						 m_pool;
	BTSQueue< std::shared_ptr<Task>, Task::Compare > m_tasks;
};
/*****************************************************************************/

} // namespace rd90
} // namespace ilrd