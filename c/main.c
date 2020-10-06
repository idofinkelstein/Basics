#include <stdio.h>
#include "g.h"

/* int g_s = 3; */

int main()
{
	printf("%d\n", g_s);
	g_s = Foo(g_s);
	printf("%d\n", g_s);

	return 0;
}
