#include <stdio.h>
#include <limits.h>

void FindMaxProduct(int arr[], size_t size)
{
	int max = arr[0];
	int second_max=INT_MIN;
	int min = arr[0];
	int sec_min = INT_MAX;
	
	size_t i = 0;

  for (i = 0; i < size; i++)
	{
		if (arr[i] > max)
		{
			second_max=max;
			max = arr[i];
		}

		else if (arr[i] > second_max)
		{
			second_max = arr[i];
		}
		
		if (arr[i] < min)
		{
			sec_min = min;
			min = arr[i];
		}

		else if (arr[i] < sec_min)
		{
			sec_min = arr[i];
		}
    }

	if (sec_min * min > max * second_max)
	{
		printf("max product = %d * %d = %d\n", min, sec_min, min * sec_min);
	}
	else
	{
		printf("max product = %d * %d = %d\n", max, second_max, max * second_max);
	}
}

int main()
{
	int arr[] = {-50, -110, 3, 5, 111, 0, 43, 1, -60, 1, 2, 5, 88, 12};
	size_t size = sizeof(arr) / sizeof(arr[0]);

	FindMaxProduct(arr, size);

	return 0;
}

