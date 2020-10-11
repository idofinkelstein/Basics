#include <stdio.h>

#include "int64.h"

int main()
{
	Int64_t y1, y2, x1, x2, res, a, b, c, t;
	long Y1 = 4554620, k = 45544362000;
	int shift = 28;
	long A = 123456789, B = -98765432;
	

	t = Int64("45544362000");
	puts("testing shift right");

	printf("t = %08x%08x\n", t.msi, t.lsi);
	printf("k = %016lx\n", k);

	t = I64Shiftr(t, 7);
	k >>= 7;

	printf("API:     t >>= %08x%08x\n", t.msi, t.lsi);
	printf("Machine: k >>= %016lx\n", k);
	puts("----------------------------------------------------------------");

	c = Int64("-1");
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


/*-------------------------------------------------------------------------------------*/

	puts("negative values test");
	printf("Machine: c = %16lx\n", -1l);
	printf("API:     c = %08x%08x\n", c.msi, c.lsi);
	printf("Is negative? %d\n", IsNegative(c));
	puts("--------------------------------------------------");

/*-------------------------------------------------------------------------------------*/

	c = Int64("-12345");
	printf("Machine: c = %16lx\n", -12345l);
	printf("API:     c = %08x%08x\n", c.msi, c.lsi);
	printf("Is negative? %d\n", IsNegative(c));
	puts("--------------------------------------------------");

/*-------------------------------------------------------------------------------------*/

	a = Int64("123456789");
	b = Int64("-98765432");	
	printf("Is a negative? %d\n", IsNegative(a));
	printf("Is b negative? %d\n", IsNegative(b));

	puts("comparison Tilde function between machine and API");

	printf(" A = %ld\n", A);
	printf(" B = %ld\n", B);

	printf(" A = %016lx\n", A);
	printf(" a = %08x%08x\n", a.msi, a.lsi);
	printf(" B = %016lx\n", B);
	printf(" b = %08x%08x\n", b.msi, b.lsi);

	a = I64Tilde(a);
	b = I64Tilde(b);

	printf(" ~A = %016lx\n", ~A);
	printf(" ~a = %08x%08x\n", a.msi, a.lsi);
	printf(" ~B = %016lx\n", ~B);
	printf(" ~b = %08x%08x\n", b.msi, b.lsi);
	


/*-------------------------------------------------------------------------------------*/
	x1 = Int64("-2200000000");
	x2 = Int64("800000000");

	res = Int64Add(x1, x2);

	puts("comparison between machine and API");
	puts("--------------------------------------------------");
	printf(" x1 = %ld\n", -2200000000l);
	printf(" x2 = %ld\n", 800000000l);
	printf("API:     x1 + x2 = %08x%08x\n", res.msi, res.lsi);
	printf("Machine: x1 + x2 = %016lx\n", -2200000000ul + 800000000);

/*-------------------------------------------------------------------------------------*/

	x1 = Int64("3000000000");
	x2 = Int64("3000000000");

	res = Int64Add(x1, x2);

	puts("--------------------------------------------------");
	printf(" x1 = %ld\n", 3000000000);
	printf(" x2 = %ld\n", 3000000000);
	printf("API:     x1 + x2 = %08x%08x\n", res.msi, res.lsi);
	printf("Machine: x1 + x2 = %016lx\n", 3000000000 + 3000000000);
	printf("Machine: x1 + x2 = %lu\n", 3000000000 + 3000000000);

/*-------------------------------------------------------------------------------------*/


	x1 = Int64("4100000000");
	x2 = Int64("4100000000");

	res = Int64Add(x1, x2);

	puts("--------------------------------------------------");
	printf(" x1 = %ld\n", 4100000000);
	printf(" x2 = %ld\n", 4100000000);
	printf("API:     x1 + x2 = %08x%08x\n", res.msi, res.lsi);
	printf("Machine: x1 + x2 = %016lx\n", 4100000000 + 4100000000);
	printf("Machine: x1 + x2 = %ld (des)\n", 4100000000 + 4100000000);
	
/*-------------------------------------------------------------------------------------*/

	x1 = Int64("43200000000");
	x2 = Int64("55550000000");
	/* can't handle long inputs until Mul is ready */
	res = Int64Add(x1, x2);

	puts("--------------------------------------------------");
	printf(" x1 = %ld\n", 43200000000);
	printf(" x2 = %ld\n", 55550000000);
	printf("API:     x1 + x2 = %08x%08x\n", res.msi, res.lsi);
	printf("Machine: x1 + x2 = %016lx\n", 43200000000 + 55550000000);
	printf("Machine: x1 + x2 = %ld (des)\n", 43200000000 + 55550000000);
	
/*-------------------------------------------------------------------------------------*/

	x1 = Int64("-7770000000");
	x2 = Int64("-6660000000");
	/* can't handle long inputs until Mul is ready */
	res = Int64Add(x1, x2);

	puts("--------------------------------------------------");
	printf(" x1 = %ld\n", -7770000000);
	printf(" x2 = %ld\n", -6660000000);
	printf("API:     x1 + x2 = %08x%08x\n", res.msi, res.lsi);
	printf("Machine: x1 + x2 = %016lx\n", -7770000000 + -6660000000);
	printf("Machine: x1 + x2 = %ld (des)\n", -7770000000 + -6660000000);
	

/*-------------------------------------------------------------------------------------*/

	x1 = Int64("7000000000");
	x2 = Int64("5");

	printf("x2.lsi = %d\n", x2.lsi);
	/* can't handle long inputs until Mul is ready */
	res = Int64Mul(x1, x2);
	printf("x2.lsi = %d\n", x2.lsi);
	puts("--------------------------------------------------");
	printf(" x1 = %ld\n", 7000000000);
	printf(" x2 = %ld\n", 5l);
	printf(" x1 = %08x%08x\n", x1.msi, x1.lsi);
	printf(" x1 = %016lx\n", 7000000000);
	printf(" x2 = %08x%08x\n", x2.msi, x2.lsi);
	printf(" x2 = %016lx\n", 5l);
	printf("API:     x1 * x2 = %08x%08x\n", res.msi, res.lsi);
	printf("Machine: x1 * x2 = %016lx\n", 7000000000 * 5);
	printf("Machine: x1 * x2 = %ld (des)\n", 7000000000 * 5);
/*-------------------------------------------------------------------------------------*/

	x1 = Int64("5");
	x2 = Int64("7000000000");
	/* can't handle long inputs until Mul is ready */
	res = Int64Mul(x1, x2);

	puts("--------------------------------------------------");
	printf(" x1 = %ld\n", 5l);
	printf(" x2 = %ld\n", 7000000000);
	printf(" x1 = %08x%08x\n", x1.msi, x1.lsi);
	printf(" x1 = %016lx\n", 5l);
	printf(" x2 = %08x%08x\n", x2.msi, x2.lsi);
	printf(" x2 = %016lx\n", 7000000000);
	printf("API:     x1 * x2 = %08x%08x\n", res.msi, res.lsi);
	printf("Machine: x1 * x2 = %016lx\n", 7000000000 * 5);
	printf("Machine: x1 * x2 = %ld (des)\n", 7000000000 * 5);

	/*-------------------------------------------------------------------------------------*/

	x1 = Int64("5435645");
	x2 = Int64("600000000");
	/* can't handle long inputs until Mul is ready */
	res = Int64Mul(x1, x2);

	puts("--------------------------------------------------");
	printf(" x1 = %ld\n", 5435645l);
	printf(" x2 = %ld\n", 600000000l);
	printf(" x1 = %08x%08x\n", x1.msi, x1.lsi);
	printf(" x2 = %08x%08x\n", x2.msi, x2.lsi);
	printf("API:     x1 * x2 = %08x%08x\n", res.msi, res.lsi);
	printf("Machine: x1 * x2 = %016lx\n", 600000000l * 5435645);
	printf("Machine: x1 * x2 = %ld (des)\n", 600000000l * 5435645);

		/*-------------------------------------------------------------------------------------*/

	x1 = Int64("-5435645");
	x2 = Int64("600000000");
	/* can't handle long inputs until Mul is ready */
	res = Int64Mul(x1, x2);

	puts("--------------------------------------------------");
	printf(" x1 = %ld\n", -5435645l);
	printf(" x2 = %ld\n", 600000000l);
	printf(" x1 = %08x%08x\n", x1.msi, x1.lsi);
	printf(" x2 = %08x%08x\n", x2.msi, x2.lsi);
	printf("API:     x1 * x2 = %08x%08x\n", res.msi, res.lsi);
	printf("Machine: x1 * x2 = %016lx\n", 600000000l * -5435645);
	printf("Machine: x1 * x2 = %ld (des)\n", 600000000l * -5435645);
	return 0;
}
