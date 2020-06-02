/*********************
File name: bit_array.c
Author: Ido finkelsein
Reviewer: Uriel Naiman
Date: 2/6/2020
**********************/

#include <stddef.h> /* size_t */

#define NUM_OF_BIT (sizeof(size_t) * 8)
#define WORD_SIZE sizeof(size_t)

typedef size_t bit_array_t; 

bit_array_t BitArrSetAll(bit_array_t arr)
{
	return (arr = ~0);
}

bit_array_t BitArrResetAll(bit_array_t arr)
{
	return (arr = 0);
}

bit_array_t BitArrSetOn(bit_array_t arr, size_t index)
{
	return(arr | ((size_t)1 << (index - 1)));
}

bit_array_t BitArrSetOff(bit_array_t arr, size_t index)
{
	return(arr & (~((size_t)1 << (index - 1))));
}

bit_array_t BitArrSetBit(bit_array_t arr, size_t index, int boolean_value)
{
	return(boolean_value ? BitArrSetOn(arr, index) : BitArrSetOff(arr, index));
}

bit_array_t BitArrFlip(bit_array_t arr, size_t index)
{
	return (arr ^ ((size_t)1 << (index - 1)));
}

int BitArrIsOn(bit_array_t arr, size_t index)
{
	return (!!(arr & ((size_t)1 << (index - 1))));
}

int BitArrIsOff(bit_array_t arr, size_t index)
{
	return (!(arr & ((size_t)1 << (index - 1))));
}

bit_array_t BitArrRotR(bit_array_t arr, size_t num_to_shift)
{
	if (num_to_shift >= NUM_OF_BIT)
	{
		num_to_shift %= NUM_OF_BIT;
	}

	return((arr >> num_to_shift) | (arr << (NUM_OF_BIT - num_to_shift)));
}

bit_array_t BitArrRotL(bit_array_t arr, size_t num_to_shift)
{
	if (num_to_shift >= NUM_OF_BIT)
	{
		num_to_shift %= NUM_OF_BIT;
	}

	return((arr << num_to_shift) | (arr >> (NUM_OF_BIT - num_to_shift)));
}

size_t BitArrCountOn(bit_array_t arr)
{
	size_t on_bits = 0;
	
	for(; arr; arr &= (arr - 1))
	{
		++on_bits;
	}
	
	return(on_bits);
}

size_t BitArrCountOff(bit_array_t arr)
{
	size_t on_bits = 0;
	
	for(; arr; arr &= (arr - 1))
	{
		++on_bits;
	}
	
	return(NUM_OF_BIT - on_bits);
}

bit_array_t BitArrMirror(bit_array_t arr)
{
	if(8 == sizeof(size_t))
	{
		arr = (arr >> 32) | (arr << 32);
	
		arr = (((arr & 0x0000FFFF0000FFFF) << 16)) | (((arr & 0xFFFF0000FFFF0000) >> 16));

		arr = (((arr & 0x00FF00FF00FF00FF) << 8)) | (((arr & 0xFF00FF00FF00FF00) >> 8));

		arr = (((arr & 0x0F0F0F0F0F0F0F0F) << 4)) | (((arr & 0xF0F0F0F0F0F0F0F0) >> 4));

		arr = (((arr & 0x3333333333333333) << 2)) | (((arr & 0xCCCCCCCCCCCCCCCC) >> 2));

		arr = (((arr & 0x5555555555555555) << 1)) | (((arr & 0xAAAAAAAAAAAAAAAA) >> 1));
	}
	else
	{
		arr = ((arr << 16) | (arr >> 16));

		arr = (((arr & 0x00FF00FF) << 8)) | (((arr & 0xFF00FF00) >> 8));

		arr = (((arr & 0x0F0F0F0F) << 4)) | (((arr & 0xF0F0F0F0) >> 4));

		arr = (((arr & 0x33333333) << 2)) | (((arr & 0xCCCCCCCC) >> 2));

		arr = (((arr & 0x55555555) << 1)) | (((arr & 0xAAAAAAAA) >> 1));
	}
	
	return (arr);
}

char *BitArrToString(bit_array_t arr, char *dest)
{
	char *curr = dest;

	*(size_t*)dest = arr;

	/* increments curr 1 place beyond last byte */
	curr += WORD_SIZE;

	*curr = '\0';

	return(dest);
}
