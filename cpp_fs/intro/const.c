#include <stdio.h>
const int i = 3;
int j = 3;

int main()
{
	int *ip = (int*)&i;
	int arr[i];
	*ip = 5;

	printf("%d %d\n", i, *ip);
	return 0;
}
