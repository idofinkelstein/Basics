/**********************
Author: Ido Finkelstein
File name: ws9_test.c
Reviewer: Gal Shvinkelstein
Date: 31/5/2020
***********************/

#include <stdio.h>  /* printf                                */
#include <string.h> /* puts, strcpy, memcpy, memmove, memset */
#include <stdlib.h> /* malloc, free                          */
#include "ws9.h"

#define BUFF_SIZE 100
#define EXIT_IF_FAILED(COND, MSG, RET) if (COND) {puts(MSG); return (RET);}

static int MemSetTest(void);
static int memsetTest(void);
static int MemCpyTest(void);
static int memcpyTest(void);
static int MemMoveTest(void);
static int memmoveTest(void);
static int AtoiTest(void);
static int ItoaTest(void);
static void ThreeArraysTest(void);
static void EndianTest(void);

int main()
{
	MemSetTest();
	memsetTest();
	MemCpyTest();
	memcpyTest();
	MemMoveTest();
	memmoveTest();
	AtoiTest();
	ItoaTest();
	ThreeArraysTest();
	EndianTest();
	
	return 0;
}

static int MemSetTest(void)
{
	char *str1 = malloc(BUFF_SIZE * sizeof(char));	
	char *str2 = malloc(BUFF_SIZE * sizeof(char));

	EXIT_IF_FAILED(NULL == str1, "malloc failed", -1);
	EXIT_IF_FAILED(NULL == str2, "malloc failed", -1);

	MemSet(str1, 'b', 16);
	MemSet(str2 + 3, 'Z', 20);

	str1[16] = '\0';
	str2[20] = '\0';
	
	
	puts("*** Testing MemSet ***");
	printf("%s\n", str1);
	printf("%s\n", str2 + 3);

	free(str1);
	free(str2);

	return 0;
}

/* for comparing MemSet to memset */
static int memsetTest(void)
{
	char *str1 = malloc(BUFF_SIZE * sizeof(char));	
	char *str2 = malloc(BUFF_SIZE * sizeof(char));

	EXIT_IF_FAILED(NULL == str1, "malloc failed", -1);
	EXIT_IF_FAILED(NULL == str2, "malloc failed", -1);

	memset(str1, 'b', 16);
	memset(str2 + 3, 'Z', 20);

	str1[16] = '\0';
	str2[20] = '\0';
	
	
	puts("*** Testing memset ***");
	printf("%s\n", str1);
	printf("%s\n", str2 + 3);

	free(str1);
	free(str2);

	return 0;
}

static int MemCpyTest(void)
{
	char *str1 = malloc(BUFF_SIZE * sizeof(char));
	char *str2 = malloc(BUFF_SIZE * sizeof(char));
	int *arr1 = malloc(BUFF_SIZE * sizeof(int));
	int *arr2 = malloc(BUFF_SIZE * sizeof(int));
	int *arr3 = malloc(BUFF_SIZE * sizeof(int));
	int *ptr_arr3 = arr3;		
	size_t i = 0;

	EXIT_IF_FAILED(NULL == str1, "malloc failed", -1);
	EXIT_IF_FAILED(NULL == str2, "malloc failed", -1);
	EXIT_IF_FAILED(NULL == arr1, "malloc failed", -1);
	EXIT_IF_FAILED(NULL == arr2, "malloc failed", -1);
	EXIT_IF_FAILED(NULL == arr3, "malloc failed", -1);
	
	for (i =0; i < 30; ++i)
	{
		arr1[i] = i * i;	
	}

	strcpy(str1, "hello, world!!!");	
	
	/* tests string and array of ints */
	MemCpy(str2, str1, 22);
	MemCpy(arr2, arr1, 120);
	MemCpy(arr3 + 7, arr1, 120);	
	
	ptr_arr3 += 7;

	puts("*** Testing MemCpy ***");	
	printf("%s\n", str2);

	for (i =0; i < 30; ++i)
	{
		printf("%d ", arr2[i]);	
	}

	puts("");

	for (i =0; i < 30; ++i)
	{
		printf("%d ", ptr_arr3[i]);	
	}

	puts("");

	free(str1);
	free(str2);
	free(arr1);
	free(arr2);
	free(arr3);

	return 0;
}

/* for comparing MemCpy to memcpy */
static int memcpyTest(void)
{
	char *str1 = malloc(BUFF_SIZE * sizeof(char));
	char *str2 = malloc(BUFF_SIZE * sizeof(char));
	int *arr1 = malloc(BUFF_SIZE * sizeof(int));
	int *arr2 = malloc(BUFF_SIZE * sizeof(int));
	int *arr3 = malloc(BUFF_SIZE * sizeof(int));
	int *ptr_arr3 = arr3;		
	size_t i = 0;

	EXIT_IF_FAILED(NULL == str1, "malloc failed", -1);
	EXIT_IF_FAILED(NULL == str2, "malloc failed", -1);
	EXIT_IF_FAILED(NULL == arr1, "malloc failed", -1);
	EXIT_IF_FAILED(NULL == arr2, "malloc failed", -1);
	EXIT_IF_FAILED(NULL == arr3, "malloc failed", -1);
	
	for (i =0; i < 30; ++i)
	{
		arr1[i] = i * i;	
	}

	strcpy(str1, "hello, world!!!");	
	
	/* tests string and array of ints */
	memcpy(str2, str1, 22);
	memcpy(arr2, arr1, 120);
	memcpy(arr3 + 7, arr1, 120);	
	
	ptr_arr3 += 7;

	puts("*** Testing memcpy ***");	
	printf("%s\n", str2);

	for (i =0; i < 30; ++i)
	{
		printf("%d ", arr2[i]);	
	}

	puts("");

	for (i =0; i < 30; ++i)
	{
		printf("%d ", ptr_arr3[i]);	
	}

	puts("");

	free(str1);
	free(str2);
	free(arr1);
	free(arr2);
	free(arr3);

	return 0;
}

