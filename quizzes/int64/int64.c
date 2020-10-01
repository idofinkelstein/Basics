#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "int64.h"

static unsigned SetBit(unsigned num, int index, int state);
static int BitState(unsigned num, int index);

Int64_t Int64(const char *val)
{
	Int64_t num = {0, 0};
	size_t i = 0;
	size_t len = strlen(val);
	char sign = 1;

	if('-' == *val) /* handles negative number */
	{
		sign = -sign;
		++val;
	}

	for (i = 0; i < len; ++i)
	{
		num.lsi = 10 * num.lsi + val[i] - '0';
	}

	num.lsi *= sign;

	return (num);
}

int I64IsEqual(Int64_t num1, Int64_t num2)
{
	return (num1.lsi == num2.lsi && num1.msi == num2.msi);
}

Int64_t I64Tilde(Int64_t num)
{
	Int64_t res = {0, 0};

	res.lsi = ~num.lsi;
	res.msi = ~num.msi;

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
	

	

	if (shift > 31)
	{
		num.msi = num.lsi << (shift -  32);
		num.lsi = 0;
	}
	else
	{
		num.msi = (num.msi << shift) | mask;
		num.lsi <<= shift;
	}


	/*printf("num.lsi = %d\n", num.lsi);*/

	return (num);
}

Int64_t Int64Add(Int64_t num1, Int64_t num2)
{
	Int64_t res = {0, 0};

	return (res);
}

static unsigned SetBit(unsigned num, int index, int state)
{
	return ((num & ~(1ul << index)) | (state << index));
} 

static int BitState(unsigned num, int index)
{
	return (!!(num & (1ul << index)));
}
