#include <stdio.h>

#define IS_LITTLE_ENDIAN *(char*)(short*)&("\5")

int main()
{
	unsigned char a = '3';
	unsigned long lg = 0;

	lg = (a | a << 7) | a << 15;

	printf("%ld\n", *&lg);

	printf("%d\n", IS_LITTLE_ENDIAN);

	return 0;
}
