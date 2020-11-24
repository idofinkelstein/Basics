#include <stdio.h>

void swap(char *byte1, char *byte2, size_t n_bytes);
void permutations(char *str, size_t i, size_t len);

int main()
{
	char str[] = "helo";

	permutations(str, 0, 4);

	return 0;
}

void swap(char *byte1, char *byte2, size_t n_bytes)
{
	char temp = 0;

	while (n_bytes--)
	{
		temp = *byte1; 
   	 	*byte1++ = *byte2;
    	*byte2++ = temp;
	}
}

void permutations(char *str, size_t i, size_t len)
{


	if (len == 0)
	{
		puts(str);
	}

	for( i = 0; i < len; ++i)
	{
		swap(str, str + i, 1);
		permutations(str, i+1, len );
		swap(str , str + i, 1);
	}
}
