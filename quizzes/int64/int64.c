#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "int64.h"

static const int max_shift = 31;

static unsigned SetBit(unsigned num, int index, int state);
static int BitState(unsigned num, int index);
int IsNegative(Int64_t num);

Int64_t Int64(const char *val)
{
	Int64_t num = {0, 0};
	Int64_t num2 = {1, 0};	
	Int64_t base = {10, 0};
	Int64_t digit = {0, 0};
	size_t i = 0;
	size_t len = strlen(val);
	char sign = 1;

	if('-' == val[0]) /* handles negative number */
	{
		sign = -sign;
		++i;
	}

	for (; i < len; ++i)
	{
		digit.lsi = val[i] - '0';
		num = Int64Add(Int64Mul(num, base),  digit);
	}

	if (sign < 0)
	{
		num = Int64Add(I64Tilde(num), num2);
	}

	return (num);
}

int I64IsEqual(Int64_t num1, Int64_t num2)
{
	return (num1.lsi == num2.lsi && num1.msi == num2.msi);
}

Int64_t I64Tilde(Int64_t num)
{
	Int64_t res = {0, 0};

	res.lsi = ~(unsigned)num.lsi;
	res.msi = ~(unsigned)num.msi;

	return (res);
}

Int64_t I64Shiftl(Int64_t num, int shift)
{
	int bit_state = 0;
	int i = 0;

	for (i = 0; i < shift; ++i)
	{
		num.msi <<= 1;

		bit_state = BitState(num.lsi, 31);
		num.msi = SetBit(num.msi, 0, bit_state);

		num.lsi <<= 1;	
	}

	return (num);
}

Int64_t I64Shiftl2(Int64_t num, int shift)
{
	unsigned mask = ((~0u << (32 - shift)) & num.lsi) >> (32 - shift);
	
	if (shift > max_shift)
	{
		num.msi = num.lsi << (shift -  32);
		num.lsi = 0;
	}
	else
	{
		num.msi = (num.msi << shift) | mask;
		num.lsi <<= shift;
	}

	return (num);
}

Int64_t Int64Add(Int64_t num1, Int64_t num2)
{
	Int64_t res = {0, 0};
	static const int carry_lut[] = {0, 0, 1, 0, 1, 0, 1, 1};
	int carry = 0;
	int n1_s_bit, n2_s_bit, r_s_bit;

/*
								num1 num2 res		carry
								  0			0		0	=	0
								  0			0		1	=	0
								  0			1		0	=	1
								  0			1		1	=	0
								  1			0		0	=	1
								  1			0		1	=	0
								  1			1		0	=	1
								  1			1		1	=	1
*/

	res.lsi = (unsigned)num1.lsi + (unsigned)num2.lsi;

	/* equal 1 if the values lesser than zero */
	n1_s_bit = num1.lsi < 0; 
	n2_s_bit = num2.lsi < 0;
	r_s_bit = res.lsi < 0; 

	carry = 	carry_lut[n1_s_bit << 2 | n2_s_bit << 1 | r_s_bit];

	res.msi = (unsigned)num1.msi + (unsigned)num2.msi + carry;

	return (res);
}

Int64_t Int64Mul(Int64_t num1, Int64_t num2)
{
	unsigned i = 0;
	unsigned j = 0;
	unsigned k = 0;
	unsigned max_val = 1u << 31;
	Int64_t res = {0, 0};

	if ((num1.lsi == 0 && num1.msi == 0) ||
		(num2.lsi == 0 && num2.msi == 0))
	{
		return (res);
	}

	for (i = 0; i < (unsigned)abs(num2.lsi); ++i)
	{
		res = Int64Add(num1, res);
	}

	if (num2.msi == 0)
	{
		return (res);
	}

	for (k = 0; k < 2; ++k)
	{
		for (i = 0; i < max_val; ++i)
		{
			for (j = 0; j < (unsigned)abs(num2.msi); ++j)
			{
				res = Int64Add(num1, res);
			}
		}
	}

	return (res);
}

int IsNegative(Int64_t num)
{
	unsigned mask = 1u << 31;

	return !!(num.msi & mask);
}

static unsigned SetBit(unsigned num, int index, int state)
{
	return ((num & ~(1ul << index)) | (state << index));
} 

static int BitState(unsigned num, int index)
{
	return (!!(num & (1ul << index)));
}
