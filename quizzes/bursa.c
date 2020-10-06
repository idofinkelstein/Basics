#include <stdio.h>

struct bursa
{
	size_t profit;
	size_t best_i;
	size_t profit_i;
};

struct bursa Bursa(size_t *arr, size_t size)
{
	size_t min_buy = arr[0];
	size_t max_profit = 0;
	size_t buy_i = 0;
	size_t profit_i = 0;
	size_t best_i = 0;
	size_t i = 0;
	struct bursa best;

	for (i = 0; i < size; ++i)
	{
		if(min_buy > arr[i])
		{
			buy_i = i;
			min_buy = arr[i];
		}
		if (arr[i] - min_buy > max_profit)
		{
			max_profit = arr[i] - min_buy;
			profit_i = i;
			best_i = buy_i;
		}
	}
	best.profit = max_profit;
	best.best_i = best_i;
	best.profit_i = profit_i;
	
	return (best);
}

int main()
{
	size_t arr[] = {6, 12, 3, 5, 1, 4, 9, 2, 11};
	size_t size = sizeof(arr) / sizeof(size_t);
	struct bursa best = {0};

	best = Bursa(arr, size);

	printf("%ld\n", best.profit);
	printf("%ld\n", best.best_i);
	printf("%ld\n", best.profit_i);

	return 0;
}
