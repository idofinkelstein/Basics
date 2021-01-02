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

    TimerWheel(T *alarm);
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
        Task() = default;
        class CompareTasks
        {
        public:
            bool operator()(const std::shared_ptr<Task>& task1,
                            const std::shared_ptr<Task>& task2);
            // compare expiration times of tasks
        };

    private:
        bool m_isTaskCancelled;
        Function<void(void)> m_alarmFunc;
        TimerId m_id;
        TimePoint m_expTime;
    };
    using TaskPtr = std::shared_ptr<Task>;
    void OnTimerEvent();
    
    std::shared_ptr<T>                                  m_alarm;
    std::priority_queue<TaskPtr, 
                        std::vector<TaskPtr>, 
                        typename Task::CompareTasks>
                                                        taskQueue;
    std::unordered_map<TimerId, std::shared_ptr<Task> > tasksMap;

};

/*---------------------------------------------------------------------------*/

template<class T> 
TimerWheel<T>::TimerWheel(T *alarm)
: m_alarm(alarm)
{
    //...
    //(*m_alarm)->RegisterOnEvent(OnTimerEvent);
    //...
}

template<class T> 
TimerWheel<T>::~TimerWheel()
{

}


template<class T>
TimerWheel<T>::TimerId TimerWheel<T>::SetAlarm(Duration timeout,
                                               Function<void(void)> func)
{

}                 


template<class T>
void TimerWheel<T>::CancelAlarm(TimerWheel<T>::TimerId uid)
{

}

template<class T>
void TimerWheel<T>::OnTimerEvent()
{

}



} // rd90
} // ilrd
