
#include <stdio.h> /* printf */
#include <stdlib.h> /* free */
#include <string.h> /* all string library functions*/
#include <strings.h>
#include <assert.h>

size_t StrLen(const char *str)
{
	char *curr = (char*)str;

	assert(str);
	
	while ('\0' != *curr)
	{
		++curr;
	}

	return (curr - str);
}


char *StrCat(char *dest, const char *src)
{
   size_t dest_len = StrLen(dest);
   

   assert( src );
   assert( dest );

    while (*src)
    {
        dest[dest_len] = src[0];
        ++dest_len;
        ++src;
        
    }

   return (dest);
}

int main()
{
	
	char str1[] = "world!";
	char str2[20] = "hello ";
	char str3[] = "hello world!";
	char str4[20] = "";
	
	printf("*** testing StrCat and compare to strcat ***\n");
	printf("src = [%s]\n", str1);
	printf("dest = [%s]\n", str2);
	printf("StrCat's output = [%s]\n", StrCat(str2, str1));
	sprintf(str2, "hello ");
	printf("strcat's output = [%s]\n", strcat(str2, str1));

	printf("src = [%s]\n", str3);
	printf("dest = [%s]\n", str4);
	printf("StrCat's output = [%s]\n", StrCat(str4, str3));
	sprintf(str4, "%s", "");
	printf("strcat's output = [%s]\n", strcat(str4, str3));
	puts("");
	return 0;
}
