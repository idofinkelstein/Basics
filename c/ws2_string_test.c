/*********************** 
file name: ws2_string_test.c
exersice: test the strings
author: Ido Finkelstein
date: 5/5/20
reviewer: 
************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* free */
#include <string.h> /* all string library functions*/
#include <strings.h>
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

	printf("*** testing StrCpy and compare to strcpy ***\n");
	printf("dest string is: [%s]\nsource string: is [%s]\n", str7, str1);
	printf("StrCpy's output: [%s]. strcpy's output: [%s].\n",
		    StrCpy(str7, str1), strcpy(str7, str1));
	printf("dest string is: [%s]\nsource string: is [%s]\n", str8, str2);
	printf("StrCpy's output: [%s]. strcpy's output: [%s].\n",
		    StrCpy(str8, str2), strcpy(str8, str2));
	printf("dest string is: [%s]\nsource string: is [%s]\n", str9, str3);
	printf("StrCpy's output: [%s]. strcpy's output: [%s].\n",
		    StrCpy(str9, str3), strcpy(str9, str3));
	printf("dest string is: [%s]\nsource string: is [%s]\n", str10, str4);
	printf("StrCpy's output: [%s]. strcpy's output: [%s].\n",
		    StrCpy(str10, str4), strcpy(str10, str4));
	printf("dest string is: [%s]\nsource string: is [%s]\n", str11, str5);
	printf("StrCpy's output: [%s]. strcpy's output: [%s].\n",
		    StrCpy(str11, str5), strcpy(str11, str5));
	printf("dest string is: [%s]\nsource string: is [%s]\n", str11, str6);
	printf("StrCpy's output: [%s]. strcpy's output: [%s].\n",
		    StrCpy(str11, str6), strcpy(str11, str6));
	puts("");	
}

void StrnCpyTest(void)
{
	char str1[] = "123456789";
	char str2[] = "some text to delete and copy somthing else.";
	char str3[] = "";
	char str4[] = "copy empty string with random n to here";

	printf("*** testing StrnCpy and compare to strncmp ***\n");
	printf("dest string is: [%s]\nsource string: is [%s], n = %d.\n", str2, str1, 4);
	printf("StrnCpy's output: [%s].\n", StrnCpy(str2, str1, 4));
	sprintf(str2, "some text to delete and copy somthing else.");	    
	printf("strncpy's output: [%s].\n", strncpy(str2, str1, 4));

	printf("dest string is: [%s]\nsource string: is [%s], n = %d.\n", str4, str3, 4);
	printf("StrnCpy's output: [%s].\n", StrnCpy(str4, str3, 4));
	sprintf(str4, "copy empty string with random n to here");	    
	printf("strncpy's output: [%s].\n", strncpy(str4, str3, 4));
	puts("");

}

void StrCaseCmpTest(void)
{
	char str1[] = "aBcDeFgHiJkLmNoP";
	char str2[] = "AbCdEfGhIjKlMnOp";
	char str3[] = "hello world!";
	char str4[] = "hello World!";
	char str5[] = "hello World!";
	char str6[] = "hello to you!";

	printf("*** testing StrCaseCmp and compare to strcasecmp ***\n");
	printf("string1 is: [%s]\nstring2 is: [%s]\nStrCaseCmp's output: %d. strcasecmp's output: %d.\n",
		    str1, str2, StrCaseCmp(str1, str2), strcasecmp(str1, str2));
	printf("string1 is: [%s]\nstring2 is: [%s]\nStrCaseCmp's output: %d. strcasecmp's output: %d.\n",
		    str3, str4, StrCaseCmp(str3, str4), strcasecmp(str3, str4));
	printf("string1 is: [%s]\nstring2 is: [%s]\nStrCaseCmp's output: %d. strcasecmp's output: %d.\n",
			str5, str6, StrCaseCmp(str5, str6), strcasecmp(str5, str6));
	printf("string1 is: [%s]\nstring2 is: [%s]\nStrCaseCmp's output: %d. strcasecmp's output: %d.\n",
			str6, str5, StrCaseCmp(str6, str5), strcasecmp(str6, str5));
	puts("");

}

