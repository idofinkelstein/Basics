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
	return ((long)x << y);
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
	return (num && num == (num & (~num + 1))); /* equivalent to ~(n - 1) */
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
	unsigned char mask2_6 = 0x22; /* 00100010 */
	
	return (mask2_6 == (c & mask2_6));	
}

/* checks if 2 or 6 bit are set */
int Are2Or6On(unsigned char c)
{
	unsigned char mask6 = 0x20;
	unsigned char mask2 = 0x2;	

	return (c & mask6 || c & mask2);	
}

unsigned char ByteMirror(unsigned char ch)
{
	unsigned char msb = 0x80;
	unsigned char mirror_char = 0;
	int len_of_byte = 8;
	int i = 0;

	for (i = 0; i < len_of_byte; ++i)
	{
		mirror_char >>= 1;

		mirror_char ^= (ch & msb);

		ch <<= 1;
	}
	
	return (mirror_char);
}

unsigned int NearestDivisibleBy16(unsigned int num)
{	
	return (num & ~0xF);
}

void BitCounter(unsigned int num)
{
	int bit_count = 0;
	
	for(; num; num &= (num - 1))
	{
		++bit_count;
		
	}

	printf("nuber of set bits = %d\n", bit_count);
}

void FloatBitCounter(float num)
{
	unsigned bit_count = 0;
	unsigned *f_ptr = (unsigned*)&num; /* look at the at the address as it is an 										  int address */
	unsigned mask = 0x80000000;
	unsigned dup = *f_ptr;	
	
	while(mask)
	{
		bit_count += !!(dup & mask);
		printf("%d, ", !!(dup & mask));

		mask >>= 1;
	}

	printf("\nnuber of set bits = %u\n", bit_count);
}

void SwapVariables(int *num1, int *num2)
{
	*num1 = *num1 ^ *num2;
	*num2 = *num1 ^ *num2;
	*num1 = *num1 ^ *num2;
}

int swapBits(unsigned int x) 
{ 
    unsigned int mask3 = 0x4 & x; 
    unsigned int mask5 = 0x10 & x;  
	
    x = x ^ ((mask3 | mask5) ^ ((mask3 << 2) | (mask5 >> 2)));
	 
    return x; 
}

unsigned CountBitsNoLoop(unsigned char num)
{
	return (!!(1 & num) + !!(2 & num) + !!(4 & num) + !!(8 & num)
			+ !!(16 & num) + !!(32 & num) + !!(64 & num) + !!(128 & num));
}

unsigned char ByteMirrorV2(unsigned char ch)
{
	unsigned char mask_l = 0x80;
	unsigned char mask_r = 0x1;
	unsigned char move_mask = 7;

	while (mask_r < mask_l)
	{
		ch ^= (((mask_l | mask_r) & ch) ^ ((((mask_l & ch) >> move_mask) |
			 				               ((mask_r & ch) << move_mask))));
		mask_r <<= 1;
		mask_l >>= 1;
		move_mask -= 2;
	}
	
	return (ch);
}

unsigned char ByteMirrorNoLoop(unsigned char ch)
{
	ch = (ch >> 4) | (ch << 4);

	ch = (((ch & 0x33) << 2)) | (((ch & 0xcc) >> 2));

	ch = (((ch & 0x55) << 1)) | (((ch & 0xaa) >> 1));
	
	return (ch);
}

void BitCountNoLoop(unsigned num) 
{
    num = num - ((num >> 1) & 0x55555555);
    num = (num & 0x33333333) + ((num >> 2) & 0x33333333);
    num = (num + (num >> 4)) & 0x0f0f0f0f;
    num = num + (num >> 8);
    num = num + (num >> 16);
	num = num & 0x3f;

	printf("nuber of set bits = %d\n", num);
    
}
