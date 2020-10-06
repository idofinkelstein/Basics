#include <stdio.h>
#include <string.h>

int IsContainPalindrome(char *str)
{
	size_t len = strlen(str);
	size_t i = len / 2;

	if (len > 1 && len % 2 == 0 && str[i] == str[i - 1])
	{
		printf("Palindrome!\n");
		return 1;
	}

	if (len > 1 && len % 2 != 0 && str[i + 1] == str[i - 1])
	{
		printf("Palindrome!\n");

		return 1;
	}

	printf("Not a palindrome!\n");
	return 0;
	
}

int main()
{
	IsContainPalindrome("");
	IsContainPalindrome("d");
	IsContainPalindrome("asfng");
	IsContainPalindrome("3554");
	IsContainPalindrome("jhgfddvgrh");
	IsContainPalindrome("bbdhurmmm,gf");
	IsContainPalindrome("aa");

	return 0;
}
