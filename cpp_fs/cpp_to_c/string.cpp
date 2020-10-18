#include <iostream>
#include <cstring>

#include "string.hpp"


namespace ilrd
{

String::String(const char* str, const char* anotherStr) : m_Str(ConcatIMP(str,anotherStr))
{
	std::cout << "\tString ctor\n";
}

String::String(const String& str) : m_Str(ConcatIMP(str.m_Str))
{
	std::cout << "\tString cctor\n";
}

String::~String()
{
	std::cout << "\tString dtor\n";
    CleanupIMP();
}

const String operator+(String s1, const String& s2)
{
	std::cout << "\tString oper+\n";
    return s1 += s2;
}

String& String::operator+=(const String& other)
{
	std::cout << "\tString oper+=\n";
	return *this = String(m_Str, other.m_Str);
}

String& String::operator=(String other)
{
	std::cout << "\tString oper=\n";
    swap(*this, other);
	return *this;
}

bool String::operator==(const String& other)
{
	std::cout << "\tString oper==\n";
    return !strcmp(m_Str, other.m_Str);
}

char& String::operator[](size_t idx)
{
	std::cout << "\tString oper[]\n";
	return const_cast<char&>( const_cast<const String&>(*this)[idx] );
}

const char& String::operator[](size_t idx) const
{
	std::cout << "\tString oper[] const\n";
	return m_Str[idx];
}

void swap(String& a, String& b)
{
	using std::swap;
	swap(a.m_Str, b.m_Str);
}

void String::CleanupIMP()
{
	delete [] m_Str;
}

char* String::ConcatIMP(const char* s1, const char* s2)
{
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2) + 1;

	char* str = new char[len1 + len2];

	memcpy(str, s1, len1);
	memcpy(str+len1, s2, len2);

	return str;
}

} // namespace ilrd
