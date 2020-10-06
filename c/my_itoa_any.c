char *ItoaAny(int num, char *str_num, int base)
{
	char *curr = str_num;
	double f_num = num; /* to handle fractions (float is not enough) */
	char sign = 0;
	double correction = 0.01; /* to round fractions */

	/* in case n is negative */
	if (0 > num)
	{
		num = -num;

		sign = '-';
	}
	
	do /* generates digits for any base */
	{
		f_num = num;

		f_num = ((f_num / base) - (int)(f_num / base)) + correction;

		f_num *= base;

		*(curr++) = Convert((int)f_num); /* saving the chars
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

