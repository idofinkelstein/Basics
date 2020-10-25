/* 

RSString class gives the user way to use strings as types and perfom operations on the objects of the class.

operations to be done on RSString object:
	- Default Ctor - a new string object
    - Ctor with string literal - creates an object initialized with string 
                                 literal
    - Cctor - copy constructor
    - Destructor

    - "+=" (add compound operator) - concatenate another RSString object to  
                                     the lvalue object
    - "[ ]" (direct access operator) - allows access to specific index in the 
                                       RSString object
    - "==" (comparison operator) - allows the comparison of two RSString objects, 
                                   as well as a RSString object to string literal

	- print using ostream object of std namespace - using the << operator 
      syntax.

Example:
void foo()
{
    RSString s1, s2("hello");
    
    s2[1] = 'j';
    
    s1 = "world";

    RSString s3 = s2+" "+s1;

    std::cout << s3 << std::endl; //"hello wjrld"

    s2[1] = 'w';
    std::cout << s2[1] << std::endl; //"w";

    std::cout << s2 << std::endl; //"helloworld";

    s2+=" "+s1;

    std::cout << s2 << std::endl; //"helloworld world";

    if("Hello" == s1)
        some code
    
    RSString s4("hello");

    RSString s5 = s4;
    std::cout << s5 << std::endl; //"hello";

    RSString s6;
    for(int i = 0 ; i<5 ; ++i)
    {
        s6[i] = i;
    }

}

*/

#pragma once



#include <iostream>     //ostream

/*---------------------------------------------------------------------------*/

namespace ilrd
{
namespace rd90
{

class RSString;
struct Buff;

bool operator==(const RSString& s1, const RSString& s2); 
bool operator<(const RSString& s1, const RSString& s2); 
bool operator>(const RSString& s1, const RSString& s2); 
std::ostream& operator<<(std::ostream& os, const RSString& s);

class RSString
{
public:
    /* non-explicit */RSString(const char* str = "");
    RSString(const RSString& other); //CCTOR
    RSString& operator=(const RSString &other);
    ~RSString();

    RSString& operator+=(const RSString& other);  

    char& operator[](size_t i);

	const char& operator[](size_t i) const;

    friend const RSString operator+(const RSString& s1,const RSString& s2);
    size_t Length() const;

private:
    Buff *buff;
	RSString(const char* str1, const char* str2);
    Buff *RSStringCreate(const char* str1, const char* str2 = "");
	void BuffCleanup();
	void BuffUpdate(const RSString& other);
};
                                                    
} // namespace rd90
} // namespace ilrd