static int MemMoveTest(void)
{
	char *str1 = malloc(30 * sizeof(char));
	char *str2 = str1 + 5;
	char *str3 = str1;
	char *str4 = malloc(30 * sizeof(char));
	char *str5 = str4 + 6;

	EXIT_IF_FAILED(NULL == str1, "malloc failed", -1);
	EXIT_IF_FAILED(NULL == str2, "malloc failed", -1);

	MemSet(str1, '\0', 30);
	MemSet(str4, '\0', 30);

	strcpy(str1, "ABCDEFGHIJKLMNOP");
	strcpy(str4, "ABCDEFGHIJKLMNOP");

	/* dest < src */
	MemMove(str1, str2, 15);

	/* dest = src */
	MemMove(str1, str3, 10);

	/* dest > src */
	MemMove(str5, str4, 12);

	puts("*** testing MemMove ***");
	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);
	printf("str3 = %s\n", str3);
	printf("str4 = %s\n", str4);
	printf("str5 = %s\n", str5);

	free(str1);
	free(str4);	

	str1 = NULL;
	str4 = NULL;
	
	return 0;
}

/* for comparing MemMove to memmove */
static int memmoveTest(void)
{
	char *str1 = malloc(30 * sizeof(char));
	char *str2 = str1 + 5;
	char *str3 = str1;
	char *str4 = malloc(30 * sizeof(char));
	char *str5 = str4 + 6;

	EXIT_IF_FAILED(NULL == str1, "malloc failed", -1);
	EXIT_IF_FAILED(NULL == str2, "malloc failed", -1);

	memset(str1, '\0', 30);
	memset(str4, '\0', 30);

	strcpy(str1, "ABCDEFGHIJKLMNOP");
	strcpy(str4, "ABCDEFGHIJKLMNOP");

	/* dest < src */
	MemMove(str1, str2, 15);

	/* dest = src */
	memmove(str1, str3, 10);

	/* dest > src */
	memmove(str5, str4, 12);

	puts("*** testing memmove ***");
	printf("str1 = %s\n", str1);
	printf("str2 = %s\n", str2);
	printf("str3 = %s\n", str3);
	printf("str4 = %s\n", str4);
	printf("str5 = %s\n", str5);

	free(str1);
	free(str4);	

	str1 = NULL;
	str4 = NULL;
	
	return 0;
}

static int AtoiTest(void)
{
	char str1[] = "3535DD";
	char str2[] = "DD32";
	char str3[] = "3535DD";
	char str4[] = "DD32";
	char *str5 = malloc(20);
	char *str6 = malloc(20);
	int num1 = 0;
	int num2 = 0;
	int num3 = 0;
	int num4 = 0;
	int num5 = 0;
	int num6 = 0;

	strcpy(str5, "AD7L04A");
	strcpy(str6, "111001011");

	num1 = atoi(str1);
	num2 = atoi(str2);
	num3 = Atoi(str3);
	num4 = Atoi(str4);
	num5 = AtoiAny(str5, 24);
	num6 = AtoiAny(str6, 2);

	puts("*** testing Atoi and atoi ***");
	printf("%d\n%d\n%d\n%d\n%d\n%d\n", num1, num2, num3, num4, num5, num6);

	free(str5);
	free(str6);

	return 0;
}

static int ItoaTest(void)
{
	int num1 = -77724309;
	int num2 = -77724309;
	char str1[32];
	char str2[32];
	int num3 = 2017156714;
	char *str3 = malloc(33);

	ItoaBin(num1, str2);
	Itoa(num2, str1);
	ItoaAny(num3, str3, 24);

	puts("*** testing Itoa ***");
	printf("%s\n", str1);
	puts("*** testing ItoaBin ***");
	printf("%s\n", str2);
	puts("*** testing ItoaAny ***");
	printf("%s\n", str3);		

	free(str3);

	return 0;
}

static void ThreeArraysTest(void)
{
	char arr1[] = {'a', 'g', 'G', 'T', '7', 'b', 'a', 'A', 'l'};
	char arr2[] = {'b', 'g', '0', 'a', '7', 'l', 'l', '0', 'Q', 'A', 's'};
	char arr3[] = {'c', 's', 'g', 'G', 'T', 's', 'Q', '1', 'a', 'b', 'a', 'A'};
	size_t size1 = sizeof(arr1);
	size_t size2 = sizeof(arr2);
	size_t size3 = sizeof(arr3);

	ThreeArrays(arr1, arr2, arr3, size1, size2, size3);
}

static void EndianTest(void)
{
	int x = 0xAABBCCDD;
	char *px = (char*)&x;

	printf("The system is: ");
	if(*px)
	{
		puts("little endian");
	}
	else
	{
		puts("big endian");
	}
}

