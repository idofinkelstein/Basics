#include <iostream>

int foo(void) { std::cout << "hi" << std::endl; return 0;}

void bar(int x)
{
	std::cout << "hi" << std::endl;
	++x;
}

float foobar(float f)
{
	std::cout << "hi" << std::endl;
	return (f + 33.2);
}
