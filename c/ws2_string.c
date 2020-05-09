/*********************** 
file name: ws2_string.c
exersice: strings
author: Ido Finkelstein
date: 5/5/20
reviewer: Hen Shay Hassid
************************/

#include <stdio.h> /* size_t */
#include <stdlib.h> /* abs */
#include <ctype.h> /* tolower */
#include <assert.h>

size_t StrLen(const char *str)
{
	const char *curr = str;

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

	while ('\0' != *str1 && *str1 == *str2)
	{		
		++str1;
		++str2;		
	}
	
	return (*str1 - *str2);	
}

char *StrCpy(char *dest, const char *src)
{
	char *tmp_dest = NULL;	

	assert(dest);
	assert(src);

	tmp_dest = dest;

	while (*src)
	{
		*tmp_dest = *src;
		++src;
		++tmp_dest;
	}	

	*tmp_dest = '\0'; 

	return (dest);
}

/* copy src to dest until stop condition is met */
char *StrnCpy(char *dest, const char *src, size_t n)
{
	char *curr = dest;
	char *stop = dest + n;

	assert(dest);
	assert(src);

	while (curr != stop && *src)
	{
		*curr = *src;
		++curr;
		++src;
	}	
	
	while (curr != stop)
	{
		*curr = '\0';
		++curr;
	}

	return (dest);
}

int StrCaseCmp(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);

	while ('\0' != *str1 && tolower(*str1) == tolower(*str2))
	{		
		++str1;
		++str2;		
	}
	
	return (tolower(*str1) - tolower(*str2));
}

char *StrDup(const char *str)
{
	char *dest = NULL;
	size_t length = StrLen(str);
	
	assert(str);

	dest = (char*) malloc(sizeof(char) * length + 1);

	if (!dest)
	{
		return (NULL);
	}

	dest = StrCpy(dest, str);

	return (dest);
}

char *StrChr(const char *str, int chr)
{
	char *curr = (char*) str;
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
	size_t dest_length = StrLen(dest);
	char *curr = dest + dest_length;

	assert(src);
	assert(dest);

	StrCpy(curr, src);

	return (dest);
}

char *StrnCat(char *dest, const char *src, size_t n)
{
	size_t dest_length = StrLen(dest);
	char *curr = dest + dest_length;

	assert(src);
	assert(dest);

	StrnCpy(curr, src, n);	

	return dest;
}

char *StrStr(const char *haystack, const char *needle)
{
	size_t i = 0;
	size_t j = 0;
	size_t cnt = 0;
	size_t hay_length = StrLen(haystack);
	size_t nee_length = StrLen(needle);
	char *curr = (char*) haystack;
	char *first = (char*) haystack;

	assert(haystack);
	assert(needle);
	
	/* double loop for running on haystack and searching for needle
	   by compring all chars, the inner loop is always starting
	   from current i and this ensures any type of string can be found.*/

	for (i = 0; i < hay_length; ++i)
	{
		cnt = 0;

		for(j = i; j < hay_length; ++j)
		{
			if (*(haystack + j) == *(needle + cnt))
			{
				++cnt;

				if (1 == cnt)
				{
					curr += j; /* put the pointer on
								  the first occurence of needle */
				}	
			}
			else
			{
				cnt = 0;
				curr = first; /* if there isn't match,
								 put the pointer at the start point */
			}

			if (cnt == nee_length) /* if there is a full match,
									  return the pointer */
			{
				return (curr);
			}
		}
	}

	return (curr = NULL);
}


