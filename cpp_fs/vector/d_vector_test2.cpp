#include <iostream>
#include "d_vector.hpp" 
#include "rc_string.hpp" 

using namespace ilrd::rd90;

static const size_t size_of_vector = 20;
static const size_t size_of_string_vector = 10;  

int main()
{
    DVector<RCString> string_vector(size_of_string_vector);

    string_vector.PushBack("Hello");
    string_vector.PushBack("World");
    string_vector.PushBack("We");
    string_vector.PushBack("Learn");
    string_vector.PushBack("C++");
    string_vector.PushBack("RD");
    string_vector.PushBack("90");

    // Print vector elements  
    for (size_t i = 0; i < string_vector.Size(); i++)
    {
        std::cout << "Element num " << i << " is " << string_vector[i] << std::endl;
    }

    // Change vector elements  
    std::cout << "Test operator [] - Change the first character of each word to the first character of vector[12]" << std::endl;
    for (size_t i = 0; i < string_vector.Size(); i++)
    {
        string_vector[i][0] = string_vector[12][0];
        std::cout << "Element num " << i << " is " << string_vector[i] << std::endl;
    }

/*
    string_vector[0] = "Hello";
    std::cout << "Element num " << 0 << " is " << string_vector[0] << std::endl;
*/

#if 1
    // Test Size Function
    std::cout << "Size of vector " << string_vector.Size() <<std::endl;

    // Change vector elements  
    for (size_t i =  string_vector.Size(); i > 0; i--)
    {
        std::cout << "Pop from vector" << std::endl;
        string_vector.PopBack();
        std::cout << "Size of vector " << string_vector.Size() <<std::endl;
    }

    std::cout << "Capacity of vector " << string_vector.Capacity() <<std::endl;
    string_vector.Resize(40);
    std::cout << "Capacity of vector " << string_vector.Capacity() <<std::endl;
    string_vector.Reserve(60);
    std::cout << "Capacity of vector " << string_vector.Capacity() <<std::endl;




    // Test Built in Type
    DVector<int> s_vector(size_of_vector);

    std::cout << "----------------------" << std::endl;
    std::cout << "Test PushBack Function" << std::endl;
    std::cout << "----------------------" << std::endl;

    // Push elements to the vector 
    for (size_t i = 0; i < 15; i++)
    {
        std::cout << "Push " << i << std::endl;
        std::cout << "Capacity of vector " << s_vector.Capacity() <<std::endl;

        s_vector.PushBack(i);    
    }

    std::cout << "----------------------" << std::endl;
    std::cout << "Test Size Function" << std::endl;
    std::cout << "Current Size is " << s_vector.Size() << std::endl;
    std::cout << "----------------------" << std::endl;

    std::cout << "Test Capacity Function" << std::endl;
    std::cout << "Current Capacity is " << s_vector.Capacity() << std::endl;
    std::cout << "----------------------" << std::endl;

    std::cout << "Print Vector Data" << std::endl;

    // Print vector elements  
    for (size_t i = 0; i < s_vector.Size(); i++)
    {
        std::cout << "Element num " << i << " is " << s_vector[i] << std::endl;
    }

    // Pop all vector elements 
    std::cout << "Pop all vector elements" << std::endl;
    std::cout << "----------------------" << std::endl;
    for (size_t i =  s_vector.Size(); i > 0; i--)
    {
        s_vector.PopBack();
    }

    std::cout << "----------------------" << std::endl;
    std::cout << "Current Size is " << s_vector.Size() << std::endl;
    std::cout << "Capacity of vector " << s_vector.Capacity() <<std::endl;


    // Push elements to the vector 
    for (size_t i = 0; i < 50; i++)
    {
        std::cout << "Push " << i << std::endl;
        std::cout << "Capacity of vector " << s_vector.Capacity() <<std::endl;

        s_vector.PushBack(i);    
    }

    for (size_t i = 0; i < 50; i++)
    {
        std::cout << "Pop " << i << std::endl;
        std::cout << "Size of vector " << s_vector.Size() <<std::endl;

        s_vector.PopBack();    
    }
    std::cout << "Capacity of vector " << s_vector.Capacity() <<std::endl;

    s_vector.Resize(20);
    std::cout << "Capacity of vector " << s_vector.Capacity() <<std::endl;

    // Print vector elements  
    for (size_t i = 0; i < s_vector.Size(); i++)
    {
        std::cout << "Element num " << i << " is " << s_vector[i] << std::endl;
    }
#endif

    return(0);
}
