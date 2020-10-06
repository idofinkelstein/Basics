/*Q1*/
int FlipDigitsInNum(int num)
{
	int fliped_num = 0;
	int is_negative = num < 0;
	int sign = -1;

	sign = -is_negative + !is_negative;
	num *= sign;

	while (num)
	{
		fliped_num += fliped_num * 10 + num % 10;

		num /= 10;
	} 

	return (fliped_num * sign);
}
/*Q4*/
unsigned char MirrorByte(unsigned char byte)
{
	byte = (byte >> 4) | (byte << 4);

	byte = (byte & 0x33) << 2 | (byte & 0xCC) >> 2;

	byte = (byte & 0x55) << 1 | (byte & 0xAA) >> 1;

	return (byte);
}
/*Q5*/
int FlipBit(int val, unsigned int n)
{
	return (val ^ (1u << n));
}
/*Q6*/
size_t CountBits(unsigned char byte)
{
	size_t bits_on = 0;

	for (; byte; byte &= (byte - 1))
	{
		++bits_on;
	}

	return (bits_on);
} 
/*Q8*/
char RotateLeft(char byte, unsigned int nbits)
{
	unsigned int bits_in_byte = 8;	

	if (nbits >= bits_in_byte)
	{
		nbits %= bits_in_byte;
	}

	return ((byte << nbits) | (byte >> (bits_in_byte - nbits)));
}
/*Q10*/
void SwapPtr(int **ptr1, int **ptr2)
{
	int *tmp = *ptr1;

	ptr1 = ptr2;
	*ptr2 = tmp;
}
/*Q11*/
size_t StrLen(char *str)
{
	char *start = str;

	while (*str)
	{
		++str;
	}

	return(str - start);
}
/*Q11*/
int StrCmp(char *str1, char *str2)
{
	while (*str1 && *str1 == *str2)
	{
		++str1;
		++str2;
	}

	return (*str1 - *str2);
}
/*Q11*/
char *StrCpy(char *dest, char *src)
{
	char *dest_start = dest;

	while (*src)
	{
		*(dest++) = *(src++);
	}

	*dest = '\0';

	return (dest_start);
}
/*Q11*/
char *StrnCpy(char *dest, char *src, size_t n)
{
	char *dest_start = dest;

	while (*src && n)
	{
		*(dest++) = *(src++);
		
		--n;
	}

	*dest = '\0';

	return (dest_start);
}
/*Q11*/
char *StrCat(char *dest, char *src)
{
	char *dest_start = dest;
	dest = dest + StrLen(dest);

	while (*src)
	{
		*(dest++) = *(src++)
	}

	*dest = '\0';

	return (dest_start);
}
/*Q12*/
unsigned long GetNFibonacciElement(unsigned int n)
{
	unsigned long *fib_arr = (unsigned long*)malloc(sizeof(unsigned long) * n);
	unsigned long res = 0;
	size_t i = 0;
	*fib_arr = 1;
	*(fib_arr + 1) = 1;

	if (NULL == fib_arr)
	{
		return 0;
	}
	
	if (0 == n)
	{
		printf("out of range\n");
		return 0;
	}

	for (i = 2; i < n; ++i)
	{
		fib_arr[i] = fib_arr[i - 1] + fib_arr[i - 2];
	}

	res = fib_arr[n - 1];

	free(fib_arr);

	return (res);
	
}
/*Q13*/
int IntToString(int num)
{
	char *str[12]; /* size: 10 digits max + sign + '\0' */

	sprintf(str, "%d", num);

	return (str);
}
/*Q14*/
long MultiplyBy8(int num)
{
	return ((long)num << 3);
}
/*Q15*/
void swap1(int *num1, int *num2)
{
	int *temp = num1;

	*num1 = *num2;
	*num2 = *temp;
}
/*Q15*/
void swap2(int *num1, int *num2)
{
	*num1 = *num1 + *num2;
	*num2 = *num1 - *num2;
	*num1 = *num1 - *num2;
}
/*Q15*/
void swap3(int *num1, int *num2)
{
	*num1 = *num1 ^ *num2;
	*num2 = *num1 ^ *num2;
	*num1 = *num1 ^ *num2;
}
