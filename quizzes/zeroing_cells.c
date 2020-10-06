#include <stdio.h>
#include <stdlib.h>

void ZeroingCells(int (*arr)[], size_t rows, size_t cols)
{
	int (*zeros)[] = malloc(sizeof(int) * rows * cols);
	size_t i = 0;
	size_t j = 0;

	for (i = 0; i < rows * cols; ++i)
	{
		*(*zeros + i) = *(*arr + i);
	}

	for (i = 0; i < rows * cols; ++i)
	{
		
		printf("%d, ", *(*zeros + i));

	}

	puts("");

	free(zeros);
}


int main()
{
	size_t rows = 6;
	size_t cols = 7;
	size_t i = 0;
	size_t j = 0;
	int arr[6][7] = 
	{	{1, 2, 1, 3, 0, 2, 0},
		{8, 2, 9, 1, 4, 5, 7},
		{1, 1, 1, 1, 1, 1, 1},
		{2, 2, 2, 2, 2, 2, 3},
		{5, 6, 4, 6, 5, 4, 4},
		{7, 0, 4, 3, 2, 1, 8}
	};

	for (i = 0; i < rows; ++i)
	{
		for (j = 0; j < cols; ++j)
		{
			printf("%d, ", arr[i][j]);
		}

		puts("");
	}

	puts("");

	ZeroingCells(arr, rows, cols);

	return 0;
}
