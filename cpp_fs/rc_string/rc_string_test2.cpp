#include <string.h>

#include "rc_string.hpp"

using namespace ilrd::rd90;

int main()
{
    RCString str1;//
    RCString str2("ffffff");
    RCString str3(str2);
    RCString str4;//
    const RCString str5("hello");
    char c = str5[3];
    RCString str7 = str5;
    RCString str8;

    //str5[4] = 'R'; 
    str4 = str2;
    //str2 += str4;
    str1 = str2 + str3;//

    str1[4] = c;
<<<<<<< HEAD
	c = str5[4];
=======
	c = str3[1];
>>>>>>> facb48c762dae9653274db9d8c1b12ccaff895ca
	//str1[20] = c;
    str2 = str2;
    str2[0] = 'z';//
    str2[1] = 'Z';
        
    std::cout << "str1 len = " << str1.Length() << std::endl <<
                       "str2 len = " << str2.Length() << std::endl <<
                       "str3 len = " << str3.Length() << std::endl <<
                       "str4 len = " << str4.Length() << std::endl;

    std::cout << "str1 = " << str1 << std::endl <<
                       "str2 = " << str2 << std::endl <<
                       "str3 = " << str3 << std::endl <<
                       "str4 = " << str4 << std::endl <<
                       "str5 = " << str5 << std::endl;
    str1 = str1;

	std::cout << " c = " << c << std::endl;

    if (str2 > str5)
    {
        std::cout << "str2 > str5" << std::endl;
    }
    else if (str2 < str5)
    {
        std::cout << "str2 < str5" << std::endl;
    }
    else if(str2 == str5)
    {
        std::cout << "str2 == str5" << std::endl;
    }

    return 0;
}
