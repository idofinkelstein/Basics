#include <iostream> // cout
#include <memory> // shared pointer

#include "factory.hpp" // class Factory

using namespace ilrd::rd90;

class Base
{
public:
    virtual void Foo() = 0;
    virtual ~Base() = default;
};
class Derived1 : public Base
{
public:
    void Foo()
    {
        std::cout << "Derived1::Foo" << std::endl;
    }
};

class Derived2 : public Base
{
public:
    void Foo()
    {
        std::cout << "Derived2::Foo" << std::endl;
    }
};

int main()
{
    Factory<Base, int> factory;

    factory.Register<Derived1>(1);
    factory.Register<Derived2>(2);

    Base *d1 = factory.Create(1);
    Base *d2 = factory.Create(2);

    std::shared_ptr<Base> sd1(factory.Create(1));
    std::shared_ptr<Base> sd2(factory.Create(2));

    d1->Foo();
    d2->Foo();

    sd1->Foo();
    sd2->Foo();

    delete d1;
    delete d2;

}