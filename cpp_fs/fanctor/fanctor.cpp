#include <functional>
#include <iostream>

class Gadget
{
public:
    explicit Gadget(int n = 5) : m_n(n){}
    friend int Foo(std::string str, const Gadget &g);
private:
    int m_n;
};



int Foo(std::string str, const Gadget &g)
{
    std::cout << str << std::endl;

    return 1 + g.m_n;
}

int main()
{
    Gadget g1;

    std::function< int(std::string, const Gadget &)> f1 = Foo;

    f1("this is functor", g1);

    
}
