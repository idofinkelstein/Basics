#include <stdio.h>

void foo(int a[], int size)
{
	int i = 0;
	int size1 = sizeof(int*);

	for (i = 0; i < size; ++i)
	{
		a[i] = i * 2;
	}

	printf("%d\n", size1);
}

int main()
{
	int arr[10] = {0};
	int size = sizeof(arr);	

	printf("%d\n", size);	
	
	foo (arr, 10);

	return (0);
}
