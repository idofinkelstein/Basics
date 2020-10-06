#include <stdio.h>
#include <stdlib.h>

int g = 144;
int *p_g = &g;

int foo();
static int bar();
void fifi();

int main(int argc, char **argv)
{
	int x = 5;
	int arr[1000] = {0};
	char *lcp = (char*)malloc(10000 * sizeof(char));
	char *cp = (char*)malloc(sizeof(char));
	int *px = &x;

	printf("address of g = %p\n", (void*)&g);
	printf("address of p_g = %p\n", (void*)&p_g);
	printf("address of p_g-> = %p\n", (void*)p_g);
	printf("address of x = %p\n", (void*)&x);
	printf("address of arr = %p\n", (void*)arr);
	printf("address of lcp = %p\n", (void*)&lcp);
	printf("address of lcp-> = %p\n", (void*)lcp);
	printf("address of cp = %p\n", (void*)&cp);
	printf("address of cp-> = %p\n", (void*)cp);
	printf("address of px = %p\n", (void*)&px);
	printf("address of px-> = %p\n", (void*)px);
	printf("address of foo = %p\n", foo);
	printf("address of bar = %p\n", bar);
	printf("address of argc = %p\n", (void*)&argc);
	printf("address of argv = %p\n", (void*)&argv);
	printf("address of argv-> = %p\n", (void*)argv);

	fifi();

	return 0;
}

int foo()
{
	return 3;
}

static int bar()
{
	return 0;
}

void fifi()
{
	fifi();
}
