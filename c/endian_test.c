#include <stdio.h>

#define ENDIAN_TYPE										

int main()
{
	int x = 0xAABBCCDD;
	int i = 0;
	char *px = (char*)&x;
	unsigned long c = 'A';
	unsigned long l = 0;
	unsigned long shift  = 8;
	char *pl = (char*)&l;

	
	printf("The system is: ");
	if(1 == *px)
	{
		puts("little endian");
	}
	else
	{
		puts("big endian");
	}

	
	l = c;

	for(i = 0; i < 4; ++i)
	{
		printf("0X%X ", *(px + i));
	}
	printf("\n0X%X\n",x);
	printf("\n%d\n",x & 7);

	while(c)
	{
		l = l | (c <<= shift);
	}
	i =8;
	printf("%lx\n",c);
	printf("%lx\n",l);

	while (i)
	{
		printf("%c", *pl);
		++pl;
		--i;
	}

	l = 'A';
	l = l | l << 8;
	l = l | l << 16;
	l = l | l << 32;

	printf("\n%lx\n",l);

	ENDIAN_TYPE;


	puts("");

	return 0;
}


