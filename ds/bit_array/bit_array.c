/*********************
File name: bit_array.c
Author: Ido finkelsein
Reviewer: Uriel Naiman
Date: 2/6/2020
**********************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#define NUM_OF_BIT (sizeof(size_t) * 8)
#define WORD_SIZE sizeof(size_t)
#define CHAR_VALS 256
#define MAX_SHIFT (sizeof(size_t) * 8 - 1)

static char bit_lut_g[CHAR_VALS] = {0};
static unsigned char mirror_lut_g[CHAR_VALS] = {0};

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
	assert(index >= 1 && index <= 64);

	return (arr | ((size_t)1 << (index - 1)));
}

bit_array_t BitArrSetOff(bit_array_t arr, size_t index)
{
	assert(index >= 1 && index <= 64);
	
	return (arr & (~((size_t)1 << (index - 1))));
}

bit_array_t BitArrSetBit(bit_array_t arr, size_t index, int boolean_value)
{
	assert(index >= 1 && index <= 64);

	return(boolean_value ? BitArrSetOn(arr, index) : BitArrSetOff(arr, index));
}

bit_array_t BitArrFlip(bit_array_t arr, size_t index)
{
	return (arr ^ ((size_t)1 << (index - 1)));
}

int BitArrIsOn(bit_array_t arr, size_t index)
{
	assert(index >= 1 && index <= 64);

	return (!!(arr & ((size_t)1 << (index - 1))));
}

int BitArrIsOff(bit_array_t arr, size_t index)
{
	assert(index >= 1 && index <= 64);

	return (!(arr & ((size_t)1 << (index - 1))));
}

bit_array_t BitArrRotR(bit_array_t arr, size_t num_to_shift)
{
	if (num_to_shift >= NUM_OF_BIT)
	{
		num_to_shift %= NUM_OF_BIT;
	}

	return ((arr >> num_to_shift) | (arr << (NUM_OF_BIT - num_to_shift)));
}

bit_array_t BitArrRotL(bit_array_t arr, size_t num_to_shift)
{
	if (num_to_shift >= NUM_OF_BIT)
	{
		num_to_shift %= NUM_OF_BIT;
	}

	return ((arr << num_to_shift) | (arr >> (NUM_OF_BIT - num_to_shift)));
}

size_t BitArrCountOn(bit_array_t arr)
{
	size_t m1  = 0x5555555555555555; /* binary: 0101... */
	size_t m2  = 0x3333333333333333; /* binary: 00110011.. */
	size_t m4  = 0x0F0F0F0F0F0F0F0F; /* binary:  4 zeros,  4 ones ... */
	size_t m8  = 0x00FF00FF00FF00FF; /* binary:  8 zeros,  8 ones ... */
	size_t m16 = 0x0000FFFF0000FFFF; /* binary: 16 zeros, 16 ones ... */
	size_t m32 = 0x00000000FFFFFFFF; /* binary: 32 zeros, 32 ones */

	arr = (arr & m1 ) + ((arr >>  1) & m1 ); 
    arr = (arr & m2 ) + ((arr >>  2) & m2 );  
    arr = (arr & m4 ) + ((arr >>  4) & m4 );  
    arr = (arr & m8 ) + ((arr >>  8) & m8 );  
    arr = (arr & m16) + ((arr >> 16) & m16);  
    arr = (arr & m32) + ((arr >> 32) & m32);

    return (arr);
}

size_t BitArrCountOff(bit_array_t arr)
{
	return (NUM_OF_BIT - BitArrCountOn(arr));
}

bit_array_t BitArrMirror(bit_array_t arr)
{
	if(8 == sizeof(size_t))
	{
		arr = (arr >> 32) | (arr << 32);
	
		arr = (((arr & 0x0000FFFF0000FFFF) << 16)) | 
			  (((arr & 0xFFFF0000FFFF0000) >> 16));

		arr = (((arr & 0x00FF00FF00FF00FF) << 8)) | 
			  (((arr & 0xFF00FF00FF00FF00) >> 8));

		arr = (((arr & 0x0F0F0F0F0F0F0F0F) << 4)) | 
			  (((arr & 0xF0F0F0F0F0F0F0F0) >> 4));

		arr = (((arr & 0x3333333333333333) << 2)) | 
			  (((arr & 0xCCCCCCCCCCCCCCCC) >> 2));

		arr = (((arr & 0x5555555555555555) << 1)) | 
			  (((arr & 0xAAAAAAAAAAAAAAAA) >> 1));
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
	size_t mask = (size_t)1 << MAX_SHIFT;

	while (mask)
	{
		*(curr++) = !!(mask & arr) + '0'; /* writes the current bit */
		
		mask >>= 1;
	}
	
	*curr = '\0';	

	return (dest);
}

size_t BitArrCountOnLUT(bit_array_t arr)
{
	size_t bits_on = 0;
	size_t i = 0;
	unsigned char *p_arr = (unsigned char*)&arr;
	
	for(i = 0; i < WORD_SIZE; ++i)
	{
		bits_on += bit_lut_g[*p_arr];

		++p_arr;
	}

	return (bits_on);
}


bit_array_t BitArrMirrorLUT(bit_array_t arr)
{
	bit_array_t mirror_arr = 0;
	unsigned char *curr_arr = (unsigned char*)&arr;
	unsigned char *curr_mirror = (unsigned char*)&mirror_arr + WORD_SIZE - 1;
	size_t i = 0;

	for (i = 0; i < WORD_SIZE; ++i)
	{
		*curr_mirror = mirror_lut_g[*curr_arr];

		++curr_arr;

		--curr_mirror;
	}

	return (mirror_arr);
}

void InitBitLUT(void)
{
	size_t num = 0;
	size_t i = 0;
	size_t on_bits = 0;

	for(i = 0; i < CHAR_VALS; ++i)
	{
		num = i;
		on_bits = 0;		

		for(; num; num &= (num - 1))
		{
			++on_bits;
		}

		bit_lut_g[i] = on_bits;
	}	
}

void InitMirrorLUT(void)
{
	size_t i = 0;
	unsigned char mirror_byte = 0;

	for(i = 0; i < CHAR_VALS; ++i)
	{
		mirror_byte = i;

		mirror_byte = (mirror_byte >> 4) | (mirror_byte << 4);

		mirror_byte = (((mirror_byte & 0x33) << 2)) | (((mirror_byte & 0xcc) >> 2));

		mirror_byte = (((mirror_byte & 0x55) << 1)) | (((mirror_byte & 0xaa) >> 1));

		mirror_lut_g[i] = mirror_byte;
	}
}
