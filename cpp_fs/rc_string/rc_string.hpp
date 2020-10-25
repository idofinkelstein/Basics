/* 

RCString class gives the user way to use strings as types and perfom operations on the objects of the class.

operations to be done on RCString object:
	- Default Ctor - a new string object
    - Ctor with string literal - creates an object initialized with string 
                                 literal
    - Cctor - copy constructor
    - Destructor

    - "+=" (add compound operator) - concatenate another RCString object to  
                                     the lvalue object
    - "[ ]" (direct access operator) - allows access to specific index in the 
                                       RCString object
    - "==" (comparison operator) - allows the comparison of two RCString objects, 
                                   as well as a RCString object to string literal

	- print using ostream object of std namespace - using the << operator 
      syntax.

Example:
void foo()
{
    RCString s1, s2("hello");
    
    s2[1] = 'j';
    
    s1 = "world";

    RCString s3 = s2+" "+s1;

    std::cout << s3 << std::endl; //"hello wjrld"

    s2[1] = 'w';
    std::cout << s2[1] << std::endl; //"w";

    std::cout << s2 << std::endl; //"helloworld";

    s2+=" "+s1;

    std::cout << s2 << std::endl; //"helloworld world";

    if("Hello" == s1)
        some code
    
    RCString s4("hello");

    RCString s5 = s4;
    std::cout << s5 << std::endl; //"hello";

    RCString s6;
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

class RCString;
struct Buff;

bool operator==(const RCString& s1, const RCString& s2); 
bool operator<(const RCString& s1, const RCString& s2); 
bool operator>(const RCString& s1, const RCString& s2); 
std::ostream& operator<<(std::ostream& os, const RCString& s);

class RCString
{
public:
    /* non-explicit */RCString(const char* str = "");
    RCString(const RCString& other); //CCTOR
    RCString& operator=(const RCString &other);
    ~RCString();

    RCString& operator+=(const RCString& other);  

    char& operator[](size_t i);

	const char& operator[](size_t i) const;

    friend const RCString operator+(const RCString& s1,const RCString& s2);
    size_t Length() const;

private:
    Buff *buff;
	RCString(const char* str1, const char* str2);
    Buff *RCStringCreate(const char* str1, const char* str2 = "");
	void BuffCleanup();
	void BuffUpdate(const RCString& other);
};
                                                    
} // namespace rd90
} // namespace ilrd




