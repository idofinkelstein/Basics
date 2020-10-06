#include <stdio.h>
#include <stdlib.h>

unsigned long GetNFibonacciElement(unsigned int n, unsigned long **fib_ptr)
{
	static unsigned last_n = 2;
	static unsigned long *fib_arr = NULL; /* array for saving computed values for future calls */
	unsigned long *tmp_arr = NULL; /* to get the return value from realloc */
	unsigned long res = 0;
	size_t i = 0;

	/* assignes more memory in case n is greater than last_n */
	tmp_arr = realloc(fib_arr, sizeof(unsigned long) * (last_n > n ? last_n : n));

	if (NULL == tmp_arr)
	{
		free(fib_arr);
		return 0;
	}

	fib_arr = tmp_arr;
	*fib_ptr = fib_arr; /* to free the memory outside the function */

	*fib_arr = 1;
	*(fib_arr + 1) = 1;

	if (0 == n)
	{
		printf("out of range\n");
		return 0;
	}

	/* if fib_arr[n - 1] computed in previous calls no need for loop */
	if(n <= last_n)
	{
		return (fib_arr[n-1]);
	}

	/* runs from the last computed n to n */
	for (i = last_n; i < n; ++i)
	{
		fib_arr[i] = fib_arr[i - 1] + fib_arr[i - 2];
	}
	
	last_n = n; /* saves n for future calls */

	res = fib_arr[n - 1];
	
	return (res);	
}

int main()
{
	unsigned long *fib_ptr = NULL;
	unsigned long res = 0;

	res = GetNFibonacciElement(6, &fib_ptr);
	printf("%ld\n", res);

	res = GetNFibonacciElement(3, &fib_ptr);
	printf("%ld\n", res);

	res = GetNFibonacciElement(8, &fib_ptr);
	printf("%ld\n", res);

	res = GetNFibonacciElement(8, &fib_ptr);
	printf("%ld\n", res);

	res = GetNFibonacciElement(15, &fib_ptr);
	printf("%ld\n", res);

	res = GetNFibonacciElement(12, &fib_ptr);
	printf("%ld\n", res);

	res = GetNFibonacciElement(16, &fib_ptr);
	printf("%ld\n", res);

	free(fib_ptr);
	return 0;
}
