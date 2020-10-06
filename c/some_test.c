#include <stdio.h>

size_t BitArrMirror(size_t arr)
{
	arr = (arr >> 32) | (arr << 32);

	arr = (((arr & 0x0000FFFF0000FFFF) << 16)) | (((arr & 0xFFFF0000FFFF0000) >> 16));

	arr = (((arr & 0x00FF00FF00FF00FF) << 8)) | (((arr & 0xFF00FF00FF00FF00) >> 8));

	arr = (((arr & 0x0F0F0F0F0F0F0F0F) << 4)) | (((arr & 0xF0F0F0F0F0F0F0F0) >> 4));

	arr = (((arr & 0x3333333333333333) << 2)) | (((arr & 0xCCCCCCCCCCCCCCCC) >> 2));

	arr = (((arr & 0x5555555555555555) << 1)) | (((arr & 0xAAAAAAAAAAAAAAAA) >> 1));
	
	return (arr);
}

void PrintBit(size_t num)
{
	
	size_t mask = (size_t)1 << 63;

	while (mask)
	{
		printf("%d", !!(mask & num)); 
		
		mask >>= 1;
	}

	puts("");
}

size_t foo(size_t x)
{
	return(x = ~0);
}

int main()
{
	size_t  a = 23;
	size_t b = ~0;

	a = foo(a);

	printf("%lu\n", a);

	PrintBit(b);
	b = BitArrMirror(b);
	PrintBit(b);
	

	return 0;
}
