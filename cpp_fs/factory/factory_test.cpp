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
    explicit Derived1(int a){std::cout << "a = " << a << std::endl;}
    void Foo()
    {
        std::cout << "Derived1::Foo" << std::endl;
    }
};

class Derived2 : public Base
{
public:
    explicit Derived2(int a){std::cout << "a = " << a << std::endl;}
    void Foo()
    {
        std::cout << "Derived2::Foo" << std::endl;
    }
};

int main()
{
    Factory<Base, int, int> factory;

    factory.Register<Derived1>(1);
    factory.Register<Derived2>(2);

    // Base *d1 = factory.Create(1, 20); // compile time error
    // Base *d2 = factory.Create(2, 14); // compile time error

    std::shared_ptr<Base> sd1(factory.Create(1, 7));
    std::shared_ptr<Base> sd2(factory.Create(2, 8));


    sd1->Foo();
    sd2->Foo();

}