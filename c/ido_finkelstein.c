#include <stdio.h>

int SumFound(int *arr, size_t size, int sum, int *start, int *end)
{
	
	int *tmp_start = arr;
	int *tmp_end = arr + size - 1;

	while (tmp_end > tmp_start)
	{
		if (*tmp_start + *tmp_end > sum)
		{
			--tmp_end;
		}

		if (*tmp_start + *tmp_end < sum)
		{
			++tmp_start;
		}
		
		if (*tmp_start + *tmp_end == sum)
		{
			*start = tmp_start - arr;
			*end = tmp_end - arr;

			return 1;			
		}
	}

	return 0;
}

int main()
{
	int arr[] = {1, 3, 5, 6, 9, 12, 35, 40, 45, 46};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	int first_index = 0;
	int last_index = size - 1;


	printf("%d\n", SumFound(arr, size, 47, &first_index, &last_index));
	printf("%d\n%d\n", first_index, last_index);
	printf("%d\n", SumFound(arr, size, 75, &first_index, &last_index));
	printf("%d\n%d\n", first_index, last_index);

	return 0;
	
}
