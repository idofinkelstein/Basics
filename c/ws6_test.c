/**********************
file name: ws6_test.c
author: Ido Finkelstein
reviewer: Inbal Elmalech
date:19/5/2020
***********************/

#include <stdio.h>	/* printf */
#include <limits.h> /* MIN_INT */
#include "ws6.h"

static void Pow2Test(void);
static void PowTwoTest(void);
static void IsPowerOf2Test(void);
static void IsPowerOf2NoLoopTest(void);
static void Add1Test(void);
static void HasOnly3BitsTest(void);
static void Are2And6OnTest(void);
static void Are2Or6OnTest(void);
static void ByteMirrorTest(void);
static void NearestDivisibleBy16Test(void);
static void FloatBitCounterTest(void);
static void BitCounterTest(void);
static void swapBitsTest(void);
static void SwapVariablesTest(void);
static void CountBitsNoLoopTest(void);

int main()
{
	Pow2Test();
	PowTwoTest();
	IsPowerOf2Test();
	IsPowerOf2NoLoopTest();
	Add1Test();
	HasOnly3BitsTest();
	Are2And6OnTest();
	Are2Or6OnTest();
	ByteMirrorTest();
	NearestDivisibleBy16Test();
	BitCounterTest();
	FloatBitCounterTest();
	swapBitsTest();
	SwapVariablesTest();
	CountBitsNoLoopTest();

	return 0;
}

static void Pow2Test(void)
{
	unsigned int a = 5;
	unsigned int b = 6;

	printf("%d * (2 ^ %d) = %ld\n", a, b, Pow2(a, b));
}

static void PowTwoTest(void)
{
	unsigned int a = 5;
	unsigned int b = 6;

	printf("%d * (2 ^ %d) = %ld\n", a, b, PowTwo(a, b));
}

static void IsPowerOf2Test(void)
{	
	unsigned int num = 0;
	
	for(num = 0; num < 20; ++num)
	{
		printf("is %d power of two? (with loop) %d\n", num, IsPowerOf2(num)); 
	}
}

static void IsPowerOf2NoLoopTest(void)
{
	unsigned int num = 0;
	
	for(num = 0; num < 20; ++num)
	{
		printf("is %d power of two? (without loop) %d\n", num, IsPowerOf2NoLoop(num)); 
	}
}


static void Add1Test(void)
{
	int num = INT_MIN;

	printf("%d + 1 = %d\n", num, Add1(num));
}

static void HasOnly3BitsTest(void)
{
			 		  /* {1111010, 111, 101, 1000010001, 1100101, 1000000010000001} */
	unsigned int arr[] = {122,     7,   5,   529,        101,     32897    };
	int size = sizeof(arr) / sizeof(int);
	
	HasOnly3Bits(arr, size);
}

static void Are2And6OnTest(void)
{
	unsigned char ch = 171;

	printf("%d\n", Are2And6On(ch));
}

static void Are2Or6OnTest(void)
{
	unsigned char ch = 15;

	printf("%d: %d\n", ch, Are2Or6On(ch));
}

static void ByteMirrorTest(void)
{
	unsigned char ch = 123;

	printf("%d is now %d\n", ch, ByteMirror(ch));

	printf("%d is now %d\n", ch, ByteMirrorV2(ch));

	printf("%d is now %d\n", ch, ByteMirrorNoLoop(ch));
}

static void NearestDivisibleBy16Test(void)
{
	unsigned int num = 0;
	
	for(num = 10; num < 66 ; ++num)
	{
		printf("%d, ", NearestDivisibleBy16(num)); 
	}

	printf("\n");
}

static void FloatBitCounterTest(void)
{
	float num = 8.5;

	FloatBitCounter(num);
}

static void BitCounterTest(void)
{
	unsigned int num = 15475;

	printf("%d has -> ", num);
	BitCounter(num);
	printf("%d has -> ", num);
	BitCountNoLoop(num);
}

static void swapBitsTest(void)
{
	int num = 171;
	
	printf("%d now become %d\n", num, swapBits(num));
}

static void SwapVariablesTest(void)
{
	int a = 12;
	int b = 25;

	printf("a = %d, b = %d\n", a, b);

	SwapVariables(&a, &b);

	printf("a = %d, b = %d\n", a, b);
}

static void CountBitsNoLoopTest(void)
{
	unsigned char num = 222;

	printf("%d has %d set bits\n", num, CountBitsNoLoop(num));
}


