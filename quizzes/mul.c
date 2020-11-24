#include <stdio.h>

long Mul(int a, int b);

int main()
{
	int x = (13 << 0) + (13 << 1) +(13 << 2) + (13 << 3) * 0; 

	int y = (7 << 0) + (7 << 2) + (7 << 3);
	int num1 = 13;	
	int num2 = 7;




	printf("%d\n", x);
	printf("%d\n", y);
	printf("%ld\n", 	Mul(num1, num2));

	return 0;
}

long Mul(int a, int b)
{
	long sum = 0;
	int shift = 0;
	unsigned shift_bit = 0;
	unsigned ub = b;
/*
			1101
			0110
			0011
			0001
*/
	while (ub)
	{
		shift_bit = ub & 1;
		sum += (a << (shift++)) * shift_bit;
		ub >>= 1;
	}

	return (sum);
}
