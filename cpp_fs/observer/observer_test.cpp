
#include <iostream>
#include <unistd.h>

#include "observer.hpp"

using namespace ilrd::rd90;

class MeteorlogicStation
{
public:
    void Wheather(){std::cout << "It's a nice and hot day today!" << std::endl;}
    
    void Subscribe(CallBack *cb)
    {
        m_disp.Subscribe(cb);
    }

    void UnSubscribe(CallBack *cb)
    {
        m_disp.UnSubscribe(cb);
    }

    void NotifyAll()
    {
        m_disp.Notify();
    }
private:
    Dispatcher m_disp;
};

class NewsApp
{
public:
    NewsApp(MeteorlogicStation *meteo)
     : m_meteo(meteo), 
       m_cb(Bind(&NewsApp::Update,this, 0)), 
       m_isNotified(false){}

    void Update(int temp){m_isNotified = true;}

    void Subscribe(MeteorlogicStation& ms);
    void UnSubscribe(MeteorlogicStation& ms);

    
    void BroadcastWheather()
    {
        if(m_isNotified == true)
        {
            m_meteo->Wheather();
            m_isNotified = false;
        }
    }
private:
    MeteorlogicStation *m_meteo;
    CallBack m_cb;
    bool m_isNotified;
};

void NewsApp::Subscribe(MeteorlogicStation &ms)
{
    ms.Subscribe(&m_cb);
}

void NewsApp::UnSubscribe(MeteorlogicStation &ms)
{
    ms.UnSubscribe(&m_cb);
}

int main()
{
    MeteorlogicStation MS;

    NewsApp NA(&MS);

    NA.Subscribe(MS);

    MS.NotifyAll();

    int i = 0;
    while(i++ < 5)
    {
        MS.NotifyAll();
        sleep(1);
        NA.BroadcastWheather();
    }

    NA.UnSubscribe(MS);

    return 0;
}