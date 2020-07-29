/**********************
File name: calculator_test.c
Author: Ido Finkelstein
Reviewer: Ori Barak
Date: 29/7/2020
***********************/

#include <stdio.h> /* printf */

#include "calculator.h"

int main()
{

	printf("6+2 = %f\n",Calculator("6+2"));
	printf("6-2 = %f\n",Calculator("6-2"));
	printf("6*2 = %f\n",Calculator("6*2"));
	printf("6/4 = %f\n",Calculator("6/4"));


	printf("2+2+3 = %f\n",Calculator("2+2+3"));
	printf("2-2+3 = %f\n",Calculator("2-2+3"));
	printf("2*2+3 = %f\n",Calculator("2*2+3"));
	printf("2/2+3 = %f\n",Calculator("2/2+3"));

	printf("4*5/2+6/3 = %f\n",Calculator("4*5/2+6/3"));
	printf("(4*5/2+6)/3 = %f\n",Calculator("(4*5/2+6)/3"));
	printf("(4*5/2+5)/3 = %f\n",Calculator("(4*5/2+5)/3"));

	printf("(4*5/2+5)/((3+2-4)/(8+9))*(4+2) = %f\n",Calculator("(4*5/2+5)/((3+2-4)/(8+9))*(4+2)"));	

	printf("(4*5/2+5)/((3+2-4)/(8+9))*(4+2)/(4*5/2+5)/3 = %f\n",
		   Calculator("(4*5/2+5)/((3+2-4)/(8+9))*(4+2)/(4*5/2+5)/3"));	

	return 0;
}
