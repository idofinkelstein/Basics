/*********************** 
file name: ws2_string.c
exersice: strings
author: Ido Finkelstein
date: 5/5/20
reviewer: 
************************/
#include <stdio.h> /* size_t */
#include <stdlib.h> /* abs */

size_t StrLen(const char *str)
{
	char *current_member = (char*)str;
	
	while ('\0' != *current_member)
	{
		++current_member;
	}

	return (current_member - str);
}

int StrCmp(const char *str1, const char *str2)
{
	while ('\0' != *str1 || '\0' != *str2)
	{
		if (*str1 == *str2)
		{
			++str1;
			++str2;
		}
		else
		{
			return (*str1-*str2);
		}
	}
	
	return (*str1-*str2);	
}

char *StrCpy(char *dest, const char *src)
{
	size_t i = 0, length = StrLen(src);

	for(i = 0; i <= length; ++i)
	{
		*(dest + i) = *(src + i);
	}	

	return (dest);
}

char *StrnCpy(char *dest, const char *src, size_t n)
{
	size_t i = 0;

	for(i = 0; i < n || '\0' == *(src + i); ++i)
	{
		*(dest + i) = *(src + i);
	}	
	
	*(dest + i) = '\0';

	return (dest);
}

int StrCaseCmp(const char *str1, const char *str2)
{
	while ('\0' != *str1 || '\0' != *str2)
	{
		if ((abs(*str1 - *str2) == 32) &&
		   ((*str1 <= 'Z' && *str1 >= 'A') || (*str1 <= 'z' && *str1 >= 'a')) &&
		   ((*str2 <= 'Z' && *str2 >= 'A') || (*str2 <= 'z' && *str2 >= 'a')))
		{
			++str1;
			++str2;
		}
		else if (*str1 == *str2)
		{
			++str1;
			++str2;
		}
		else 
		{
			return(*str1 - *str2);
		}
	}

	return (*str1-*str2);
}



