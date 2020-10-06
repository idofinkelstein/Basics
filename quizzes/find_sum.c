/*
Given an unsorted array of integers, find a pair with given sum in it.

For example:

input: arr = [8, 7, 2, 5, 3, 1]
sum = 10

output:
Pair found at index 0 and 2 (8 + 2)
or
Pair found at index 1 and 4 (7 + 3)
*/

#include <stdio.h>

void FindPairThatMatchSum(int *arr, size_t size, int sum)
{
	int dig[10]= {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,};
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		if (dig[sum - arr[i]] != -1)
		{
			printf("first index = %ld\nsecond index = %d\n",
				   i, dig[sum - arr[i]]);
		}
		else
		{
			dig[arr[i]] = i;
		}
	}
}

int main()
{
	int arr[] = {2, 4, 1, 9 ,3, 6, 2, 5, 6};

	FindPairThatMatchSum(arr, 9 ,10);

	return 0;	
}

