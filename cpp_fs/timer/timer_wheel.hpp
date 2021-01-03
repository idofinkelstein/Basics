#pragma once

#include "alarm.hpp"

namespace ilrd
{
namespace rd90
{


template <typename T>
class TimerWheel
{
public:
    using TimerId = uint32_t;
    using SysClock = std::chrono::system_clock;
    using TimePoint = std::chrono::time_point<SysClock>;
    using Duration = std::chrono::duration<double>;

    explicit TimerWheel(T *alarm);
    ~TimerWheel();
    
    TimerWheel(const TimerWheel& other) = delete; /* UNCOPYABLE */
    TimerWheel& operator=(const TimerWheel& other) = delete;

    TimerId SetAlarm(Duration timeout,
                     Function<void(void)> func);
    void    CancelAlarm(TimerId uid);

private:
    class Task
    {
    public:
        Task(const TimePoint& timeout, const Function<void(void)>& func);
        class CompareTasks
        {
        public:
            bool operator()(const std::shared_ptr<Task>& task1,
                            const std::shared_ptr<Task>& task2);
            // compare expiration times of tasks
        };
        TimePoint &GetExp();

    private:
        bool                 m_isTaskCancelled;
        Function<void(void)> m_alarmFunc;
        TimerId              m_id;
        TimePoint            m_expTime;
    };
    using TaskPtr = std::shared_ptr<Task>;
    void OnTimerEvent();
    
    std::shared_ptr<T>                                  m_alarm;
    std::priority_queue<TaskPtr, 
                        std::vector<TaskPtr>, 
                        typename Task::CompareTasks>
                                                        m_taskQueue;
    std::unordered_map<TimerId, std::shared_ptr<Task> > m_tasksMap;

};

/*---------------------------------------------------------------------------*/

template<typename T> 
TimerWheel<T>::TimerWheel(T *alarm)
: m_alarm(alarm)
{
    m_alarm->T::RegisterOnEvent(Bind(TimerWheel::OnTimerEvent, this, 0));
}

template<typename T> 
TimerWheel<T>::~TimerWheel()
{

}


template<typename T>
typename
TimerWheel<T>::TimerId TimerWheel<T>::SetAlarm(Duration timeout,
                                               Function<void(void)> func)
{
    static TimerId alarmUID = 0;

    TimePoint timeNow = SysClock::now();
    TimePoint absTime = timeout + timeNow;

    std::shared_ptr<Task> task(new Task(timeout, func));

    m_tasksMap[alarmUID] = task;
    m_taskQueue.push(task);
}                 


template<typename T>
void TimerWheel<T>::CancelAlarm(TimerWheel<T>::TimerId uid)
{

}

template<typename T>
void TimerWheel<T>::OnTimerEvent()
{

}


/*---------------------------------------------------------------------------*/

template<class T> 
TimerWheel<T>::Task::Task(const TimePoint &timeout, const Function<void ()> &func)
: m_alarmFunc(func), m_expTime(timeout), m_isTaskCancelled(0)
{

}


template<typename T>
typename TimerWheel<T>::TimePoint& TimerWheel<T>::Task::GetExp()
{
    return m_expTime;
}


template<typename T> 
bool TimerWheel<T>::Task::CompareTasks::operator()(const std::shared_ptr<TimerWheel<T>::Task> &task1, 
const std::shared_ptr<TimerWheel<T>::Task> &task2)
{
    return task1->GetExp() > task2->GetExp();
}



} // rd90
} // ilrd
