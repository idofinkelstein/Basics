#include <cstdlib>
#include <iostream>

#include "rs_string.hpp"

using namespace ilrd::rd90;

int main()
{
	RSString s1("hefdyhdfllo"), s2 = "fdsg";
	RSString s3(s1);
	RSString s4(RSString("asdf"));
	char c;
	

	s3 = s4;
	s4 = s4;
	c = s3[0];

	s1 + s2;

	std::cout << c << std::endl;
	std::cout << s1 + s2 << std::endl;
	std::cout << (s1 + s2).Length() << std::endl;
	return  0;
}
