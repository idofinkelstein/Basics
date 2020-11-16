#include "singleton.hpp"

class A
{
public:
    void Foo() {}
};

int main()
{
    Singleton<A> instance;

    instance->Foo();


    return 0;
}
