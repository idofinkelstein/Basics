#include <cstdlib>
#include <iostream>
#include <cstring>

#include "rs_string.hpp"

namespace ilrd
{
namespace rd90
{

struct Buff
{
	size_t counter;
	char str[1];
};
                                     
RSString::RSString(const char* str) : buff(RSStringCreate(str)) {}

RSString::RSString(const char* str1, const char* str2) : buff(RSStringCreate(str1, str2)) {}

Buff *RSString::RSStringCreate(const char *str1, const char* str2)
{
    size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	Buff *buff = static_cast<Buff*>(malloc(sizeof(Buff) + len1 + len2));
    memcpy(&buff->str, str1, len1 + 1);
	memcpy(&buff->str + len1, str2, len2 + 1);
	buff->counter = 1;

    return (buff);
}
       
void RSString::BuffCleanup()
{
	--buff->counter;
	if (buff->counter == 0)
	{
		free(buff);
	}
}

RSString::RSString(const RSString& other)
{
	BuffUpdate(other);
}
        
RSString::~RSString()
{
	BuffCleanup();
}

void RSString::BuffUpdate(const RSString& other)
{
	buff = other.buff;
	++buff->counter;
}

RSString& RSString::operator=(const RSString &other)
{

	if (&other != this)
	{
		BuffCleanup();

		BuffUpdate(other);
    }
    return (*this);
}

const char& RSString::operator[](size_t i) const
{
	return (buff->str[i]);
}

char& RSString::operator[](size_t i)
{
	if (buff->counter > 1)
	{
		--buff->counter;
		buff = RSStringCreate(buff->str);
	}
	return (const_cast<char&>( static_cast<const RSString&>(*this)[i]) );
}

const RSString operator+(const RSString& s1,const RSString& s2)
{
	return (RSString(s1.buff->str, s2.buff->str));
}

std::ostream& operator<<(std::ostream& os, const RSString& s)
{
    return (os << &s[0]);
}

size_t RSString::Length() const
{
    return (strlen(buff->str));
}

bool operator==(const RSString& s1, const RSString& s2)
{
	 return (0 == strcmp(&s1[0], &s2[0]));
}

bool operator<(const RSString& s1, const RSString& s2)
{
	 return (0 > strcmp(&s1[0], &s2[0]));
}
bool operator>(const RSString& s1, const RSString& s2)
{
	return (0 < strcmp(&s1[0], &s2[0]));
}

} // namespace rd90
} // namespace ilrd


