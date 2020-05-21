/**********************
file name: ws6.c
author: Ido Finkelstein
reviewer: Inbal Elmalech
date: 19/5/2020
***********************/

#include <stdio.h> /* printf */

#define TRUE 1
#define FALSE 0 

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

/* computes the value of x * (2 ^ y) and returns the result (the hard way) */
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

/* computes the value of x * (2 ^ y) and returns the result (the easy way) */
long PowTwo(unsigned int x, unsigned int y)
{
	return (x << y);
}

int IsPowerOf2(unsigned int num)
{
	unsigned int one = 1;
	unsigned int bit_count = 0;
	
	/* this loop compares the LSB of num and 1,
	   if there is more than 1 match num is not power of two */
	while (num && 2 > bit_count)
	{			
		bit_count += num & one;		
		
		num >>= 1;
	}

	return (bit_count == one);	
}

int IsPowerOf2NoLoop(unsigned int num)
{
	if(0 == num)
	{
		return 0;
	}
	
	return (num == (num & (~num + 1))); /* equivalent to ~(n - 1) */
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

		while (0 < num_to_check && 4 > is_contain_3_bits)
		{
			is_contain_3_bits += num_to_check & one;
									
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
	unsigned char two_and_six_are_on = 34; /* 00100010 */
	unsigned char answer = 0;

	answer = c & two_and_six_are_on;

	return (answer == two_and_six_are_on);	
}

/* checks if 2 or 6 bit are set */
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

unsigned char ByteMirror(unsigned char ch)
{
	unsigned char msb = 128;
	unsigned char mirror_char = 0;
	unsigned tmp_bit = 0;
	int len_of_byte = 8;
	int i = 0;

	for (i = 1; i < len_of_byte; ++i)
	{
		tmp_bit = ch & msb;

		mirror_char =  mirror_char ^ tmp_bit;

		ch <<= 1;

		mirror_char >>= 1;
	}
	
	return (mirror_char);

}

unsigned int NearestDivisibleBy16(unsigned int num)
{
	unsigned int msb = 0x80000000;	

	if(16 > num)
	{
		return (FALSE);
	}

	while (!(msb & num))
	{
		msb >>= 1;
	}
		
	return (msb);

}

void BitCounter(unsigned int num)
{
	int bit_count = 0;
	unsigned int lsb = 1;

	while (num)
	{
		bit_count += lsb & num;

		num >>= 1;
	}

	printf("nuber of set bits = %d\n", bit_count);
}


void FloatBitCounter(float num)
{
	unsigned bit_count = 0;
	unsigned *f_ptr = (unsigned*)&num; /* look at the at the address as it is an 										  int address */
	unsigned mask = 1<<31;
	unsigned dup = *f_ptr;
	/**/	
	
	while(mask)
	{
		bit_count += (dup & mask) / mask;
		printf("%d, ", (dup & mask) / mask);

		mask >>=1;
	}

	printf("nuber of set bits = %u\n", bit_count);
}

void SwapVariables(int *num1, int *num2)
{
	*num1 = *num1 ^ *num2;
	*num2 = *num1 ^ *num2;
	*num1 = *num1 ^ *num2;
}

int swapBits(unsigned int x) 
{ 
	int mid = 0;
    unsigned int set1 =  1 << 2; 
    unsigned int set2 =  1 << 4; 
    unsigned int xor = 0; 
	unsigned int result= 0;
	
	/* take the 3rd and fifth bit */
	set1 = set1 & x;
	set2 = set2 & x;

	/* put them together */
	mid = set1 | set2;
	
	/* swap the positions of them*/ 
	set2 = set2 >> 2;
	set1 = set1 << 2;
    
	/* put the swap bits together and xor them with the originals */
    xor = set1 | set2;
	xor = xor ^ mid; 

	/* xor x with the xored bits */  
    result = x ^ xor; 
  
    return result; 
}

