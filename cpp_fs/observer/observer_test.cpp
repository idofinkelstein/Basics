
#include <iostream>
#include "observer.hpp"

using namespace ilrd::rd90;

class MeteorlogicStation
{
public:
    void Wheather(){std::cout << "It's a nice and hot day today!" << std::endl;}
    void Subscribe(CallBack *cb)
    {
        disp.Subscribe(cb);
    }
    void NotifyAll()
    {
        disp.Notify();
    }
private:
    Dispatcher disp;
};

class NewsApp
{
public:
    NewsApp(MeteorlogicStation *meteo) : m_meteo(meteo), m_cb(Bind(&NewsApp::Update,this, 0)){}
    void Update(int temp){}
    void Subscribe(MeteorlogicStation& ms);
    
    void BroadcastWheather()
    {
        m_meteo->Wheather();
    }
private:
    MeteorlogicStation *m_meteo;
    CallBack m_cb;
};

void NewsApp::Subscribe(MeteorlogicStation &ms)
{
    ms.Subscribe(&m_cb);
}


int main()
{
    MeteorlogicStation MS;

    NewsApp NA(&MS);

    NA.Subscribe(MS);

    return 0;
}