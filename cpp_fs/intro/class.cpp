#include <cstdio>

struct X
{
//public:
	explicit X(int a_);
	void Foo();

private:
	unsigned char m_a;
};

X::X(int a_): m_a(a_)
{

}

void X::Foo()
{
	printf("%d\n", m_a);
}

void Foo(const X &x_)
{
    //printf("%d\n", x_.m_a);
	X &x = const_cast<X&>(x_);
	x.Foo();
}

int main()
{
    X x1(4);

    x1.Foo();
    /*printf("%d\n", x1.m_a);*/
    Foo(x1);

    return 0;
}
