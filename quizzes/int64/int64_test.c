#include <stdio.h>

#include "int64.h"

int main()
{
	Int64_t y1, y2;
	long Y1 = 4554620;
	int shift = 28;


	
	y1 = Int64("4554620");
	y2 = Int64("4554620");

	Y1 <<= shift;
	y1 = I64Shiftl(y1, shift);
	y2 = I64Shiftl2(y2, shift);





	printf("y1 = %08x%08x\n", y1.msi, y1.lsi);
	printf("Y1 = %016lx\n", Y1);
	printf("y2 = %08x%08x\n", y2.msi, y2.lsi);


	printf("y1.msi = %d\n", y1.msi);
	printf("y2.msi = %d\n", y2.msi);
	printf("y1.lsi = %d\n", y1.lsi);
	printf("y2.lsi = %d\n", y2.lsi);


	return 0;
}
