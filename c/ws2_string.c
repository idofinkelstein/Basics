/*********************** 
file name: ws2_string.c
exersice: strings
author: Ido Finkelstein
date: 5/5/20
reviewer: 
************************/
#include <stdio.h> /* size_t */

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
	/*char *current_str1 = (char*)str1, *current_str2 = (char*)str2;*/

	while ('\0' != *str1 || '\0' != *str2)
	{
		if (*str1 == *str2)
		{
			++str1;
			++str2;
		}
		else if(*str1 < *str2)
		{
			return (*str1-*str2);
		}
		else
		{
			return (*str1-*str2);
		}
	}
	
	return (*str1-*str2);	

}
