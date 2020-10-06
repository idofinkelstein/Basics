#include <string.h>
#include <stdio.h>

void SwapBytes(char *byte1, char *byte2, size_t n_bytes);

void PrintPermutations(char *str)
{
	size_t len = strlen(str);
	size_t i = 0;
	size_t j = 0;

	for (i = 0; i < len; ++i)
	{		
		

		for (j = i; j < len; ++j)
		{
			
			SwapBytes(str, str + j, 1);
			printf("%s\n", str);
			
		}
		/*SwapBytes(str, str + i, 1);*/
	}	
}

int main()
{
	char str[] = "ABC";

	PrintPermutations(str);

	return 0;
}
