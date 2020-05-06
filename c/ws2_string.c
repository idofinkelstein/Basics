/*********************** 
file name: ws2_string.c
exersice: strings
author: Ido Finkelstein
date: 5/5/20
reviewer: Hen Shay Hassid
************************/

#include <stdio.h> /* size_t */
#include <stdlib.h> /* abs */
#include <assert.h>

size_t StrLen(const char *str)
{
	char *curr = (char*)str;

	assert(str);
	
	while ('\0' != *curr)
	{
		++curr;
	}

	return (curr - str);
}

int StrCmp(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);

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

	assert(dest);
	assert(src);

	for(i = 0; i <= length; ++i)
	{
		*(dest + i) = *(src + i);
	}	

	return (dest);
}

/* copy src to dest until stop condition is met */
char *StrnCpy(char *dest, const char *src, size_t n)
{
	size_t i = 0;

	assert(dest);
	assert(src);

	for(i = 0; i < n || '\0' == *(src + i); ++i)
	{
		*(dest + i) = *(src + i);
	}	
	
	for (i = i; i < n; ++i)
	{
		*(dest + i) = '\0';
	}

	return (dest);
}

int StrCaseCmp(const char *str1, const char *str2)
{
	int upper_lower_difference = 32;	

	assert(str1);
	assert(str2);

	while ('\0' != *str1 || '\0' != *str2)
	{
		/* let's check if *str1 and *str2 are same letter diferrent case */ 
		if ((abs(*str1 - *str2) == upper_lower_difference) &&
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
			/* forcing the return value to be a subtraction of
			   the same case */
			if ((*str1 <= 'Z' && *str1 >= 'A') &&
			    (*str2 <= 'z' && *str2 >= 'a')) 
			{
				return(*str1 - *str2 + upper_lower_difference);
			}

			/* forcing the return value to be a subtraction of
			   the same case */
			if ((*str1 <= 'z' && *str1 >= 'a') &&
			    (*str2 <= 'Z' && *str2 >= 'A'))
			{
				return(*str1 - *str2 - upper_lower_difference);
			}

			return(*str1 - *str2);
		}
	}

	return (*str1-*str2);
}

char *StrDup(const char *str)
{
	size_t length = StrLen(str), i = 0;
	char *dest = (char*)malloc(sizeof(char) * length + 1);

	assert(str);

	for (i = 0; i <= length; ++i)
	{
		*(dest + i) = *(str + i);
	}

	return (dest);
}

char *StrChr(const char *str, int chr)
{
	char *curr = (char*)str;
	size_t length = StrLen(str);
	
	assert(str);
	

	while (*curr != chr && '\0' != *curr)
	{
		++curr;
	}

	if (curr == (str + length ) && '\0' != chr)
	{
		curr = NULL;
	}
	
	return (curr);
}

/* the function appends source string to dest string */
char *StrCat(char *dest, const char *src)
{
	size_t j = 0;  
	size_t i = 0;
	size_t src_length = StrLen(src);
	size_t dest_length = StrLen(dest);

	assert(src);
	assert(dest);

	/* appending the source string to dest string */
	for (i = dest_length, j = 0; i < (dest_length + src_length + 1); ++i, ++j)
	{
		*(dest + i) = *(src + j);
	}
	return dest;
}


