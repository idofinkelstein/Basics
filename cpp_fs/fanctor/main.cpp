
// 1. g++ -g main.cpp
// 2. g++ -g -O1 main.cpp
#include <iostream>
#include <cstdio>


template<typename InputIt, typename UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
{
    for (; first != last; ++first)
    {
        printf("fe: %p\n", __builtin_frame_address(0));
        f(*first); 
    }

    return f;
}


// option 1 - inline function
inline void PrintData(int data)
{
    printf("fn: %p\n", __builtin_frame_address(0));
    printf("Value = %d\n", data);
}


// option 2 - functor
class PrintDataFunctor
{
public:
    PrintDataFunctor() : m_count(0) {}

    void operator()(int data)
    {
        printf("(): %p\n", __builtin_frame_address(0));
        printf("Value = %d\n", data);
        m_count++;
    }

    size_t GetCount() { return m_count; }

private:
    size_t m_count;
};



int main()
{
    int arr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };


    // option 1 - function
    for_each<  int*,void(*)(int)  >(&arr[0], &arr[10], PrintData);


    puts("---------------\n");


    // option 2 - functor
    PrintDataFunctor f = for_each<  int*,PrintDataFunctor  >(&arr[0], &arr[10], PrintDataFunctor());
    printf("--- %ld\n", f.GetCount());


    return 0;
}
