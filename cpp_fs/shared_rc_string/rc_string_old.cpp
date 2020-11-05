#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cstddef>

#include "rc_string.hpp"

namespace ilrd
{
namespace rd90
{





RCString::StringData::StringData(const char *lhs, const char *rhs,
												    size_t lhLen, size_t rhLen) 
												
{
	memcpy(&str, lhs, lhLen + 1);
	memcpy(&str + lhLen, rhs, rhLen);
}


RCString::RCString(const char* str) : m_str(StringData::Create(str)) 
{
	
}

RCString::RCString(const char* str1, const char* str2) : 
							  m_str(StringData::Create(str1, str2)) {}

RCString::StringData *RCString::StringData::Create(const char *str1, const char* str2)
{
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2) + 1;

	void *buff = ::operator new(len1 + len2);

    return  new (buff) StringData(str1, str2, len1, len2);
}
       


        


void RCString::StringDataUpdate(const RCString& other)
{
	m_str = other.m_str;
	
}



const char& RCString::operator[](size_t i) const
{
	return ((*m_str)[i]);	
}

RCString::Proxy RCString::operator[](size_t i)
{
	return (Proxy(*this, i));
}

const RCString operator+(const RCString& s1,const RCString& s2)
{
	return (RCString(&s1[0], &s2[0]));
}

std::ostream& operator<<(std::ostream& os, const RCString& s)
{
    return (os << &s[0]);
}

size_t RCString::Length() const
{
    return (strlen(&(*m_str)[0]));
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





void RCString::StringData::Detach()
{	
	delete this;
}


void RCString::Setchar(char c, size_t i)
{
	(*m_str)[i] = c;
}

RCString::Proxy::Proxy(RCString& str, size_t index) : m_str(&str), m_i(index) {}

RCString::Proxy::operator char() const
{
	return ((*m_str->m_str)[m_i]);
}

char RCString::Proxy::operator=(char c)
{
	if (m_str->m_str.UseCount() > 1)
	{
		// this is the problem
		m_str->m_str->RCString::StringData::Create(*(m_str->m_str));
	}

	m_str->Setchar(c, m_i);

	return c;
}

const char &RCString::StringData::operator[](size_t i) const
{
	return str[i];
}

char &RCString::StringData::operator[](size_t i)
{
	return str[i];
}

char RCString::Proxy::operator=(const Proxy& other)
{
    return (*this = static_cast<char>(other));
}

} // namespace rd90
} // namespace ilrd


