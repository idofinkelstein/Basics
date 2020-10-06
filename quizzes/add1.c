#include <stdio.h>

void Add1(int num)
{
	int before = num;
	unsigned int mask = 1;

	while (num & mask)
	{
		num ^= mask;
		mask <<= 1;
	}

	num ^= mask;

	printf("%d + 1 = %d\n", before, num);
}

int main()
{
	Add1(34);
	Add1(47);
	Add1(0);
	Add1(7);

	return 0;
}

