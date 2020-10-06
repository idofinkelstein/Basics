#include <stdlib.h>
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


int *SwapPointers(int *ptr1, int *ptr2)
{
	int *tmp_ptr = NULL;

	tmp_ptr = ptr1;
	ptr1 = ptr2;
	ptr2 = tmp_ptr;

	return (ptr1);
}

void SevenBoom(int from, int to)
{
	int is_seven = 0;
	int num = 0;
	size_t size = to - from + 1;
	int *arr = (int*) malloc(sizeof(int) * size);
	int *curr = arr;
	int *start = arr;
	int *stop = arr + size - 1;
	int is_negative = 0;
	int sign = 0;
	
	*arr = from;
	num = *curr;

	
	while(arr <= stop)
	{
		*arr = num;
		++arr;
		++num;
	}

	while (curr <= stop)
	{
		num = *curr;
		is_negative = num < 0;
		sign = -1 * is_negative + !is_negative;
		
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
			is_seven = ((num * sign) % 10);
			

			if (7 == is_seven)
			{
				printf("BOOM, ");

				++curr;

				break;
			}
			else
			{
				num = num / 10;
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

	while ((*curr == ' ' || *curr == '\t'))
	{
		*curr = '\0';
		--curr;
	}

	curr = str;

	while ((*curr == ' ' || *curr == '\t'))
	{
		++curr;
	}
	
	StrCpy(str, curr);
	curr = str;
	
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
	char *new_num1 = NULL;
	char *new_num2 = NULL;
	char *curr_new_num1 = NULL;
	char *curr_new_num2 = NULL;
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

	if (num1_len > num2_len)
	{
		sum_len = num1_len + 1;
		len = num1_len;
		new_num2 = (char*) malloc(sizeof(char) * len + 1);
		sum = (char*) malloc(sizeof(char) * sum_len + 1);
		curr_new_num2 = new_num2 + len;
		*curr_new_num2 = '\0';
		stop = curr_new_num2 - num2_len;

		while (curr_new_num2 >= stop)
		{
			*curr_new_num2 = *curr1;
			--curr_new_num2;
			--curr1;
		}

		while (curr_new_num2 >= tmp_num)
		{
			*curr_new_num2 = '0';
			--curr_new_num2;
		}


	}
	else
	{
		sum_len = num2_len + 1;
		len = num2_len;
		new_num1 = (char*) malloc(sizeof(char) * len + 1);
		sum = (char*) malloc(sizeof(char) * sum_len + 1);
		curr_new_num1 = new_num1 + len;
		*curr_new_num1 = '\0';
		stop = curr_new_num1 - num1_len;

		while (curr_new_num2 >= stop)
		{
			*curr_new_num1 = *curr1;
			--curr_new_num1;
			--curr1;
		}

		while (curr_new_num2 >= tmp_num)
		{
			*curr_new_num1 = '0';
			--curr_new_num1;
		}
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

		curr_sum = sum + sum_len;
		*curr_sum = '\0';
		--curr_sum;



		*curr_sum = remain + 48;
	

	if ('0' == *curr_sum)
		{
			StrCpy(curr_sum, curr_sum + 1);
		} 		

	free(tmp_num);

	printf("%s\n+\n", num1);
 	printf("%s\n=\n", num2);
	return (curr_sum);
}

/* char *AddBigNumbers(char *num1, char *num2)
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
 */

