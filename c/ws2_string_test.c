/*********************** 
file name: ws2_string_test.c
exersice: test the strings
author: Ido Finkelstein
date: 5/5/20
reviewer: 
************************/

#include <stdio.h> /* printf */
#include <string.h> /* all string library functions*/
#include "ws2_string.h" /* my string functions */

void StrLenTest(void)
{
	char str1[] = "";
	char str2[] = "123456789";
	char str3[] = "hello world!";

	printf("*** testing StrLen and compare to strlen ***\n");
	printf("the string is: [%s] StrLen's output: %lu. strlen's output: %lu.\n",
 			str1, StrLen(str1), strlen(str1));
	printf("the string is: [%s] StrLen's output: %lu. strlen's output: %lu.\n",
		    str2, StrLen(str2), strlen(str2));
	printf("the string is: [%s] StrLen's output: %lu. strlen's output: %lu.\n",
		    str3, StrLen(str3), strlen(str3));
	puts("");

}

void StrCmpTest(void)
{
	char str1[] = "";
	char str2[] = "123456789";
	char str3[] = "hello world!";
	char str4[] = "hello woold!";

	printf("*** testing StrCmp and compare to strcmp ***\n");
	printf("string1 is: [%s]\nstring2 is: [%s]\nStrCmp's output: %d. strcmp's output: %d.\n",
		    str1, str2, StrCmp(str1, str2), strcmp(str1, str2));
	printf("string1 is: [%s]\nstring2 is: [%s]\nStrCmp's output: %d. strcmp's output: %d.\n",
		    str2, str1, StrCmp(str2, str1), strcmp(str2, str1));
	printf("string1 is: [%s]\nstring2 is: [%s]\nStrCmp's output: %d. strcmp's output: %d.\n",
			str3, str2, StrCmp(str3, str2), strcmp(str3, str2));
	printf("string1 is: [%s]\nstring2 is: [%s]\nStrCmp's output: %d. strcmp's output: %d.\n",
			str2, str3, StrCmp(str2, str3), strcmp(str2, str3));
	printf("string1 is: [%s]\nstring2 is: [%s]\nStrCmp's output: %d. strcmp's output: %d.\n",
		    str2, str2, StrCmp(str2, str2), strcmp(str2, str2));
	printf("string1 is: [%s]\nstring2 is: [%s]\nStrCmp's output: %d. strcmp's output: %d.\n",
		    str1, str1, StrCmp(str1, str1), strcmp(str1, str1));
	printf("string1 is: [%s]\nstring2 is: [%s]\nStrCmp's output: %d. strcmp's output: %d.\n",
		    str3, str4, StrCmp(str3, str4), strcmp(str3, str4));
	puts("");

}

void StrCpyTest(void)
{
	char str1[] = "123456789";
	char str2[] = "hello world!";
	char str3[] = "hello woold!";
	char str4[] = "                    ";
	char str5[] = "some text to delete and copy not the same.";
	char str6[] = "";
	/* need to repeat this example because StrCpy *
	 * overwrite the original string.             */ 
	char str7[] = "some text to delete and copy somthing else."; 
	char str8[] = "some text to delete and copy somthing else.";
	char str9[] = "some text to delete and copy somthing else.";
	char str10[] = "some text to delete and copy somthing else.";
	char str11[] = "some text to delete and copy somthing else.";

	printf("*** testing StrCpy and compare to strcmp ***\n");
	printf("dest string is: [%s]\nsource string: is [%s]\n", str7, str1);
	printf("StrCmp's output: [%s]. strcmp's output: [%s].\n",
		    StrCpy(str7, str1), strcpy(str7, str1));
	printf("dest string is: [%s]\nsource string: is [%s]\n", str8, str2);
	printf("StrCmp's output: [%s]. strcmp's output: [%s].\n",
		    StrCpy(str8, str2), strcpy(str8, str2));
	printf("dest string is: [%s]\nsource string: is [%s]\n", str9, str3);
	printf("StrCmp's output: [%s]. strcmp's output: [%s].\n",
		    StrCpy(str9, str3), strcpy(str9, str3));
	printf("dest string is: [%s]\nsource string: is [%s]\n", str10, str4);
	printf("StrCmp's output: [%s]. strcmp's output: [%s].\n",
		    StrCpy(str10, str4), strcpy(str10, str4));
	printf("dest string is: [%s]\nsource string: is [%s]\n", str11, str5);
	printf("StrCmp's output: [%s]. strcmp's output: [%s].\n",
		    StrCpy(str11, str5), strcpy(str11, str5));
	printf("dest string is: [%s]\nsource string: is [%s]\n", str11, str6);
	printf("StrCmp's output: [%s]. strcmp's output: [%s].\n",
		    StrCpy(str11, str6), strcpy(str11, str6));
	puts("");	
}

int main()
{
	StrLenTest();
	StrCmpTest();
	StrCpyTest();

	return 0;
}
