#include <iostream> /* cout */

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

    x += x;
#if 1
    std::cout << "testing '=' operator:" << std::endl;
    num1 = num2;
    a = b;

    std::cout << "num1 = num2 = 0x"<<
                        std::uppercase <<
                        num1 <<
                         " = 0x" <<
                        num2 <<
                        std::endl;

    std::cout << "a = b = " << std::uppercase << "0x"<< a << " = " << b << std::endl;

    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "testing '+' operator:" << std::endl;
    std::cout << std::uppercase << "0x" << num3+ num4 << std::endl;

    std::cout  << std::hex                      << 
                        std::uppercase           <<
                        "0x"                            << 
                        -1000000 + 2000000 << 
                        std::endl;

    std::cout << std::uppercase << "x + y = " << "0x" << x + y << std::endl;

    std::cout <<  "X + Y = " << 
                        std::hex << 
                        std::uppercase <<
                        "0x" << 
                        X + Y << 
                        std::endl;

    std::cout << "x + x + x + x = " << 
                        std::uppercase <<
                        "0x" << 
                        x + x + x + x <<
                        std::endl;

    std::cout << "X + X + X + X = " <<
                        std::hex <<
                        std::uppercase <<
                        "0x" <<
                        X + X + X + X <<
                        std::endl;

    std::cout << "--------------------------------------------------------" << std::endl;

    std::cout << "testing '+=' operator:" << std::endl;
    num2 += num1+= num1;
    b += a += a;
    std::cout << "num1 = " << num1 << std::endl;
    std::cout << "num2 = " << num2 << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    X += X += X += X += X += X += X;
    x += x += x += x += x += x += x;

    std::cout << "test X += X += X += X += X += X += X; and" 
                        "x += x += x += x += x += x += x;" <<
                        std::endl;

    std::cout << "X = 0x" << X << std::endl;
    std::cout << "x = 0x" << x << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    x + 3;
    3 + x;
    5 + a + b + 4 + x;

#endif
	return 0;


}
