/****************
file name: ws3_flav.c
author: Ido Finkelstein
reviewer: Reut Ben Harush
date: 12.5.2020
*****************/

#include <stdlib.h> /* printf */
#include <stdio.h>  /* malloc, free */

void InitArray(int arr[], unsigned n)
{
	size_t i =  0;

	for (i = 0; i < n; ++i)
	{
		arr[i] = 1;
	}	
}

void PrintArray(int arr[], unsigned n)
{
	size_t i =  0;

	for (i = 0; i < n; ++i)
	{
		printf("%d ", arr[i]);
	}

	puts("");	
}


/* the function kill checks for the last standing man and changes the value
   of the pointer *winner */
int Kill(int arr[], unsigned n, int servivors, int *kill, int *winner)
{
	size_t i = 0;
	
	while (i < n)
	{
		if (*kill == 1)
		{			
			
			if(arr[i] == 1)
			{
				
				*kill = 0;
				*winner = i;

				if(i == n - 1)
				{	
					break;
				}

				++i;
				
			}
			else
			{
				if(i == n - 1)
				{	
					break;
				}

				++i;
			}
		}

		if (*kill == 0)
		{
			if(arr[i] == 0)
			{
				if(i == n - 1)
				{	
					break;
				}

				++i;
			}
			else
			{
				*kill = 1;
				arr[i] = 0;
				
				--servivors;

				if(i == n - 1)
				{
					break;
				}

				++i;
			}
		}
	}

	
	return (servivors);
}

int Flav(unsigned n)
{
	int servivors = n; /* for knowing how many servivors left each round */
	int *arr = (int*) malloc(n * sizeof(int));
	int kill = 1; /* kill flag */
	int *ptr_kill = &kill; /* *kill pointer to send to function each iteration */
	int winner = 0; /* this is winning man */
	int *ptr_winner = &winner; /* also being sent to function each iteration */

	if (NULL == arr)
	{
		return (0);
	}	

	InitArray(arr, n);

	PrintArray(arr,n);

	while (servivors > 1)
	{
		servivors = Kill(arr, n, servivors, ptr_kill, ptr_winner);
		PrintArray(arr,n);
	}

	printf("the winner is: %d\n", *ptr_winner);
	
	free(arr);

	return (0);
}


