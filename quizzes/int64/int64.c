#include <stdio.h>
#include <string.h>

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

static unsigned SetBit(unsigned num, int index, int state)
{
	return ((num & ~(1ul << index)) | (state << index));
} 

static int BitState(unsigned num, int index)
{
	return (!!(num & (1ul << index)));
}
