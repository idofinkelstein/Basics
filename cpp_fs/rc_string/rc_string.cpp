#include <cstdlib>
#include <iostream>
#include <cstring>

#include "rc_string.hpp"

namespace ilrd
{
namespace rd90
{

struct Buff
{
	size_t counter;
	char str[1];
};
                                     
RCString::RCString(const char* str) : buff(RCStringCreate(str)) {}

RCString::RCString(const char* str1, const char* str2) : buff(RCStringCreate(str1, str2)) {}

Buff *RCString::RCStringCreate(const char *str1, const char* str2)
{
    size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	Buff *buff = static_cast<Buff*>(malloc(sizeof(Buff) + len1 + len2));
    memcpy(&buff->str, str1, len1 + 1);
	memcpy(&buff->str + len1, str2, len2 + 1);
	buff->counter = 1;

    return (buff);
}
       
void RCString::BuffCleanup()
{
	--buff->counter;
	if (buff->counter == 0)
	{
		free(buff);
	}
}

RCString::RCString(const RCString& other)
{
	BuffUpdate(other);
}
        
RCString::~RCString()
{
	BuffCleanup();
}

void RCString::BuffUpdate(const RCString& other)
{
	buff = other.buff;
	++buff->counter;
}

RCString& RCString::operator=(const RCString &other)
{

	if (&other != this)
	{
		BuffCleanup();

		BuffUpdate(other);
    }
    return (*this);
}

const char& RCString::operator[](size_t i) const
{
	return (buff->str[i]);
}

char& RCString::operator[](size_t i)
{
	if (buff->counter > 1)
	{
		--buff->counter;
		buff = RCStringCreate(buff->str);
	}
	return (const_cast<char&>( static_cast<const RCString&>(*this)[i]) );
}

const RCString operator+(const RCString& s1,const RCString& s2)
{
	return (RCString(s1.buff->str, s2.buff->str));
}

std::ostream& operator<<(std::ostream& os, const RCString& s)
{
    return (os << &s[0]);
}

size_t RCString::Length() const
{
    return (strlen(buff->str));
}

bool operator==(const RCString& s1, const RCString& s2)
{
	 return (0 == strcmp(&s1[0], &s2[0]));
}

bool operator<(const RCString& s1, const RCString& s2)
{
	 return (0 > strcmp(&s1[0], &s2[0]));
}
bool operator>(const RCString& s1, const RCString& s2)
{
	return (0 < strcmp(&s1[0], &s2[0]));
}

} // namespace rd90
} // namespace ilrd


