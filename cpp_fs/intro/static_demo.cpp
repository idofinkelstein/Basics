#include <iostream>

class X
{
public:
    X(): m_id(++s_cntr) {}
    int GetId()
    {
        std::cout << m_id << std::endl;
        return m_id;
    }
    static int getid(X &x);

private:
    int m_id;
    static int s_cntr;

};

int X::getid(X &x)
{
    return ++x.m_id;
}

int X::s_cntr = 0;

int main()
{
    X x1, x2;

    X::getid(x1);
    x1.GetId();
    x2.GetId();

    return 0;
}

