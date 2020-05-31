/**********************
Author: Ido Finkelstein
File name: ws9.c
Reviewer: Gal Shvinkelstein
Date: 31/5/2020
***********************/

#include <stdio.h>  /* size_t       */
#include <stdlib.h> /* malloc, free */
#include <assert.h>
#include <string.h> /* strcpy */

#define ASCII_ELEMENTS 128
#define ADDRESS_MASK (sizeof(size_t) - 1)
#define EXIT_IF_FAILED(COND, MSG, RET) if (COND) {puts(MSG); return (RET);}
#define ELEMENT_AMOUNT 2

char *Reverse(char arr[]);
int Convert(char digit);

void *MemSet(void *str, int c, size_t n)
{
	void *curr_str = str;
	size_t dup_c = c;
	size_t c_word = c;
	size_t shift = sizeof(size_t);

	assert(str);

	/* this loop runs until curr_str meets alinged memory address */
	while (((size_t)curr_str & ADDRESS_MASK) && n)
	{
		*(char*)curr_str = (char)c;

		curr_str = (char*)curr_str + 1;

		--n;
	}
	
	/* this loop duplicates input char word-size times */
	while(c_word)
	{
		dup_c = dup_c | (c_word <<= shift);
	}

	/* this loop copys wordsize chunks to *curr_str */
	while (n > ADDRESS_MASK)
	{
		*(size_t*)curr_str = dup_c;

		curr_str = (size_t*)curr_str + 1;

		n -= shift;
	}

	/* this loop copys the leftover bytes to *curr_str */
	while (n)
	{
		*(char*)curr_str = (char)c;

		curr_str = (char*)curr_str + 1;

		--n;
	}
						
	return (str);
}

 void *MemCpy(void *dest, const void *src, size_t n)
{
	void *curr_dest = dest;
	void *curr_src= (void*)src;
	size_t shift = sizeof(size_t);

	assert(dest);
	assert(src);

	/* this loop runs until curr_dest meets alinged memory address */
	while (((size_t)curr_dest & ADDRESS_MASK) && n)
	{
		*(char*)curr_dest = *(char*)curr_src;

		curr_dest = (char*)curr_dest + 1;		

		curr_src = (char*)curr_src + 1;

		--n;
	}
	
	/* this loop copys wordsize chunks to *curr_dest */
	while (n > ADDRESS_MASK)
	{
		*(size_t*)curr_dest = *(size_t*)curr_src;

		curr_dest = (size_t*)curr_dest + 1;		

		curr_src = (size_t*)curr_src + 1;

		n -= shift;
	}

	/* this loop copys the leftover bytes to *curr_dest */
	while (n)
	{
		*(char*)curr_dest = *(char*)curr_src;

		curr_dest = (char*)curr_dest + 1;		

		curr_src = (char*)curr_src + 1;

		--n;
	}				

	return (dest);
}

void *MemMove(void *dest, const void *src, size_t n)
{
	void *curr_dest = dest;
	void *curr_src= (void*)src;
	size_t shift = sizeof(size_t);

	assert(dest);
	assert(src);

	/* in case  dest is smaller then src this loop
	   copys   wordsize   chunks   to   *curr_dest */
	while (dest < src && n > ADDRESS_MASK)
	{
		*(size_t*)curr_dest = *(size_t*)curr_src;

		curr_dest = (size_t*)curr_dest + 1;		

		curr_src = (size_t*)curr_src + 1;

		n -= shift;
	}

	/* this loop copys the rest of the bytes to *curr_dest */
	while (dest < src && n)
	{
		*(char*)curr_dest = *(char*)curr_src;

		curr_dest = (char*)curr_dest + 1;		

		curr_src = (char*)curr_src + 1;

		--n;
	}

	/* in case dest is bigger then src, copying starts from
	   the end */
	if (src < dest)
	{
		curr_dest = (char*)curr_dest + n - 1;		

		curr_src = (char*)curr_src + n - 1;

		while (n)
		{
			*(char*)curr_dest = *(char*)curr_src;

			curr_dest = (char*)curr_dest - 1;		

			curr_src = (char*)curr_src - 1;

			--n;
		}
	}

	return (dest);
}

/* converts string to int, also handles negative sign */
int Atoi(const char *str)
{
	int num = 0;
	char sign = 1;

	if('-' == *str) /* handles negative number */
	{
		sign = -sign;
		++str;
	}

	while ('0' <= *str && *str <= '9')
	{
		num = (num * 10) + *str++ - '0';	
	}

	return (num * sign);
}

/* converts string in base up to 36 to int, also handles negative sign */
int AtoiAny(const char *str, char base)
{
	int num = 0;
	char sign = 1;

	if('-' == *str) /* handles negative number */
	{
		sign = -sign;
		++str;
	}

	while (('0' <= *str && *str <= '9') || ('A' <= *str && *str <= 'Z'))
	{
		if('0' <= *str && *str <= '9') /* converts digits */
		{
			num = (num * base) + *str++ - '0';
		}
		else if ('A' <= *str && *str <= 'Z') /* converts letters
											    (only capitals) */
		{
			num = (num * base) + *str++ - 'A' + 10;
		}
	}

	return (num * sign);
}


/* itoa for base 10 */
char *Itoa(int num, char *str_num)
{
	char *curr = str_num;
	char sign = 0;

	if (0 > num) /* handles negative number */
	{
		sign = '-';
		num = -num;
	}

	do
	{
		*(curr++) = (num % 10) + '0';
			
	}while (num /= 10);

	if('-' == sign)
	{
		*(curr++) = sign;
	}

	*curr = '\0';

	Reverse(str_num);

	return (str_num);
}

