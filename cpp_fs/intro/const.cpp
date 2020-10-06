#include <stdio.h>
const int i = 3;

int main()
{
int j = 3;
	int *ip = (int*)&i;
	*ip = 5;
	int arr[j];

	printf("%d %d\n", i, *ip);
	return 0;
}
