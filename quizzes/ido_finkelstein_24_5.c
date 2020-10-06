unsigned CountBits(long num)
{
	unsigned count = 0;

	for (; num; num &= (num - 1))
		{
			++count;
		}

	return (count);
}

unsigned CountBitCouples(unsigned char num)
{
	unsigned count == 0;
	unsigned double_count = 0;
	unsigned char mask = 1;

	while (num)
	{
		if (count == 1 && (num & mask))
		{
			++double_count;
			count = 0;		
		}

		count += num & mask;
		num >>= 1;
	}

	return (double_count);
}

void Swap1(int *num1, int *num2)
{
	*num1 += *num2;
	*num2 = *num1 - *num2;
	*num1 -= *num2;
}

void Swap2(int *num1, int *num2)
{
	*num1 ^= *num2;
	*num2 ^= *num1;
	*num1 ^= *num1;
}

void Swap3(int *num1, int *num2)
{
	int temp = *num1;

	*num1 = *num2;
	*num2 = temp;	
}

/* 4. בגלל שהתו הוא בעל סימן, הזזה ימינה לא מוגדרת בשפה.
5. << זה נחשב כאופרטור אריטמתי כי הוא מבצע פעולה מתמטית של חלוקה/כפל בחזקה של 2, תלוי בכיוון החיצים.
