#include <stdio.h>

#define ENDIANNESS *(char*)("\1")

int main()
{
	printf("%d\n", ENDIANNESS);

	return 0;
}
