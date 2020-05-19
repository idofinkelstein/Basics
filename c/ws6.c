/**********************
file name: ws6.c
author: Ido Finkelstein
reviewer: Inbal Elmalech
date: 19/5/2020
***********************/

#include <stdio.h> /* printf */

/* assistant function for adding */
long Add(unsigned int x, unsigned int y)
{
	unsigned int result = y;
	unsigned int carry = x;
		
	/* x + y */
	while (carry != 0)
	{
		carry = carry & result;

		result = x ^ result;

		carry <<= 1;

		x = carry;	
	}

	return (result);
}

/* computes the value of x * (2 ^ y) and returns the result */
long Pow2(unsigned int x, unsigned int y)
{
	unsigned int result = 2;
	unsigned int stop = y;
	unsigned int i = 0;
	
	if (x == 0)
	{
		return 0;
	}
	if (0 == y)
	{
		return x;
	}
	
	/* 2 ^ y */ 
	for (i = 1; i < stop; ++i)
	{
		result = Add(result, result);
	}
	printf("(2 ^ %d) = %d\n", y, result);	
	
	stop = result;
	result = x;	
	
	/* x * y */
	for (i = 1; i < stop; ++i)
	{
		result = Add(x, result);
	}
	
	return (result);
}

int IsPowerOf2(unsigned int num)
{
	unsigned int one = 1;
	int is_pow_of_two = 0;
	
	if (0 == num)
	{
		return 0;
	}
	
	/* this loop compares the LSB of num and 1,
	   if there is more than 1 match num is not power of two */
	while (0 < num)
	{
		if (one == (num & one))
		{
			++is_pow_of_two;
			
			
			
			if (1 < is_pow_of_two)
			{
				return 0;
			}
		}

		num >>= 1;
	}

	return 1;	
}

/* adds 1 */
int Add1(int num)
{
	int carry = num;
	int result = 1;
	
	/* x + 1 */
	while (carry != 0)
	{
		carry = carry & result;

		result = result ^ num;

		carry <<= 1;

		num = carry;	
	}

	return (result);
}

/* checks if array elment has only 3 bits on */
void HasOnly3Bits(unsigned int* arr, int size)
{
	int i = 0;
	unsigned int one = 1;
	int three_bits = 3;
	int is_contain_3_bits = 0;
	unsigned int num_to_check = 0;

	for (i = 0; i < size; ++i)
	{
		num_to_check = arr[i];

		while (0 < num_to_check)
		{
			if (one == (num_to_check & one))
			{
				++is_contain_3_bits;
			}	
						
			num_to_check >>= 1;			
		}

		if (is_contain_3_bits == three_bits)
			{
				printf("%d, ", arr[i]);
			}

		is_contain_3_bits = 0;
	}
		
	printf("\n");
}

/* checks if 2 and 6 bit are set */
int Are2And6On(unsigned char c)
{
	unsigned char two_and_six_are_on = 34;
	unsigned char answer = 0;

	answer = c & two_and_six_are_on;

	return (answer == two_and_six_are_on);	
}

int Are2Or6On(unsigned char c)
{
	unsigned char two_and_six_are_on = 34;
	unsigned char six_is_on = 32;
	unsigned char two_is_on = 2;	
	unsigned char answer = 0;

	answer = c & two_and_six_are_on;

	answer = answer & six_is_on || answer & two_is_on;

	return (answer);	
}
/*
int SwapBit3And5(unsigned char c)
{
	unsigned char bit3 = 4;
	unsigned char bit5 = 16;
	unsigned char swap3 = 0;
	unsigned char swap5 = 0;

	swap3 = bit5 & 
}
*/
