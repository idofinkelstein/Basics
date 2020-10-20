#include <string.h>
#include <assert.h>

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

char *String::StringCreate(const char *str1, const char* str2)
{
    size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	char *new_str = new char[len1 + len2 + 1];

    memcpy(new_str, str1, len1 + 1);
	memcpy(new_str + len1, str2, len2 + 1);

    return (new_str);
}

char& String::operator[](size_t i)
{
	// calls const oper[] and casts it to non-const.
    return (const_cast<char&>( static_cast<const String&>(*this)[i]) );
}
/*-----------------------------------------------------------------------------*/
const char& String::operator[](size_t i) const
{
	assert(i < Length());

    return (str[i]);
}
/*-----------------------------------------------------------------------------*/

String& String::operator+=(const String& other)
{   
	char *new_str = StringCreate(str, other.str);
   
	*this = new_str;
	delete[] new_str;

    return (*this/* = StringCreate(str, other.str)*/);
}
/*-----------------------------------------------------------------------------*/

const String operator+(String s1,const String& s2)
{
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
