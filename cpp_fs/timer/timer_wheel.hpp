/******************************************************************************
* Project name:					 	timer wheel                     
* Developer: 						Ido Finkelstein        
* Project Lauch: 					Dec 30, 2020          
* Project completion				Jan 03, 2021          
* Reviewer:                                              
******************************************************************************/

#pragma once

#include "alarm.hpp"

namespace ilrd
{
namespace rd90
{

template <typename T>
class TimerWheel
{
private:
    class Task; //forward declaration for using TaskPtr;
public:
    using AlarmId = uint32_t;
    using SysClock = std::chrono::system_clock;
    using TimePoint = std::chrono::time_point<SysClock>;
    using Duration = std::chrono::duration<double>;
    using TaskPtr = std::shared_ptr<Task>;

    explicit TimerWheel(T *alarm);
    ~TimerWheel();
    
    /* UNCOPYABLE */
    TimerWheel(const TimerWheel& other) = delete; 
    TimerWheel& operator=(const TimerWheel& other) = delete;

    AlarmId SetAlarm(std::chrono::nanoseconds timeout,
                     Function<void(void)> func);

    void    CancelAlarm(AlarmId uid);

private:
    class Task
    {
    public:
        Task(const TimePoint& timeout, const Function<void(void)>& func, AlarmId id);

        class CompareTasks
        {
        public:
            // compares expiration time of tasks
            bool operator()(const TaskPtr& task1,
                            const TaskPtr& task2);
           
        };

        TimePoint&  GetExp();
        AlarmId     GetID();
        void        PerformTask();
        void        Cancel();
        bool        IsCanceled();

    private:
        bool                 m_isTaskCancelled;
        Function<void(void)> m_alarmFunc;
        AlarmId              m_id;
        TimePoint            m_expTime;
    };
    
    void OnAlarmEvent(int);
    
    std::shared_ptr<T>                                  m_alarm;
    std::priority_queue<TaskPtr, 
                        std::vector<TaskPtr>, 
                        typename Task::CompareTasks>    m_taskQueue;
                                                        
    std::unordered_map<AlarmId, TaskPtr >               m_tasksMap;

};

/*-------------------Class TimerWheel definition------------------------------*/

template<typename T> 
TimerWheel<T>::TimerWheel(T *alarm)
: m_alarm(alarm)
{
    m_alarm->T::RegisterOnEvent(Bind(&TimerWheel::OnAlarmEvent, this, 0));
}
/*---------------------------------------------------------------------------*/
template<typename T> 
TimerWheel<T>::~TimerWheel() {}
/*---------------------------------------------------------------------------*/
template<typename T>
typename
TimerWheel<T>::AlarmId TimerWheel<T>::SetAlarm(std::chrono::nanoseconds timeout,
                                               Function<void(void)> func)
{
    static AlarmId alarmUID = 0;

    TimePoint timeNow = SysClock::now();
    TimePoint absTime = timeout + timeNow;

    TaskPtr task(new Task(absTime, func, alarmUID));

    m_tasksMap[alarmUID] = task;
    m_taskQueue.push(task);

    if (m_taskQueue.top()->GetExp() == absTime)
    {
        auto nextTime = m_taskQueue.top()->GetExp() - timeNow;
        m_alarm->T::Arm(nextTime);
    }

    return (alarmUID++);
}                 
/*---------------------------------------------------------------------------*/

template<typename T>
void TimerWheel<T>::CancelAlarm(TimerWheel<T>::AlarmId uid)
{
    m_tasksMap[uid]->Cancel();
}
/*---------------------------------------------------------------------------*/
template<typename T> 
void TimerWheel<T>::OnAlarmEvent(int Void)
{
    (void)Void;

    TaskPtr task = m_taskQueue.top();
    m_taskQueue.pop();

    if (!task->IsCanceled())
    {
        task->PerformTask();
        m_tasksMap.erase(task->GetID());
    }

    task = m_taskQueue.top();

    while (task->IsCanceled())
    {
        m_taskQueue.pop();
        task = m_taskQueue.top();
    }

    if (!m_taskQueue.empty())
    {
        // set the timer for next time exp
        auto nextTime = m_taskQueue.top()->GetExp() - SysClock::now();

        m_alarm->T::Arm(nextTime);
    }  
}

/*-------------------Class TimerWheel::Task definition------------------------*/

template<typename T>  
TimerWheel<T>::Task::Task(const TimePoint &timeout, const Function<void(void)> &func, AlarmId id)
: m_isTaskCancelled(false), m_alarmFunc(func),m_id(id), m_expTime(timeout) {}
/*---------------------------------------------------------------------------*/

template<typename T>
typename TimerWheel<T>::TimePoint& TimerWheel<T>::Task::GetExp()
{
    return m_expTime;
}

/*---------------------------------------------------------------------------*/
template<typename T> 
void TimerWheel<T>::Task::Cancel()
{
    m_isTaskCancelled = true;
}
/*---------------------------------------------------------------------------*/
template<typename T> bool 
TimerWheel<T>::Task::IsCanceled()
{
    return m_isTaskCancelled;
}
/*---------------------------------------------------------------------------*/
template<typename T> 
typename TimerWheel<T>::AlarmId TimerWheel<T>::Task::GetID()
{
    return m_id;
}
/*---------------------------------------------------------------------------*/
template<typename T> 
void TimerWheel<T>::Task::PerformTask()
{
    m_alarmFunc();
}

/*-------------Class TimerWheel::Task::CompareTasks definition---------------*/
template<typename T> 
bool TimerWheel<T>::Task::CompareTasks::operator()(const TaskPtr &task1, 
                                                   const TaskPtr &task2)
{
    return task1->GetExp() > task2->GetExp();
}

} // rd90
} // ilrd
