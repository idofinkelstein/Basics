/* 

String class gives the user way to use strings as types and perfom operations on the objects of the class.

operations to be done on String object:
	- Default Ctor - a new string object
    - Ctor with string literal - creates an object initialized with string 
                                 literal
    - Cctor - copy constructor
    - Destructor

    - "+=" (add compound operator) - concatenate another String object to  
                                     the lvalue object
    - "[ ]" (direct access operator) - allows access to specific index in the 
                                       String object
    - "==" (comparison operator) - allows the comparison of two String objects, 
                                   as well as a String object to string literal

	- print using ostream object of std namespace - using the << operator 
      syntax.

Example:
void foo()
{
    String s1, s2("hello");
    
    s2[1] = 'j';
    
    s1 = "world";

    String s3 = s2+" "+s1;

    std::cout << s3 << std::endl; //"hello wjrld"

    s2[1] = 'w';
    std::cout << s2[1] << std::endl; //"w";

    std::cout << s2 << std::endl; //"helloworld";

    s2+=" "+s1;

    std::cout << s2 << std::endl; //"helloworld world";

    if("Hello" == s1)
        some code
    
    String s4("hello");

    String s5 = s4;
    std::cout << s5 << std::endl; //"hello";

    String s6;
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

class String;
bool operator==(const String& s1, const String& s2); // "hello" == s1 OR s1 == "hello"
bool operator<(const String& s1, const String& s2); // "hello" == s1 OR 
bool operator>(const String& s1, const String& s2); // "hello" == s1 OR 
std::ostream& operator<<(std::ostream& os, const String& s);

class String
{
public:
    /* non-explicit */String(const char* str = "");
    String(const String& other); //CCTOR
    String& operator=(const String& other);
    ~String();

    String& operator+=(const String& other);  

    char& operator[](size_t i);

    /*1.*/ const char& operator[](size_t i) const;
    /*2.*/// char operator[](size_t i) const;
    
    size_t Length() const;

private:
    friend const String operator+(String s1,const String& s2);
    friend bool operator==(const String& s1, const String& s2); // "hello" == s1 OR 
    friend bool operator<(const String& s1, const String& s2); // "hello" == s1 OR 
    friend bool operator>(const String& s1, const String& s2); // "hello" == s1 OR 
    friend std::ostream& operator<<(std::ostream& os, const String& s);
    void StringCreate(const char* str);

    char *str;
};
                                                    


} // namespace rd90
} // namespace ilrd




