#include <stdio.h>

int main()
{
	bool b1 = true;
	bool b2;
	int i = b1;
	printf("%d\n", b2);
	i = 7;
	printf("%d\n", i);
	b2 = i; 
	printf("%d\n", b2);
	printf("%lu\n", sizeof(bool));
	printf("%lu\n", sizeof(b1));

	return 0;
}
