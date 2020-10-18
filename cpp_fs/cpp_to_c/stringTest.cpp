#include <iostream>

#include "string.hpp"


using namespace ilrd;

void foo(String s);
String bar(const char* arg);


int main()
{
    std::cout << "Line " << __LINE__ << std::endl;
    String s1("Hello");

    std::cout << "Line " << __LINE__ << std::endl;
    String s2(s1);

    std::cout << "Line " << __LINE__ << std::endl;
    String s3 = "Shalom";

    std::cout << "Line " << __LINE__ << std::endl;
    String* s4 = new String;

    std::cout << "Line " << __LINE__ << std::endl;
    *s4 = s3;

    std::cout << "Line " << __LINE__ << std::endl;
    if (s3 == "Shalom") {}

    std::cout << "Line " << __LINE__ << std::endl;
    char c = s3[3];

    std::cout << "Line " << __LINE__ << std::endl;
    foo(s3);

    std::cout << "Line " << __LINE__ << std::endl;
    foo("RD90 are champions");

    std::cout << "Line " << __LINE__ << std::endl;
    c = bar("We love C++")[9];

    std::cout << "Line " << __LINE__ << std::endl;
    delete s4;

    std::cout << "Line " << __LINE__ << std::endl;
    return c;
}

void foo(String s)
{
    std::cout << "Line " << __LINE__ << std::endl;
    std::cout << "foo got the arg:\n" << &s[0] << std::endl;
}

String bar(const char* arg)
{
    String s1 = String(arg) + "Really?";
    return s1;
}
