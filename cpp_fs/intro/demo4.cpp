#include <stdlib.h>

int main()
{
	int *p = new int (5);

	delete p;

	int *p2 = (int*)malloc(4*10);

	delete p2;

	char *p3 = NULL;

	delete p3;

	return 0;
}
