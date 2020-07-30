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
	float f = 0;

	printf("6+2 = %f\n",Calculator("6+2"));
	printf("6-2 = %f\n",Calculator("6-2"));
	printf("6*2 = %f\n",Calculator("6*2"));
	printf("6/4 = %f\n",Calculator("6/4"));

	printf("17-22 = %f\n",Calculator("17-22"));
	printf("17-22/2-12 = %f\n",Calculator("17-22/2-12"));
	printf("17-11-12 = %f\n",Calculator("17-11-12"));


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

	printf("(4*5/2+5)+((3+2-4)/(8+9))*(4+2)/(4*5/2+5)/3-5-6-1*4*2+1+1-2*(4/3/2*4*(1+1+1-5-0.5))*3 = %f\n",
		   Calculator("(4*5/2+5)+((3+2-4)/(8+9))*(4+2)/(4*5/2+5)/3-5-6-1*4*2+1+1-2*(4/3/2*4*(1+1+1-5-0.5))*3"));

	f = ((float)4*5/2+(float)5)+(((float)3+2-4)/((float)8+9))*((float)4+2)/((float)4*5/2+5)
		/(float)3-5-6-1*4*2+1+1-2*((float)4/3/2*4*((float)1+1+1-5-0.5))*(float)3;

	printf("compiler result for last expression: %f\n", f);

	return 0;
}
