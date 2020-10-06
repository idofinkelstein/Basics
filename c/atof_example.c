#include <stdlib.h> /* malloc, free, atof */
#include <stdio.h>   /* printf */

int main()
{
	const char *str = "324.5646fhdfh";
	float f = 0;

	f = (float)strtod(str, (char**)&str);

	printf("%f\n", f);
	printf("%s\n", str);

	return 0;
}
