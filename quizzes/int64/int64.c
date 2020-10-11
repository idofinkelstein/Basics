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
		/* -n = ~n + 1 */
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

/* old version of shift left */
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

Int64_t I64Shiftr(Int64_t num, int shift)
{
	unsigned lsi = num.lsi;
	unsigned msi = num.msi;

	if(shift == 0)
	{
		return (num);
	}

	if (shift > max_shift)
	{
		lsi = msi >> (shift - 32);
		msi = 0;
	}
	else
	{
		lsi = (lsi >> shift) | (msi << (32 - shift));
		msi >>= shift;
	}

	num.lsi = lsi;
	num.msi = msi;

	return (num);
}

Int64_t I64Shiftl2(Int64_t num, int shift)
{
	unsigned lsi = num.lsi;
	unsigned msi = num.msi;
	unsigned mask = ((~0u << (32 - shift)) & lsi) >> (32 - shift);
	
	if(shift == 0)
	{
		return (num);
	}
	
	if (shift > max_shift)
	{
		msi = lsi << (shift -  32);
		lsi = 0;
	}
	else
	{
		msi = (msi << shift) | mask;
		lsi <<= shift;
	}

	num.lsi = lsi;
	num.msi = msi;

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
	Int64_t res = {0, 0};
	int shift = 0;
	Int64_t sub_res = {0, 0};
	unsigned shift_bit = 0;

	while (num2.lsi || num2.msi) /* num2 != 0 */
	{
		shift_bit = num2.lsi & 1;
		sub_res = I64Shiftl2(num1, shift++);
		sub_res.lsi *= shift_bit;
		sub_res.msi *= shift_bit;
		res = Int64Add(res, sub_res);
		num2 = I64Shiftr(num2, 1);
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
