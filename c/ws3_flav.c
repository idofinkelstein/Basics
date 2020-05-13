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

/* The function kill checks for the last standing man and changes the value
   of the varible winner:
   If i just killed someone, i jump to the next one, kill flag is raised and
   there are 2 options, if next one is dead, jump to the next one, if he is 
   alive turn off the flag and jump to the next one,
   now when the flag is down there are also 2 options, if the next man is dead
   jump to the next one, if he is alive kill him raise the flag and jump to the
   next one. we do this until we have 1 servivor left.

   To know the position of the winner the varible winner saves the index of i
   in the position of the man how is giong to do the next kill.*/

int Kill(int arr[], unsigned n)
{
	size_t i = 0;
	int kill = 1; /* killing flag */
	int winner = 0;
	unsigned servivors = n;
	
	
	while (servivors > 1)
	{
		if (kill == 1)
		{					
			if(arr[i] == 1)
			{		
				kill = 0;
				winner = i;
			}

			i = (i + 1) % n;
		}

		if (kill == 0)
		{
			if(arr[i] == 1)
			{
				kill = 1;
				arr[i] = 0;
				
				--servivors;
			}

			i = (i + 1) % n;
		}
	}

	return (winner);
}

int Flav(unsigned n)
{
	int *arr = (int*) malloc(n * sizeof(int));	
	int winner = 0; /* this is the winning man */
	 
	if (NULL == arr)
	{
		return (0);
	}	

	InitArray(arr, n);

	winner = Kill(arr, n);

	printf("the winner for %d worriors is: %d (%d)\n", n, winner, winner + 1);
	
	free(arr);

	return (0);
}


