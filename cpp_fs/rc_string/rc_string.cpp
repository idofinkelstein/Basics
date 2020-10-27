#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cstddef>

#include "rc_string.hpp"

namespace ilrd
{
namespace rd90
{
                              
RCString::RCString(const char* str) : m_str(StringData::Create(str)) {}

RCString::RCString(const char* str1, const char* str2) : 
							  m_str(StringData::Create(str1, str2)) {}

RCString::StringData *RCString::StringData::Create(const char *str1, const char* str2)
{
    size_t len1 = strlen(str1);
	size_t len2 = strlen(str2) + 1;

	void *buff = operator new(offsetof(StringData, str) + len1 + len2);
   
    return  new (buff)   StringData(str1, str2, len1, len2);
}
       
void RCString::StringDataCleanup()
{
	--m_str->counter;
	if (m_str->counter == 0)
	{
		delete m_str;
	}
}

RCString::RCString(const RCString& other)
{
	StringDataUpdate(other);
}
        
RCString::~RCString()
{
	StringDataCleanup();
}

void RCString::StringDataUpdate(const RCString& other)
{
	m_str = other.m_str;
	++m_str->counter;
}

RCString& RCString::operator=(const RCString &other)
{

	if (&other != this)
	{
		StringDataCleanup();

		StringDataUpdate(other);
    }
    return (*this);
}

const char& RCString::operator[](size_t i) const
{
	return (m_str->str[i]);
}

RCString::Proxy RCString::operator[](size_t i)
{
	return (Proxy(*this, i));
}

const RCString operator+(const RCString& s1,const RCString& s2)
{
	return (RCString(s1.m_str->str, s2.m_str->str));
}

std::ostream& operator<<(std::ostream& os, const RCString& s)
{
    return (os << &s[0]);
}

size_t RCString::Length() const
{
    return (strlen(m_str->str));
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

RCString::StringData::StringData(const char *lhs, const char *rhs,
												    size_t lhLen, size_t rhLen) :
													counter(1)
{
	memcpy(&str, lhs, lhLen + 1);
	memcpy(&str + lhLen, rhs, rhLen);
}

<<<<<<< HEAD
RCString::Proxy::Proxy(RCString& str, size_t index) : m_str(&str), m_i(index) {}

RCString::Proxy::operator char() const
{
	return m_str->m_str->str[m_i];
}

char RCString::Proxy::operator=(char c)
{
	if (m_str->m_str->counter > 1)
	{
		--m_str->m_str->counter;
		m_str->m_str = StringData::Create(m_str->m_str->str);
	}

	m_str->m_str->str[m_i] = c;

	return c;
}
=======

>>>>>>> 4a9ab5dd4c40f10db7b17f51b296ffc35be6487d

} // namespace rd90
} // namespace ilrd


