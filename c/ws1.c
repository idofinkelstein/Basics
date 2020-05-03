/**********************
File name: ws1.c
author: Ido Finkelstein
reviewer: Rita Lempert
date: 3/5/20
status: Approved
***********************/

#include <stdio.h> /* printf() */
#include <stdlib.h>/* abs() */

void PrintHelloWorld()
{
	/* presentation of helloworld with hexadecimal numbers */
	char str[] = {0x22, 0x48, 0x65, 0x6c, 0x6c, 0x6f,
				  0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x22, '\0'};
	
	printf("%s\n", str);
}

float TenPower(int n)
{
	float res = 1.0; /* saving the result*/
	float pow = 10.0;
	int i;

	if (n < 0)
	{
		n = -n;
		pow = 1 / pow;
	}

	for (i = 0; i < n; i++)
	{
		res = res * pow;
	}

	return (res);
}

int ReverseDigits(int num)
{
    int reversed_num = 0;
    
    /* Every iteration the smallest digit in num becomes the largest in reversed_num */
    while (abs(num) > 0)
    {
        reversed_num = reversed_num * 10 + (num % 10);
        num /= 10;
    }
    
    return (reversed_num);
}



void SwapValues(int *ptr_num1, int *ptr_num2)
{
	int temp = 0;

	temp = *ptr_num1;
	*ptr_num1 = *ptr_num2;
	*ptr_num2 = temp;
}

int main()
{
	int num1 = 5, num2 = 10;
	
	/* ***Testing HelloWorld*** */
	puts("***Testing HelloWorld***");
	PrintHelloWorld();
	puts("");

	/* ***Testing TenPower*** */
	puts("***Testing TenPower***");
	printf("10 ^ (%d) = %f\n", 3, TenPower(3));
	printf("10 ^ (%d) = %f\n", -3, TenPower(-3));	
	printf("10 ^ (%d) = %f\n", 0, TenPower(0));
	puts("");

	/* ***Testing ReverseDigits*** */
	puts("***Testing ReverseDigits***");
	printf("The number 3004000 becomes %d\n",ReverseDigits(3004000));
    printf("The number -3004000 becomes %d\n",ReverseDigits(-3004000));
    printf("The number 123456 becomes %d\n",ReverseDigits(123456));
    printf("The number 7650432 becomes %d\n",ReverseDigits(7650432));
	puts("");

	/* ***Testing SwapValues*** */
	puts("***Testing SwapValues***");
	printf("num1 = %d, num2 = %d.",num1, num2);
	SwapValues(&num1, &num2);
	printf(" After swapping: num1 = %d, num2 = %d.", num1, num2);
	puts("");


	return 0;
}