void StrChrTest(void)
{
	char str[] = "hello world!";

	printf("*** testing StrChr and compare to strchr ***\n");
	printf("chr = [%c]\nStrChr's output is: ", 'l');
	printf("[%s]\n", StrChr(str, 'l'));
	printf("strchr's output is: [%s]\n", strchr(str, 'l'));
	printf("chr = [%c]\nStrChr's output is: ", ' ');
	printf("[%s]\n", StrChr(str, ' '));
	printf("strchr's output is: [%s]\n", strchr(str, ' '));
	printf("chr = [%c]\nStrChr's output is: ", '!');
	printf("[%s]\n", StrChr(str, '!'));
	printf("strchr's output is: [%s]\n", strchr(str, '!'));
	printf("chr = [%c]\nStrChr's output is: ", '\0');
	printf("[%s]\n", StrChr(str, '\0'));
	printf("strchr's output is: [%s]\n", strchr(str, '\0'));
	printf("chr = [%c]\nStrChr's output is: ", 'a');
	printf("[%s]\n", StrChr(str, 'a'));
	printf("strchr's output is: [%s]\n", strchr(str, 'a'));
	puts("");

}

void StrDupTest(void)
{
	char str1[] = "hello world!";
	char *dest = StrDup(str1);
	printf("*** testing StrDup ***\n");
	printf("%s\n", dest);
	free(dest);
}

void StrCatTest(void)
{
	char str1[] = "world!";
	char str2[20] = "hello ";
	char str3[] = "hello world!";
	char str4[20] = "";
	
	printf("*** testing StrCat and compare to strcat ***\n");
	printf("src = [%s]\n", str1);
	printf("dest = [%s]\n", str2);
	printf("StrCat's output = [%s]\n", StrCat(str2, str1));
	sprintf(str2, "hello ");
	printf("strcat's output = [%s]\n", strcat(str2, str1));

	printf("src = [%s]\n", str3);
	printf("dest = [%s]\n", str4);
	printf("StrCat's output = [%s]\n", StrCat(str4, str3));
	sprintf(str4, "%s", "");
	printf("strcat's output = [%s]\n", strcat(str4, str3));
	puts("");
}

void StrnCatTest(void)
{
	char str1[] = "world!";
	char str2[20] = "hello ";
	char str3[] = "hello world!";
	char str4[20] = "";
	
	printf("*** testing StrnCat and compare to strncat ***\n");
	printf("n = 3\n");
	printf("src = [%s]\n", str1);
	printf("dest = [%s]\n", str2);
	printf("StrnCat's output = [%s]\n", StrnCat(str2, str1, 3));
	sprintf(str2, "hello ");
	printf("strncat's output = [%s]\n", strncat(str2, str1, 3));

	printf("n = 5\n");
	printf("src = [%s]\n", str1);
	printf("dest = [%s]\n", str2);
	sprintf(str2, "hello ");
	printf("StrnCat's output = [%s]\n", StrnCat(str2, str1, 5));
	sprintf(str2, "hello ");
	printf("strncat's output = [%s]\n", strncat(str2, str1, 5));

	printf("n = 7\n");
	printf("src = [%s]\n", str1);
	printf("dest = [%s]\n", str2);
	sprintf(str2, "hello ");
	printf("StrnCat's output = [%s]\n", StrnCat(str2, str1, 7));
	sprintf(str2, "hello ");
	printf("strncat's output = [%s]\n", strncat(str2, str1, 7));

	printf("n = 9\n");
	printf("src = [%s]\n", str3);
	printf("dest = [%s]\n", str4);
	sprintf(str4, "%s", "");
	printf("StrnCat's output = [%s]\n", StrnCat(str4, str3, 9));
	sprintf(str4, "%s", "");
	printf("strncat's output = [%s]\n", strncat(str4, str3, 9));
	puts("");

	printf("n = 12\n");
	printf("src = [%s]\n", str3);
	printf("dest = [%s]\n", str4);
	sprintf(str4, "%s", "");
	printf("StrnCat's output = [%s]\n", StrnCat(str4, str3, 12));
	sprintf(str4, "%s", "");
	printf("strncat's output = [%s]\n", strncat(str4, str3, 12));
	puts("");
	
	printf("n = 15\n");
	printf("src = [%s]\n", str3);
	printf("dest = [%s]\n", str4);
	sprintf(str4, "%s", "");
	printf("StrnCat's output = [%s]\n", StrnCat(str4, str3, 15));
	sprintf(str4, "%s", "");
	printf("strncat's output = [%s]\n", strncat(str4, str3, 15));
	puts("");

	printf("n = 0\n");
	printf("src = [%s]\n", str3);
	printf("dest = [%s]\n", str4);
	sprintf(str4, "%s", "");
	printf("StrnCat's output = [%s]\n", StrnCat(str4, str3, 0));
	sprintf(str4, "%s", "");
	printf("strncat's output = [%s]\n", strncat(str4, str3, 0));
	puts("");
}

int main()
{
	StrLenTest();
	StrCmpTest();
	StrCpyTest();
	StrnCpyTest();
	StrCaseCmpTest();
	StrDupTest();
	StrChrTest();
	StrCatTest();
	StrnCatTest();

	return 0;
}
