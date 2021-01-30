/* version 1.0 */

#include <stdio.h>

/* version 1.3 */
void OutputString(int color, const char* str)
{
	volatile char* video = (volatile char*)0XB8000;
	while (*str != 0)
	{
		*video++ = *str++;
		*video++ = color;
	}
}

int main()
{
	/* v1.1 */
	float x = 5.5; 

	x += 3;

	/* v1.2 */

	x += x;
	
	OutputString(9, "hello world"); /* has some bugs */

	return 0;
}

