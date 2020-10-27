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

bool operator==(const RCString& s1, const RCString& s2); 
bool operator<(const RCString& s1, const RCString& s2); 
bool operator>(const RCString& s1, const RCString& s2); 
std::ostream& operator<<(std::ostream& os, const RCString& s);

class RCString
{
private:
    class Proxy;
    friend class Proxy;
	class StringData;
public:
<<<<<<< HEAD
=======
    class Proxy;
    friend class Proxy;
>>>>>>> 4a9ab5dd4c40f10db7b17f51b296ffc35be6487d

    /* non-explicit */RCString(const char* str = "");
    RCString(const RCString& other); //CCTOR
    RCString& operator=(const RCString &other);
    ~RCString();

    RCString& operator+=(const RCString& other);  

<<<<<<< HEAD
    Proxy operator[](size_t i);
=======
    Proxy& operator[](size_t i);
>>>>>>> 4a9ab5dd4c40f10db7b17f51b296ffc35be6487d

	const Proxy& operator[](size_t i) const;

    friend const RCString operator+(const RCString& s1,const RCString& s2);
    size_t Length() const;

private:
    StringData *m_str;

	RCString(const char* str1, const char* str2);
	void StringDataCleanup();
	void StringDataUpdate(const RCString& other);
};

class RCString::StringData
{
public:
	size_t counter;
	char str[1];

    static StringData *Create(const char* str1 = "", const char* str2 = "");

private:
	explicit StringData(const char *lhs, const char *rhs, size_t lhLen, size_t rhLen);
};

class RCString::Proxy 
{

public:
<<<<<<< HEAD
    Proxy(RCString& str, size_t index);

    char operator=(const Proxy& rhs); // lvalue
    char operator=(char c);
    // uses
    operator char() const;
private:
    RCString* m_str;
    int m_i;
=======
    Proxy(RCString& str, int index);

    Proxy& operator=(const Proxy& rhs); // lvalue
    Proxy& operator=(char c);
    // uses
    operator char() const;
private:
    RCString& str;
    int charIndex;
>>>>>>> 4a9ab5dd4c40f10db7b17f51b296ffc35be6487d

};
                                                 
} // namespace rd90
} // namespace ilrd




