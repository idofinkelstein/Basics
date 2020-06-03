/*********************
File name: bit_array_test.c
Author: Ido finkelsein
Reviewer: Uriel Naiman
Date: 2/6/2020
**********************/

#include <stdio.h>  /* printf */
#include <stdlib.h> /* size_t */
#include "ilrd_bit_array.h"

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
void InitBitLUT(void);
void InitMirrorLUT(void);

int main()
{
	InitBitLUT();
	InitMirrorLUT();
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
	char str[65] = {0};

	puts("*** testing  BitArrSetAll ***");

	BitArrToString(arr, str);

	printf("%s\n", str);

	arr = BitArrSetAll(arr);
	
	BitArrToString(arr, str);

	printf("%s\n", str);

	
	puts("");
}

void BitArrResetAllTest(void)
{
	bit_array_t arr = 4365;
	char str[65] = {0};

	puts("*** testing  BitArrResetAll ***");

	BitArrToString(arr, str);

	printf("%s\n", str);

	arr = BitArrResetAll(arr);

	BitArrToString(arr, str);

	printf("%s\n", str);
	puts("");
}

void BitArrSetOnTest(void)
{
	bit_array_t arr = 4365;
	char str[65] = {0};

	puts("*** testing  BitArrSetOn ***");

	BitArrToString(arr, str);

	printf("%s\n", str);

	arr = BitArrSetOn(arr, 50);

	BitArrToString(arr, str);

	printf("%s\n", str);

	puts("");
}

void BitArrSetOffTest(void)
{
	bit_array_t arr = 4365;
	char str[65] = {0};

	puts("*** testing  BitArrSetOff ***");

	BitArrToString(arr, str);

	printf("%s\n", str);

	arr = BitArrSetOff(arr, 4);

	BitArrToString(arr, str);

	printf("%s\n", str);

	puts("");
}

void BitArrSetBitTest(void)
{
	bit_array_t arr = 4365;
	char str[65] = {0};

	puts("*** testing  BitArrSetBit ***");

	BitArrToString(arr, str);

	printf("%s\n", str);

	arr = BitArrSetBit(arr, 17, 1);

	BitArrToString(arr, str);

	printf("%s\n", str);

	puts("");
}

void BitArrFlipTest(void)
{
	bit_array_t arr = 4365;
	char str[65] = {0};

	puts("*** testing  BitArrFlip ***");

	BitArrToString(arr, str);

	printf("%s\n", str);

	arr = BitArrFlip(arr, 2);

	BitArrToString(arr, str);

	printf("%s\n", str);

	puts("");
}

void BitArrIsOnTest(void)
{
	bit_array_t arr = 4365;
	char str[65] = {0};

	puts("*** testing  BitArrIsOn ***");

	BitArrToString(arr, str);

	printf("%s\n", str);

	arr = BitArrIsOn(arr, 1);

	BitArrToString(arr, str);

	printf("%ld\n", arr);

	puts("");
}

void BitArrIsOffTest(void)
{
	bit_array_t arr = 4365;
	char str[65] = {0};

	puts("*** testing  BitArrSetOff ***");

	BitArrToString(arr, str);

	printf("%s\n", str);

	arr = BitArrIsOff(arr, 1);

	printf("%ld\n", arr);
	puts("");
}

void BitArrRotRTest(void)
{
	bit_array_t arr = 4365;
	char str[65] = {0};

	puts("*** testing  BitArrRotR ***");

	BitArrToString(arr, str);

	printf("%s\n", str);

	arr = BitArrRotR(arr, 3);

	BitArrToString(arr, str);

	printf("%s\n", str);

	puts("");
}

void BitArrRotLTest(void)
{
	bit_array_t arr = 4365;
	char str[65] = {0};

	puts("*** testing  BitArrRotL ***");

	BitArrToString(arr, str);

	printf("%s\n", str);

	arr = BitArrRotL(arr, 129);

	BitArrToString(arr, str);

	printf("%s\n", str);

	puts("");
}

void BitArrCountOnTest(void)
{
	bit_array_t arr = ~0;
	char str[65] = {0};

	puts("*** testing  BitArrCountOn ***");

	BitArrToString(arr, str);

	printf("%s\n", str);

	printf("%ld\n", BitArrCountOn(arr));
	printf("%ld\n", BitArrCountOnLUT(arr));

	puts("");
}

void BitArrCountOffTest(void)
{
	bit_array_t arr = 4365;
	char str[65] = {0};

	puts("*** testing  BitArrCountOff ***");

	BitArrToString(arr, str);

	printf("%s\n", str);

	printf("%ld\n", BitArrCountOff(arr));

	puts("");
}

void BitArrMirrorTest(void)
{
	bit_array_t arr = 91243685657113095;
	bit_array_t arr2 = 91243685657113095;
	char str[65] = {0};

	puts("*** testing  BitArrMirror ***");

	BitArrToString(arr, str);
	printf("%s\n", str);

	arr = BitArrMirror(arr);
	arr2 = BitArrMirrorLUT(arr2);
	
	BitArrToString(arr, str);
	printf("%s\n", str);

	BitArrToString(arr2, str);
	printf("%s\n", str);
	
	puts("");
}

void BitArrToStringTest(void)
{
	char str[65] = {0};
	
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
