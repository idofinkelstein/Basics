/**********************
file name: ws6.h
author: Ido Finkelstein
reviewer: Inbal Elmalech
date: 19/5/2020
***********************/

#ifndef __WS6_H__
#define __WS6_H__

/*raises x to the power of 2^y */
unsigned long Pow2(unsigned int x, unsigned int y);

/*raises x to the power of 2^y */
unsigned long PowTwo(unsigned int x, unsigned int y);

/*checks if num is a power of two */
int IsPowerOf2(unsigned int num);

/*checks if num is a power of two without a loop */
int IsPowerOf2NoLoop(unsigned int num);

/* adds one to number */
int Add1(int num);

/* recieves an array and print out the numbers contain 3 only bits */ 
void HasOnly3Bits(unsigned int* arr, int size);

/* checks if second and sixth bits are on */
int Are2And6On(char c);

/* checks if second or sixth bits are on */
int Are2Or6On(unsigned char c);

/* returns a mirror image of a char */
unsigned char ByteMirror(unsigned char ch);

/* returns the closest divisible by 16 to num */
unsigned int NearestDivisibleBy16(unsigned int num);

/* counts the bits in num */
void BitCounter(int num);

void FloatBitCounter(float num);

unsigned CharBitCount(char ch);

int swapBits(unsigned int x); 

void SwapVariables(int *num1, int *num2);

#endif /* __WS6_H__ */
