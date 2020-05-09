
#include <stdio.h>
#include <stdlib.h>
#include "ws2_additional.h"

void IsPalindromeTest(void)
{
	char str1[] = "hello!";
	char str2[] = "abccba";
	char str3[] = "~!@#@!~";
	char str4[] = "";
	char str5[] = "heelkeeh";
	char str6[] = " ";

	printf("*** testing IsPalindrome ***\n");
	printf ("[%s] is %d\n", str1, IsPalindrome(str1));
	printf ("[%s] is %d\n", str2, IsPalindrome(str2));
	printf ("[%s] is %d\n", str3, IsPalindrome(str3));
	printf ("[%s] is %d\n", str4, IsPalindrome(str4));
	printf ("[%s] is %d\n", str5, IsPalindrome(str5));
	printf ("[%s] is %d\n", str6, IsPalindrome(str6));
	puts("");
}

void SwapPointersTest(void)
{
	int num1 = 5;
	int num2 = 10;
	int *p_num1 = &num1;
	int *p_num2 = &num2;

	printf("p_num1 -> %d\n", *p_num1);
	printf("p_num2 -> %d\n", *p_num2);
	SwapPointers(p_num1, p_num2);
	printf("p_num1 -> %d\n", *p_num1);
	printf("p_num2 -> %d\n", *p_num2);
	puts("");
}

void SevenBoomTest(void)
{
	SevenBoom(-100, 100);
}

void RemoveSpacesTest(void)
{
	char str1[] = "  	 Too					much 			  white-spaces"
				  "	 		 between  	  words  		 ";
	printf ("[%s]\n", str1);
	RemoveSpaces(str1);
	printf ("[%s]\n", str1);
}

void AddBigNumbersTest(void)
{
	char *str = AddBigNumbers("111111111111111111111111111111119", "11111111111111111111111111111111111");
	printf("%s\n", str);
	free(str);
	
}

int main()
{
	IsPalindromeTest();
	SwapPointersTest();
	SevenBoomTest();
	RemoveSpacesTest();
	AddBigNumbersTest();

	return 0;
}
