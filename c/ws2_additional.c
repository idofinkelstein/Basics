/**************************
file name: ws2.additional.c
author: Ido Finkelstein
reviewer: Anna Poryadkov
sanding date: 10/5/20
***************************/

#include <stdlib.h> /* printf */
#include "ws2_string.h" 
#include "ws2_string.c"

int IsPalindrome(const char *str)
{
	size_t str_length = StrLen(str);
	int flag = 0;
	char *forward = (char*)str;
	char *backward = (char*)str + str_length - 1;

	while (backward >= forward)
	{
		if (*forward == *backward)
		{
			flag = 1;
			++forward;
			--backward;
		}
		else return 0;
	}

	return flag;
}


void SwapPointers(int *ptr1, int *ptr2)
{
	int *tmp_ptr = NULL;

	tmp_ptr = ptr1;
	ptr1 = ptr2;
	ptr2 = tmp_ptr;
}

void SevenBoom(int from, int to)
{
	int is_seven = 0;
	int num = 0;
	size_t size = to - from + 1;
	int *arr = (int*) malloc(sizeof(int) * size); /* creating array
													 for the numbers */
	int *curr = arr;
	int *start = arr;
	int *stop = arr + size - 1;
	int is_negative = 0;
	int sign = 0;
	
	*arr = from;
	num = *curr;

	
	while(arr <= stop) /* adding values to array */
	{
		*arr = num;
		++arr;
		++num;
	}

	while (curr <= stop) /* running on the array */
	{
		num = *curr;
		is_negative = num < 0; /* for negative numbers */
		sign = -1 * is_negative + !is_negative; /* for negative numbers */
		
		if (0 == (num * sign) % 7)
		{
			printf("BOOM, ");

			++curr;
			num = *curr;
			is_negative = num < 0;
			sign = -1 * is_negative + !is_negative;
			
		}
		
		while (num != 0)
		{
			is_seven = ((num * sign) % 10); /* extracting the least sagnificant
											   digit from number */
			

			if (7 == is_seven) /* checking if digit equals 7 */
			{
				printf("BOOM, ");

				++curr;

				break; /* if it is, breaking the loop */
			}
			else /* checking if the number contains the digit 7 */
			{
				num = num / 10; /* if it is not, dividing the number in 10
								   for extracting the least significant 
								   digit in the next iteration */
			}
			
			if (0 == num)
			{
				printf("%d, ", *curr);

				++curr;			
			}	
		}		
	}
	printf("\n");

	arr = start;
	free(arr);
}

char *RemoveSpaces(char *str)
{
	size_t length = StrLen(str);
	char *curr = str + length - 1;

	while ((*curr == ' ' || *curr == '\t')) /* removing white-spaces from the
											   the end of the string and replacing
											   them with '\0' */
	{
		*curr = '\0';
		--curr;
	}

	curr = str;

	while ((*curr == ' ' || *curr == '\t')) /* removing white-spaces from the
											   beginning */
	{
		++curr;
	}
	
	StrCpy(str, curr);
	curr = str;
	
	/* this loop checks if the current char and next one is white-space,
	   if it is, it calls StrCpy() to fix it */
	while (*curr)
	{
		if ((*curr == ' ' || *curr == '\t') &&
		   (*(curr + 1) == '\t' || *(curr + 1) == ' '))
		{
			StrCpy(curr, curr + 1);			
		}
		else
		{
			++curr;
		}
	}

	curr = str;

	/* i had some bugs with the '\t' char so i replaced them with ' ' */
	while (*curr) 
	{
		if (*curr == '\t')
		{
			*curr = ' ';
		}

		++curr;
	}
	
	return (str);
}

char *AddBigNumbers(char *num1, char *num2)
{
	size_t num1_len = StrLen(num1);
	size_t num2_len = StrLen(num2);
	size_t sum_len = 0;
	size_t len = 0;
	char *sum = NULL;
	char *tmp_num = NULL;
	char *tmp_curr = NULL;
	char *stop = NULL;
	char *curr_sum = NULL;
	char *curr1 = num1 + num1_len;
	char *curr2 = num2 + num2_len;
	int num1_int = 0;
	int num2_int = 0;
	int remain = 0;
	int res = 0;

	assert(num1);
	assert(num2);

	/* this if statement check which of the strings is longer and preper a
	   new string in the length of the longer one for the shorter one.
	   after the new string is ready, the short string goes to the new
	   string from the end backward and the rest of the string padded with 
	   zeros.
	   after the new string is ready it adds the numbers by first converting them 
	   to int according to ascii table, than adds them, saves the remainder,
	   converts back to chars and places them in string sum.
	   the else statement does the same for the case that num1_len < num2_len. */
	if (num1_len > num2_len)
	{
		sum_len = num1_len + 1;
		len = num1_len;
		tmp_num = (char*) malloc(sizeof(char) * len + 1);
		sum = (char*) malloc(sizeof(char) * sum_len + 1);
		tmp_curr = tmp_num + len;
		*tmp_curr = '\0';
		stop = tmp_curr - num2_len;
		curr_sum = sum + sum_len;
		*curr_sum = '\0';
		--curr_sum;

		while (tmp_curr >= stop)
		{
			*tmp_curr = *curr2;
			--tmp_curr;
			--curr2;
		}

		while (tmp_curr >= tmp_num)
		{
			*tmp_curr = '0';
			--tmp_curr;
		}

		tmp_curr = tmp_num + len - 1;
		--curr1;

		while(tmp_curr >= tmp_num && curr1 >= num1)
		{
			num1_int = *curr1 - 48;
			num2_int = *tmp_curr - 48;
			res = remain + num1_int + num2_int;
			remain = res / 10;
			res = res % 10;

			*curr_sum = res + 48;

			--tmp_curr;
			--curr1;
			--curr_sum;
		}

		*curr_sum = remain + 48;
	}
	else
	{
		sum_len = num2_len + 1;
		len = num2_len;
		tmp_num = (char*) malloc(sizeof(char) * len + 1);
		sum = (char*) malloc(sizeof(char) * sum_len + 1);
		tmp_curr = tmp_num + len;
		*tmp_curr = '\0';
		stop = tmp_curr - num1_len;
		curr_sum = sum + sum_len;
		*curr_sum = '\0';
		--curr_sum;

		while (tmp_curr >= stop)
		{
			*tmp_curr = *curr1;
			--tmp_curr;
			--curr1;
		}

		while (tmp_curr >= tmp_num)
		{
			*tmp_curr = '0';
			--tmp_curr;
		}
		
		tmp_curr = tmp_num + len - 1;
		--curr2;

		while(tmp_curr >= tmp_num && curr2 >= num2)
		{
			num1_int = *tmp_curr - 48;
			num2_int = *curr2 - 48;
			res = remain + num1_int + num2_int;
			remain = res / 10;
			res = res % 10;

			*curr_sum = res + 48;

			--tmp_curr;
			--curr1;
			--curr_sum;
		}

		*curr_sum = remain + 48;
	}

	if ('0' == *curr_sum)
		{
			StrCpy(curr_sum, curr_sum + 1);
		} 		

	free(tmp_num);

	printf("%s\n+\n", num1);
 	printf("%s\n=\n", num2);
	return (curr_sum);
}

