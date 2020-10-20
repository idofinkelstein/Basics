#include <iostream>


class X
{
public:
    explicit X();
     X(int a_);
     X(int a_, int b_);

    operator int() const;
    void Print() const;

private:
    int m_a;
};

X::X() : m_a(0){}
X::X(int a_): m_a(a_){}
X::X(int a_, int b_): m_a(a_ + b_){}

X::operator int() const
{
    return(m_a);
}

void X::Print() const
{
    std::cout << "X::Print()" << m_a << '\n';
}

void Fifi(X x_)
{
    std::cout << "Fifi()"<< x_ << '\n';
    x_.Print();
}

int main()
{
    X x1(7);

    Fifi(x1);
    Fifi(X(7));
    // Fifi(9);
     Fifi(X(3,4));

    return x1 * 3;
}
