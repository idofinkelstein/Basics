/******************************************************************************
* Project name:					 	threadpool           ***     *******
* Developer: 						Ido Finkelstein       *      *
* Project Launch: 					Dec 03, 2020          *      ****
* Project completion				Dec 07, 2020          *      *
* Reviewer:                         Janna torbilo        ***  *  *
******************************************************************************/
/**********************   PREPROCESSOR DIRECTIVES   **************************/
#pragma once
#include <vector>
//#include <future>
#include <thread>
#include <memory>
#include "bts_queue.hpp"
#include "function.hpp"

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
public:
	enum Priority
	{
		LOW = 0,
		MID,
		HIGH
	};
	explicit ThreadPool(size_t nofThreads = 1);
	~ThreadPool();

	void SetActiveThreads(size_t nofThreads);

	ThreadPool(const ThreadPool& other) = delete;
	ThreadPool& operator=(const ThreadPool& other) = delete;

	void Async(Function<int(void)> func, Priority pri);

private:
	class Task
	{
	public:
		explicit Task(Function<int(void)> func, Priority pri);
		explicit Task(){}
		int RunFunc();
	private:
		Function<int(void)> m_func;
		Priority m_pri;
	};

	//מטמפלטים את התור למצביע חכם של משימות
	void ThreadFunc(int debugging);

	size_t m_nOfThreads;
	size_t m_activeThreads;
	std::vector<std::thread> m_pool;
	BTSQueue< std::shared_ptr<Task> > m_tasks;
};
/*****************************************************************************/

} // namespace rd90
} // namespace ilrd