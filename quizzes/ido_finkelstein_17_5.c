int FindMaxProfit(int *arr, int size, int end_ptr, int start_ptr)
{
	int diff = 0;
	int i = 0;
	int *tmp_start = NULL;
	int tmp_end = NULL;	

	start_ptr = arr;
	end_ptr = arr + size - 1;

	tmp_start = start_ptr;
	tmp_end = end_ptr;

	diff = *tmp_end - *tmp_start;

	while (tmp_end + 1 > tmp_start)
	{
		if (arr[size - i - 2] - arr[size - i - 1] >
		    arr[i + 1] - arr[i])
		{
			--tmp_end;
		}
		else
		{
			++tmp_start;
		}

		if(*tmp_end - *tmp_start > diff)
		{
			diff = *tmp_end - *tmp_start;
			
			start_ptr = tmp_start;
			end_ptr = tmp_end;
		}

		++i;
	}

	return (diff); 	
}
