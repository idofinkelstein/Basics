long Add1(long num)
{
	
	unsigned long mask = 1;

	while (num & mask)
	{
		num ^= mask;
		mask <<= 1;
	}

	return (num ^= mask);
}
