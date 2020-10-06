#include <stdio.h>
#include <string.h>

int IsRotation(char *str1, char *str2)
{
	size_t len = strlen(str1);
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	size_t match = 0;

	for (i = 0; i < len; ++i)
	{
		k = 0;		
	
		while (1)
		{
			if (str1[k] == str2[j])
			{
				++match;
				++k;
				j = (j + 1) % len;
			}
			else
			{
				match = 0;
				
				break;
			}

			if (match == len)
			{
				return 1;
			}
		}	
	}
	 
	return 0;
}

int main ()
{
	char *str1 = "12112345";
	char *str2 = "12345121";
	char *str3 = "12345121";
	char *str4 = "12112345";
	char *str5 = "121212123";
	char *str6 = "121231212";
	char *str7 = "121231212";
	char *str8 = "121212123";
	char *str9 = "111211131";
	char *str10 = "111311112";
	char *str11 = "111311112";
	char *str12 = "111211131";
	char *str13 = "131111111";
	char *str14 = "311111111";


	
	printf("%d\n", IsRotation(str1, str2));
	printf("%d\n", IsRotation(str3, str4));
	printf("%d\n", IsRotation(str5, str6));
	printf("%d\n", IsRotation(str7, str8));
	printf("%d\n", IsRotation(str9, str10));
	printf("%d\n", IsRotation(str11, str12));
	printf("%d\n", IsRotation(str13, str14));

	return 0;
}
