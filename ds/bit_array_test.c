/*********************
File name: bit_array_test.c
Author: Ido finkelsein
Reviewer: Uriel Naiman
Date: 2/6/2020
**********************/

#include <stdio.h>
#include <stdlib.h>
#include "bit_array.h"

#define MAX_SHIFT (sizeof(size_t) * 8 - 1)

/* testing function declarations */
void BitArrSetAllTest(void);
void BitArrResetAllTest(void); 
void BitArrSetOnTest(void);
void BitArrSetOffTest(void);
void BitArrSetBitTest(void);
void BitArrFlipTest(void);
void BitArrIsOnTest(void);
void BitArrIsOffTest(void);
void BitArrRotRTest(void);
void BitArrRotLTest(void);
void BitArrCountOnTest(void);
void BitArrCountOnLUTTest(void);
void BitArrCountOffTest(void);
void BitArrMirrorTest(void);
void BitArrMirrorLUTTest(void);
void BitArrToStringTest(void);
void PrintBit(size_t num);

int main()
{
	InitLUT();
	BitArrSetAllTest();
	BitArrResetAllTest();
	BitArrSetOnTest();
	BitArrSetOffTest();
	BitArrSetBitTest();
	BitArrFlipTest();
	BitArrIsOnTest();
	BitArrIsOffTest();
	BitArrRotRTest();
	BitArrRotLTest();
	BitArrCountOnTest();
	BitArrCountOffTest();
	BitArrMirrorTest();
	BitArrToStringTest();

	return 0;
}

void BitArrSetAllTest(void)
{
	bit_array_t arr = 4365;

	puts("*** testing  BitArrSetAll ***");

	PrintBit(arr);

	arr = BitArrSetAll(arr);

	PrintBit(arr);
	puts("");
}

void BitArrResetAllTest(void)
{
	bit_array_t arr = 4365;

	puts("*** testing  BitArrResetAll ***");

	PrintBit(arr);

	arr = BitArrResetAll(arr);

	PrintBit(arr);
	puts("");
}

void BitArrSetOnTest(void)
{
	bit_array_t arr = 4365;

	puts("*** testing  BitArrSetOn ***");

	PrintBit(arr);

	arr = BitArrSetOn(arr, 50);

	PrintBit(arr);
	puts("");
}

void BitArrSetOffTest(void)
{
	bit_array_t arr = 4365;

	puts("*** testing  BitArrSetOff ***");

	PrintBit(arr);

	arr = BitArrSetOff(arr, 4);

	PrintBit(arr);
	puts("");
}

void BitArrSetBitTest(void)
{
	bit_array_t arr = 4365;

	puts("*** testing  BitArrSetBit ***");

	PrintBit(arr);

	arr = BitArrSetBit(arr, 4, 1);

	PrintBit(arr);
	puts("");
}

void BitArrFlipTest(void)
{
	bit_array_t arr = 4365;

	puts("*** testing  BitArrFlip ***");

	PrintBit(arr);

	arr = BitArrFlip(arr, 2);

	PrintBit(arr);
	puts("");
}

void BitArrIsOnTest(void)
{
	bit_array_t arr = 4365;

	puts("*** testing  BitArrIsOn ***");

	PrintBit(arr);

	arr = BitArrIsOn(arr, 1);

	printf("%ld\n", arr);
	puts("");
}

void BitArrIsOffTest(void)
{
	bit_array_t arr = 4365;

	puts("*** testing  BitArrSetOff ***");

	PrintBit(arr);

	arr = BitArrIsOff(arr, 1);

	printf("%ld\n", arr);
	puts("");
}

void BitArrRotRTest(void)
{
	bit_array_t arr = 4365;

	puts("*** testing  BitArrRotR ***");

	PrintBit(arr);

	arr = BitArrRotR(arr, 3);

	PrintBit(arr);
	puts("");
}

void BitArrRotLTest(void)
{
	bit_array_t arr = 4365;

	puts("*** testing  BitArrRotL ***");

	PrintBit(arr);

	arr = BitArrRotL(arr, 129);

	PrintBit(arr);
	puts("");
}

void BitArrCountOnTest(void)
{
	bit_array_t arr = ~0;

	puts("*** testing  BitArrCountOn ***");

	PrintBit(arr);

	printf("%ld\n", BitArrCountOn(arr));
	printf("%ld\n", BitArrCountOnLUT(arr));
	puts("");
}

void BitArrCountOffTest(void)
{
	bit_array_t arr = 4365;

	puts("*** testing  BitArrCountOff ***");

	PrintBit(arr);

	printf("%ld\n", BitArrCountOff(arr));
	puts("");
}

void BitArrMirrorTest(void)
{
	bit_array_t arr = 4365;

	puts("*** testing  BitArrMirror ***");

	PrintBit(arr);

	arr = BitArrMirror(arr);

	PrintBit(arr);
	puts("");
}

void BitArrToStringTest(void)
{
	char str[9] = {0};
	
	bit_array_t arr = 0x796B6E69466F6449;

	puts("*** testing  BitArrToString ***");

	PrintBit(arr);

	BitArrToString(arr, str);

	printf("%s\n", str);
	puts("");
}

void PrintBit(bit_array_t num)
{
	size_t mask = (size_t)1 << MAX_SHIFT;

	while (mask)
	{
		printf("%d", !!(mask & num)); 
		
		mask >>= 1;
	}

	puts("");
}
