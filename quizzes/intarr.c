#include <stdio.h>
#include  <stdlib.h>

long *SumIntPairsToLongs(int ints[], size_t size)
{
	size_t i = 0;
	void *sum = ints;
	
	while (i < size / 2)
	{ 
		*(long*)sum = (long)*(ints + 0) + *(ints + 1);
		
		ints = ints + 2;
		sum = (long*)sum + 1;
		++i;
	}

	return ((long*)ints);
}

int main()
{
	int arr[] = {1, 3,5 ,4 ,3,3};
	
	size_t i = 0;
	long *a = (long*)&arr[0];
	SumIntPairsToLongs(arr, 6); 	

	for (i = 0; i < 3; ++i)
	{
		printf("%ld ", a[i]);
	}
	

	return 0;
}
