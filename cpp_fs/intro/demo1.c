#include <stdio.h>

int main()
{
	enum E {AA, BB, CC, DD};
/*	enum E2 {TT, KK};
	enum E e = 2;
	enum E2 e2 = AA;
	// e22 = kk;
	++e;
	int i = e;
*/
	enum E a;

	a += 3;

	printf("%d\n", a);
	return 0;
}
