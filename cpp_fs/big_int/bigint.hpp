/* 

Bigint class is a double int of integral type, equals to a long.

operations to be done on type:
	- Default Ctor - returns Bigint initialized to zero
    - Ctor with int - initializes a Bigint to an int value
    - Cctor - copy constructor
    - "=" (assign operator) - assign a value  of non-lvalue Bigint variable to 
                              the lvalue Bigint
    = "+" (add operator) - adds two Bigints variables
	- print using ostream object of std namespace - using the << operator 
      syntax.


Example:
void foo()
{
    Bigint x1;
    Bigint x2;
    Bigint x3;

    x3 = x1 + x2;

    Bigint x4 = x2;
    Bigint x5(x4);

    x2 = x1 += x5;
    
    std::cout << "x4 + x1: " << x4 + x1 << std::endl;

}

*/

#ifndef ILRD_90_BIGINT_HPP
#define ILRD_90_BIGINT_HPP



#include <iostream>     //ostream

/*---------------------------------------------------------------------------*/

namespace ilrd
{
namespace rd90
{

class Bigint
{
public:
    typedef int word_t;
    /* non-explicit */ Bigint(word_t num = 0);    // default ctor, with int
    // using generated functions

    //const Bigint operator+(const Bigint &num) const;
    Bigint& operator+=(const Bigint &num);
    const Bigint operator~() const;

    friend std::ostream& operator<<(std::ostream &os, const Bigint &bigint);
    friend const Bigint operator+(const Bigint &num1, const Bigint &num2); 

private:
    word_t words[2];
};

} // namespace rd90
} // namespace ilrd


#endif  /* ILRD_90_BIGINT_HPP */


