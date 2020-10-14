#include <string.h>

#include "string.hpp"

namespace ilrd
{
namespace rd90
{

String::String(const char* str): str(StringCreate(str)) {}
/*-----------------------------------------------------------------------------*/
String::String(const String& other): str(StringCreate(other.str)) {}
/*-----------------------------------------------------------------------------*/

String& String::operator=(const String &other)
{
    if (this != &other)
    {
        char *temp_str = StringCreate(other.str);
        delete[] this->str;
        this->str = temp_str;
    }
    return (*this);
}
/*-----------------------------------------------------------------------------*/

String::~String()
{
    delete[] str;
}

/*-----------------------------------------------------------------------------*/

char *String::StringCreate(const char *str)
{
    size_t len = strlen(str);
    char *new_str = new char[len + 1];

    memcpy(new_str, str, len + 1);

    return (new_str);
}

char& String::operator[](size_t i)
{
    return (str[i]);
}
/*-----------------------------------------------------------------------------*/
const char& String::operator[](size_t i) const
{
    return (str[i]);
}
/*-----------------------------------------------------------------------------*/

String& String::operator+=(const String& other)
{   
    //str1 = "hello "
    //str2 = "world"
    // str1 += str2 ==> str1 = "hello world"

    String temp(*this);
    size_t old_len = Length();
    size_t other_len = other.Length();
    size_t new_len = old_len + other_len + 1;

    delete[] str;

    str = new char[new_len];
    memcpy(str, temp.str, old_len + 1);
    strcat(str, other.str);

    return (*this);
}
/*-----------------------------------------------------------------------------*/

const String operator+(String s1,const String& s2)
{
    // s1 = s2 + s3;

    return (s1 += s2);
}
/*-----------------------------------------------------------------------------*/

bool operator==(const String& s1, const String& s2)
{
    return (0 == strcmp(&s1[0], &s2[0]));
}
/*-----------------------------------------------------------------------------*/

bool operator<(const String& s1, const String& s2)
{
    //s1 < s2 ==> returns 1 if true

     return (0 > strcmp(&s1[0], &s2[0]));
}

bool operator>(const String& s1, const String& s2)
{
     return (0 < strcmp(&s1[0], &s2[0]));
}
/*-----------------------------------------------------------------------------*/

std::ostream& operator<<(std::ostream& os, const String& s)
{
    return (os << &s[0]);
}
/*-----------------------------------------------------------------------------*/


size_t String::Length() const
{
    return (strlen(str));
}

}// namespace rd90
}// namespace ilrd
