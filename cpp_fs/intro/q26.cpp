#if 0
#include<iostream>
using namespace std;
using namespace X;
class X;

int operator+(const X& x1_, const X& x2_)
{
    return 7;
}

//ostream& operator<<(ostream& os_, const X& x_);

class X
{
public:
    bool operator==(const X& o_) const { return m_a == o_.m_a; }
    ostream& operator<<(ostream& os_);

private:
    int m_a;
};

int main()
{
    X x1;
    X x2;

    cout<< " x1+x2:" << x1 + x2 <<
           " x1==x2:" << (x1 == x2) <<
           " x1:" << x1 <<
           " x2:" << x2 << endl;

    return 0;
}

ostream &X::operator<<(ostream& os_)
{
    return os_ << m_a;
}
#endif
#include<iostream>
using namespace std;

class X;

int operator+(const X& x1_, const X& x2_)
{
	(void)x1_, (void)x2_;
    return 7;
}

ostream& operator<<(ostream& os_, const X& x_);

class X
{
public:
    bool operator==(const X& o_) const { return m_a == o_.m_a; }
    friend ostream& operator<<(ostream& os_, const X& x_);

private:
    int m_a;
};

int main()
{
    X x1;
    X x2;

    cout << " x1+x2:" << x1 + x2 <<
           " x1==x2:" << (x1 == x2) <<
           " x1:" << x1 <<
           " x2:" << x2 << endl;

    return 0;
}

ostream & operator<<(ostream& os_, const X& x_)
{
    return os_ << x_.m_a;
}
