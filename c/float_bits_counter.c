#include <stdio.h>
#include <stdlib.h>


void FloatBitCounter(float num)
{
	unsigned bit_count = 0;
	unsigned *f_ptr = (unsigned*)&num; /* look at the at the address as it is a 										  int address */
	unsigned mask = 1<<31;
	unsigned dup = *f_ptr;
	/**/	
	
	while(mask)
	{
		bit_count += (dup & mask) / mask;
		printf("%d, ", (dup & mask) / mask);

		mask >>=1;
	}


	printf("nuber of set bits = %u\n", bit_count);
}

int main()
{
	float num = 44000.234;

	FloatBitCounter(num);
	

	return 0;
}

/*	unsigned int lsb = 1;

	while (*f_ptr)
	{
		*f_ptr &= (*f_ptr - 1);
		
		++bit_count;	
	}

	while (*f_ptr)
	{
		bit_count += lsb & *f_ptr;

		*f_ptr >>= 1;
	}
*/
