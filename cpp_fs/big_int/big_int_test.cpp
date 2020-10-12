#include <iostream>

#include "bigint.hpp"
using namespace ilrd::rd90;

int main()
{
    Bigint num1, num2(455);
    int a = 0, b = 455;
    Bigint num3(-1000000), num4(2000000);
    Bigint x(-2000000000);
    Bigint y(-1500000000);
    long X = -2000000000;
    long Y = -1500000000;

    std::cout << "testing '=' operator:" << std::endl;
    num1 = num2;
    a = b;
    std::cout << "num1 = num2 = "<< num1 << " = " << num2 << std::endl;
    std::cout << "a = b = "<< a << " = " << b << std::endl;

    std::cout << "testing '+=' operator:" << std::endl;
    num2 += num1+= num1;
    b += a += a;
    std::cout << "num1 = " << num1 << std::endl;
    std::cout << "num2 = " << num2 << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    std::cout << "testing '+' operator:" << std::endl;
    std::cout << std::hex  << std::uppercase << "0x" << num3+ num4 << std::endl;

    std::cout  << std::hex                      << 
                        std::uppercase           <<
                        "0x"                            << 
                        -1000000 + 2000000 << 
                        std::endl;

    std::cout << std::hex << std::uppercase << "0x" << x + y << std::endl;
    std::cout << std::hex << std::uppercase << "0x" << X + Y << std::endl;


	return 0;


}
