#include <stdio.h>
/* multiplyes without * */ 
int MulR(int a, int b)
{
	if (b == 0)
	{
		return b;
	}

	else if (b > 0)
	{
		return MulR(a, b-1) + a;
	}

	return MulR(a, b+1) + -a;
}

/* adds 1 bitwise style */
int Add1(int a)
{
	unsigned mask = 1;

	while (a & mask)
	{
		a ^= mask;
		mask <<= 1;
	}

	return a ^ mask;
}

/* adds 1 bitwise style recursively */
int _Add1(int a, int mask)
{
	if (!(a & mask))
	{
		return a ^ mask;
	}

	return mask ^ _Add1(a, mask << 1);
}

/* _Add1's wrapper */
int Add1R(int a)
{
	return _Add1(a, 1);
}

int main()
{
	printf("%d\n", MulR(5,10));
	printf("%d\n", Add1R(21));

	return 0;
}
