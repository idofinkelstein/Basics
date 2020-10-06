#include <stdio.h>

void SetBit(unsigned *num, int index, long state)
{
	*num = (*num & ~(1ul << index)) | (state << index);
}

int main()
{
	unsigned x = 0;

	SetBit(&x, 0, 0);
	printf("%u\n", x);

	return 0;
}
