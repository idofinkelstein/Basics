#include <setjmp.h>

#include "knights_tour_hiuristic.h"



int main()
{
	int i = 0;
	int j = 0;
	int size = 8;

	for (i = 0; i < size; ++i)
	{
		for (j = 0; j < size; ++j)
		{
			KnightTour(i, j);		
			
		}
	
	
	}
		
	
	return (0);
}
