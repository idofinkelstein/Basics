#include <iostream>

void Foo(const double &d);
void Bar(double &d);

int main()
{
	int x = 5;
	int y = 6;

	Foo(x); // implicit cast to const double&
	Bar(reinterpret_cast<double&>(y));

	std::cout << y << std::endl;

	return 0;
}

void Foo(const double &d)
{
	std::cout << "Foo:" << std::endl;
	std::cout << d << std::endl;
	std::cout << &d << std::endl;

}
void Bar(double &d)
{
	std::cout << "Bar:" << std::endl;
	std::cout << d << std::endl;
	std::cout << &d << std::endl;
}
