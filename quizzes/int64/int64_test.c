#include <stdio.h>

#include "int64.h"

int main()
{
	Int64_t x, y;

	x = Int64("-634562");
	y = Int64("4562");

	 y = I64Shiftl(y, 32);

	printf("%d\n", x.lsi);
	printf("%d\n", y.msi);

	return 0;
}
