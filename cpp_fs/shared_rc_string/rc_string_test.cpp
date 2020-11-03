#include <cstdlib>
#include <iostream>

#include "rc_string.hpp"

using namespace ilrd::rd90;

int main()
{
	RCString s1("hefdyhdfllo"), s2 = "fdsg";
	RCString s3(s1);
	RCString s4(RCString("asdf"));
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
