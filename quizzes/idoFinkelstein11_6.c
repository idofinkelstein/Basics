unsigned int AddOne(unsigned int num)
{
	unsigned int to_add = 1;
	unsigned int carry = 0;

	do
	{
		carry <<= 1;
		carry = num & to_add;
		num = num ^ to_add;
		to_add <<= 1;

	}while (carry);

	return (num);
}
