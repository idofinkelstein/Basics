#include <iostream>

#include "d_vector.hpp"
#include "rc_string.hpp"

using namespace ilrd::rd90;

void TestStringMembers(void);
void TestIntMembers(void);
int main()
{  
	TestStringMembers();
	TestIntMembers();

    return 0;
}

void TestStringMembers(void)
{
	DVector<RCString>v(1);
	std::cout << "capacity = " << v.Capacity() << std::endl;
	for(size_t i = 0; i < 100; ++i)
	v.PushBack("hello");

	v[5] = v[5] + " world";

	v[12] = v[5];

	v[99] = v[13] = v[5];

	std::cout << "capacity = " << v.Capacity() << std::endl;

	for(size_t i = 0; i < 100; ++i)
	std::cout << v[i] << std::endl;

	for(size_t i = 0; i < 80; ++i)
	v.PopBack();

	std::cout << "capacity = " << v.Capacity() << std::endl;
	std::cout << "size = " << v.Size() << std::endl;

	v.Resize(300, "bye");

	for(size_t i = 0; i < v.Size(); ++i)
	std::cout << v[i] << i << std::endl;

}

void TestIntMembers(void)
{
	DVector<int> v(4);

	for(size_t i = 0; i < 100; ++i)
    {
        v.PushBack(5);
    }
}
