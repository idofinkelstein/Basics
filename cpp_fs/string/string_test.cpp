#include <string.h>

#include "string.hpp"

using namespace ilrd::rd90;

int main()
{
    String str1;
    String str2("ffffff");
    String str3(str2);
    String str4;
    const String str5("hello");
    char c = str5[3];
    String str7 = str5;

    //str5[4] = 'R'; 
    str4 = str2;
    str2 += str4;
    str1 = str2 + str3;

    str1[4] = 'A';
        
    std::cout << "str1 len = " << str1.Length() << std::endl <<
                       "str2 len = " << str2.Length() << std::endl <<
                       "str3 len = " << str3.Length() << std::endl <<
                       "str4 len = " << str4.Length() << std::endl;

    std::cout << "str1 = " << str1 << std::endl <<
                       "str2 = " << str2 << std::endl <<
                       "str3 = " << str3 << std::endl <<
                       "str4 = " << str4 << std::endl;

    return 0;
}