/* Itoa for base 2 (2's comlement) */
char *ItoaBin(int num, char *str_num)
{
	char *curr = str_num;
	unsigned mask = 1 << 31;

	while (mask)
	{
		*(curr++) = !!(mask & num) + '0'; /* writes the current bit */
		
		mask >>= 1;
	}
	
	*curr = '\0';	

	return (str_num);
}
/* Itoa for any base (only base 10 represents as negative) */
char *ItoaAny(int num, char *str_num, int base)
{
	char *curr = str_num;
	char sign = 0;


	/* in case n is negative */
	if (0 > num)
	{
		num = -num;

		sign = '-';
	}
	
	do /* generates digits for any base */
	{
		*(curr++) = Convert(num % base); /* saving the chars
									     in reversed order */
			
	}while (num /= base);

	/* assigns the negative sign to the string */
	if('-' == sign)
	{
		*(curr++) = sign;
	}

	*curr = '\0';

	Reverse(str_num); /* reverses the order */

	return (str_num);
}

/* revereses array of bytes */
char *Reverse(char arr[])
{
	char *left = arr;
	size_t len = strlen(arr);
	char *right = arr + len - 1;


	while (right > left)
	{
		*left ^= *right;
		*right ^= *left;
		*(left++) ^= *(right--);
	}	

	return (arr);
}
/**/
int ThreeArrays(char *arr_a, char *arr_b, char *arr_c, size_t size_a,
				 						  size_t size_b, size_t size_c)
{
	/* 2D array for counting char appearances */
	char **ascii_arr = malloc(sizeof(char*) * 3); 
	size_t i = 0;
	size_t j = 0;

	EXIT_IF_FAILED(NULL == ascii_arr, "malloc failed!", -1);

	ascii_arr[0] = malloc(sizeof(char) * ASCII_ELEMENTS);
	ascii_arr[1] = malloc(sizeof(char) * ASCII_ELEMENTS);
	ascii_arr[2] = malloc(sizeof(char) * ASCII_ELEMENTS);

	EXIT_IF_FAILED(NULL == ascii_arr[0], "malloc failed!", -1);
	EXIT_IF_FAILED(NULL == ascii_arr[1], "malloc failed!", -1);
	EXIT_IF_FAILED(NULL == ascii_arr[2], "malloc failed!", -1);

	/* at the start all the elemnt are initialized to 0 */
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < ASCII_ELEMENTS; ++j)
		{
			ascii_arr[i][j] = 0;
		}
	}

	for (i = 0; i < size_a; ++i)
	{
		ascii_arr[0][(unsigned char)arr_a[i]] = 1;	
	}

	for (i = 0; i < size_b; ++i)
	{
		ascii_arr[1][(unsigned char)arr_b[i]] = 1;	
	}

	for (i = 0; i < size_c; ++i)
	{
		ascii_arr[2][(unsigned char)arr_c[i]] = 1;	
	}
	
	/* if the sum of the first 2 rows is 2, it prints the char */
	for (i = 0; i < ASCII_ELEMENTS; ++i)
	{
		if (ELEMENT_AMOUNT == /* 2 */
			ascii_arr[0][i] + ascii_arr[1][i] && 
			0 == ascii_arr[2][i]) 
		{
			printf("%c ", (char)i);
		}
	}

	puts("");

	free(ascii_arr[0]);
	free(ascii_arr[1]);
	free(ascii_arr[2]);
	free(ascii_arr);

	return 0;
}

/* converting table */
int Convert(char digit)
{
	switch (digit)
	{
		case 0:
			digit = '0';
			break;
		case 1:
			digit = '1';
			break;
		case 2:
			digit = '2';
			break;
		case 3:
			digit = '3';
			break;
		case 4:
			digit = '4';
			break;
		case 5:
			digit = '5';
			break;
		case 6:
			digit = '6';
			break;
		case 7:
			digit = '7';
			break;
		case 8:
			digit = '8';
			break;
		case 9:
			digit = '9';
			break;
		case 10:
			digit = 'A';
			break;
		case 11:
			digit = 'B';
			break;
		case 12:
			digit = 'C';
			break;
		case 13:
			digit = 'D';
			break;
		case 14:
			digit = 'E';
			break;
		case 15:
			digit = 'F';
			break;
		case 16:
			digit = 'G';
			break;
		case 17:
			digit = 'H';
			break;
		case 18:
			digit = 'I';
			break;
		case 19:
			digit = 'J';
			break;
		case 20:
			digit = 'K';
			break;
		case 21:
			digit = 'L';
			break;
		case 22:
			digit = 'M';
			break;
		case 23:
			digit = 'N';
			break;
		case 24:
			digit = 'O';
			break;
		case 25:
			digit = 'P';
			break;
		case 26:
			digit = 'Q';
			break;
		case 27:
			digit = 'R';
			break;
		case 28:
			digit = 'S';
			break;
		case 29:
			digit = 'T';
			break;
		case 30:
			digit = 'U';
			break;
		case 31:
			digit = 'V';
			break;
		case 32:
			digit = 'W';
			break;
		case 33:
			digit = 'X';
			break;
		case 34:
			digit = 'Y';
			break;
		case 35:
			digit = 'Z';
			break;
		default:
			break;
	}

	return (digit);
}
/**/
