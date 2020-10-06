int MaxSum(int arr*, size_t size)
{
	int sum = 0;
	int mid_sum = 0;
	size_t i = 0;

	for (i = 0; i < size; ++i)
	{
		if(mid_sum + arr[i] >= 0 && mid_sum + arr[i] > sum)
		{
			sum = mid_sum + arr[i];
			mid_sum = sum;
		}
		else if(mid_sum + arr[i] >= 0)
		{
			mid_sum = mid_sum + arr[i];
		}
		else
		{
			sum = 0;
			mid_sum = 0;
		}
	}

	if(sum > mid_sum)
	{
		return sum;
	}

	return(mid_sum);
}
