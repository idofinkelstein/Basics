#include <iostream>

int Sum(int x = 5, int = 7, float f = 54.4);

void f(int x);
void f(int x = 5)
{
	++x;
}

int main()
{
	int i;

	std::cin >> i ;

	std::cout << "hello world!" << std::endl << i << std::endl;
	std::cerr << "hello world!" << std::endl << i << std::endl;

	Sum();
	f();
	Sum(1);

	Sum(1,2);

	Sum(1,2,3.3);

	return 0;
}

int Sum(int x, int y, float f)
{
	return (x + y - static_cast<int>(f));
}
