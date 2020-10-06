
#include <stdio.h>

double TenPower(int n)
{
	double res = 1.0; /* saving the result*/
	double base = 10.0;
	int i;

	if (n < 0)
	{
		n = -n;
		base = 1 / base;
	}

	for (i = 0; i < n; ++i)
	{
		res = res * base;
	}

	return (res);
}

int main()
{
	/* ***Testing TenPower*** */
	puts("***Testing TenPower***");
	printf("10 ^ (%d) = %f\n", 3, TenPower(3));
	printf("10 ^ (%d) = %f\n", -3, TenPower(-3));	
	printf("10 ^ (%d) = %f\n", 0, TenPower(0));
	puts("");


	return 0;
}
