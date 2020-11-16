#include "singleton.hpp"

using namespace ilrd::rd90;

class A
{
public:
    template<typename T>
    friend class ilrd::rd90::Singleton;

    void Foo() {}
private:
    A(){}
};

void Foo();
void *Action(void *arg);

int main()
{
    pthread_t tid[4];

    for (int i = 0; i < 4; ++i)
    {
        pthread_create(&tid[i], NULL, Action, NULL);
    }

    for (int i = 0; i < 4; ++i)
    {
        pthread_join(tid[i], NULL);
    }

    Singleton<A> instance;
    Singleton<A> instance2;

    instance->Foo();
    instance2->Foo();
    Foo();
    instance2.GetCount();
    return 0;
}


void Foo()
{
    Singleton<A> instance;

    instance->Foo();
}

void *Action(void *arg)
{
    (void)arg;

    Singleton<A> instance;

    instance->Foo();
    Foo();

    return (NULL);
}