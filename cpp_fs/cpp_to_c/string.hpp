#pragma once

namespace ilrd
{

class String;
const String operator+(String s1, const String& s2);
// s1 + s2 + s3
class String
{
public:
	/*non-explicit*/ String(const char* str = "", const char* anotherStr = "");
	String(const String& str);
	~String();

    String& operator+=(const String& other);
    String& operator=(String other);
	bool operator==(const String& other);

	char& operator[](size_t idx);
	const char& operator[](size_t idx) const;

    friend void swap(String& a, String& b);

private:
	char* m_Str;

    void CleanupIMP();
    static char* ConcatIMP(const char* s1, const char* s2 = "");
};

} // namespace ilrd
