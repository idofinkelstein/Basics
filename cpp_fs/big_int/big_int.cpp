#include <iostream>

#include "bigint.hpp"

const static int LSI = 0;
const static int MSI = 1;


namespace ilrd
{
namespace rd90
{

Bigint::Bigint(word_t num)
{
    words[LSI] = num;
    words[MSI] = 0;

    if (num < 0)
    {     
        words[MSI] = ~0; 
    }
}

const Bigint Bigint::operator+(const Bigint &num)
{
    Bigint res;
    static const int carry_lut[] = {0, 0, 1, 0, 1, 0, 1, 1};
	int carry = 0;
	int n1_s_bit, n2_s_bit, r_s_bit;

    res.words[LSI] = words[LSI] + num.words[LSI];

    n1_s_bit = words[LSI] < 0; 
	n2_s_bit = num.words[LSI] < 0;
	r_s_bit = res.words[LSI] < 0; 

    carry = carry_lut[n1_s_bit << 2 | n2_s_bit << 1 | r_s_bit];

    res.words[MSI] = unsigned(words[MSI]) + unsigned(num.words[MSI]) + carry;

    return (res);
}

Bigint &Bigint::operator+=(const Bigint& num)
{
    *this = *this + num;

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Bigint &bigint)
{
    os /*<< "0x" << std::hex*/ << bigint.words[MSI] /* <<  std::hex*/ << bigint.words[LSI];

    return os;
}

} // namespace rd90
} // namespace ilrd
