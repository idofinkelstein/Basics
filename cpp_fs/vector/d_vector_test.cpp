#include <iostream>
#include <fstream>
#include <string>
#include "d_vector.hpp"
#include "rc_string.hpp"

using namespace ilrd::rd90;

void TestStringMembers(void);
void TestIntMembers(void);
void DictTest(void);

int main()
{  
	TestStringMembers();
	TestIntMembers();
	DictTest();

    return 0;
}

void TestStringMembers(void)
{
	DVector<RCString>v(1);
	DVector<RCString>v2(300);
	std::cout << "capacity = " << v.Capacity() << std::endl;
	for(size_t i = 0; i < 100; ++i)
	v.PushBack("hello");

	v[5] = v[5] + " world";

	v[12] = v[5];

	v[99] = v[13] = v[5];


	v.PopBack();

	std::cout << "capacity = " << v.Capacity() << std::endl;
	std::cout << "size = " << v.Size() << std::endl;

	v.Resize(300, "bye");

	for(size_t i = 0; i < v.Size(); ++i)
	std::cout << v[i] << i << std::endl;

	std::copy(v.Begin(), v.End(), v2.Begin());

	for(size_t i = 0; i < v2.Size(); ++i)
	std::cout << v2[i] << i << std::endl;


}

void TestIntMembers(void)
{
	DVector<int> v(4);
	
	for(size_t i = 0; i < 100; ++i)
    {
        v.PushBack(5);
    }
}

void DictTest(void)
{
	//DVector<std::string> v(0);
	DVector<RCString>v(1);

	std::ifstream ifs("/usr/share/dict/american-english");
	char s[200];

	while(ifs.getline(s, 35))
	v.PushBack(s);

	for(size_t i = 0; i < v.Size(); ++i)
	std::cout << v[i]  << std::endl;
}