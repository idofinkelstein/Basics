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
    using AlarmId = uint32_t;
    using SysClock = std::chrono::system_clock;
    using TimePoint = std::chrono::time_point<SysClock>;
    using Duration = std::chrono::duration<double>;

    explicit TimerWheel(T *alarm);
    ~TimerWheel();
    
    TimerWheel(const TimerWheel& other) = delete; /* UNCOPYABLE */
    TimerWheel& operator=(const TimerWheel& other) = delete;

    AlarmId SetAlarm(Duration timeout,
                     Function<void(void)> func);
    void    CancelAlarm(AlarmId uid);

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
        void Cancel();
        bool IsCanceled();
        void PerformTask();
        AlarmId GetID();

    private:
        bool                 m_isTaskCancelled;
        Function<void(void)> m_alarmFunc;
        AlarmId              m_id;
        TimePoint            m_expTime;
    };
    using TaskPtr = std::shared_ptr<Task>;
    void OnAlarmEvent(int);
    
    std::shared_ptr<T>                                  m_alarm;
    std::priority_queue<TaskPtr, 
                        std::vector<TaskPtr>, 
                        typename Task::CompareTasks>
                                                        m_taskQueue;
    std::unordered_map<AlarmId, std::shared_ptr<Task> > m_tasksMap;

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
TimerWheel<T>::AlarmId TimerWheel<T>::SetAlarm(Duration timeout,
                                               Function<void(void)> func)
{
    static AlarmId alarmUID = 0;

    TimePoint timeNow = SysClock::now();
    TimePoint absTime = timeout + timeNow;

    std::shared_ptr<Task> task(new Task(absTime, func));

    m_tasksMap[alarmUID] = task;
    m_taskQueue.push(task);

    if (m_taskQueue.top()->GetExp == absTime)
    {
        auto nextTime = m_taskQueue.top()->GetExp() - timeNow;
        m_alarm->T::Arm(nextTime);
    }

    return (alarmUID++);
}                 


template<typename T>
void TimerWheel<T>::CancelAlarm(TimerWheel<T>::AlarmId uid)
{
    m_tasksMap[uid]->Cancel();
}

template<class T> void 
TimerWheel<T>::OnAlarmEvent(int Void)
{
    (void)Void;

    TaskPtr task = m_taskQueue.top();
    m_taskQueue.pop();

    if (!task->IsCanceled())
    {
        task->PerformTask()();
        m_tasksMap.erase(task.GetID());
    }

    while (task->IsCancelled())
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

template<class T> 
void TimerWheel<T>::Task::Cancel()
{
    m_isTaskCancelled = 1;
}

template<class T> bool 
TimerWheel<T>::Task::IsCanceled()
{
    return m_isTaskCancelled;
}

template<class T> 
typename TimerWheel<T>::AlarmId TimerWheel<T>::Task::GetID()
{
    return m_id;
}

template<class T> 
void TimerWheel<T>::Task::PerformTask()
{
    m_alarmFunc();
}


} // rd90
} // ilrd
