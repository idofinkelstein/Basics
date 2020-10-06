#include <stdio.h>
#include <string.h>

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

char *Itoa(int num, char *str_num)
{
	char *curr = str_num;
	char sign = 0;

	if (num < 0)
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

int main()
{
	char str[] = "-12345600";
	char str2[32];
	int num = -4000;

	Itoa(num, str2);
	Reverse(str);
	printf("%s\n", str);
	printf("%s\n", str2);

	return 0;
}
