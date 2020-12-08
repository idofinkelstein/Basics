/******************************************************************************
* Project name:					 	threadpool           ***     *******
* Developer: 						Ido Finkelstein       *      *
* Project Launch: 					Dec 03, 2020          *      ****
* Project completion				Dec 07, 2020          *      *
* Reviewer:                         unknown        		 ***  *  *
******************************************************************************/
#pragma once
#include <vector>
//#include <future>
#include <thread>
#include <memory>
#include "bts_queue.hpp"
#include "function.hpp"
#include "semaphore.hpp"

/*
int main ()
{
	Threadpool t_pool(4);
	std::future<> task1 = Async(Function<int(void)> , low);
	std::future<> task2 = Async(Function<int(void)> , mid);
	std::future<> task3 = Async(Function<int(void)> , high);
	std::future<> task4 = Async(Function<int(void)> , low);

	return (0);
}
*/

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
		LOW = 0,
		MID,
		HIGH
	};
	explicit ThreadPool(size_t nofThreads = 1);
	~ThreadPool();

	// adds or removes available threads by delta
	void Tune(int delta);
	ThreadPool(const ThreadPool& other) = delete;
	ThreadPool& operator=(const ThreadPool& other) = delete;
	Future Async(Function<int(void)> func, Priority pri);

	class Future
	{
	public:
		explicit Future(std::shared_ptr<Task> task);
		void operator=(const Future &) = delete;
		void Wait();
	private:
		std::shared_ptr<Task> m_task;
	};

private:
	class Task
	{
	public:
		explicit Task(Function<int(void)> func, Priority pri);
		explicit Task() : m_sem(0){}
		int RunFunc();
		friend class Future;

		class Compare
		{
		public:
			bool operator()(const std::shared_ptr<Task> &lhs, const std::shared_ptr<Task> &rhs);
		};

	private:
		Function<int(void)> m_func;
		Priority m_pri;
		int m_retVal;
		Semaphore m_sem;
	};

	void ThreadFunc(int debugging);
	int WaitTask(int);

	int m_maxThreads;
	int m_activeThreads;
	Semaphore m_sem;
	std::vector<std::thread> m_pool;
	BTSQueue< std::shared_ptr<Task>, Task::Compare > m_tasks;
};
/*****************************************************************************/

} // namespace rd90
} // namespace ilrd