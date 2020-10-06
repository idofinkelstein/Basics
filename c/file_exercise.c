#include <stdio.h>
#include <string.h>

int main()
{
	char str[100] = "abcd";
	char str2[100] = "abcd";
	char c;
	FILE *file_ptr;
		

	/* take input from stdin and write it into str */
	fgets(str, 100, stdin);	
	
	/* open or create file for writing */
	 file_ptr = fopen("txt.txt", "w");
	
	/* write to file pointed to by file_ptr the content of str */
	fwrite(str, sizeof(char), strlen(str), file_ptr); 

	fclose(file_ptr);
	
	/* open file for reading */
	file_ptr = fopen("txt.txt", "r");

	/* take the char pointed to by file_ptr and assigned
	   it to c */
	while ((c = fgetc(file_ptr)) != EOF)
	{
		printf("%c", c);
	}

	fclose(file_ptr);

	file_ptr = fopen("txt.txt", "r");

	/* read the file pointed to by file_ptr and write it to str */
	fread(str2, sizeof(char), strlen(str), file_ptr); 

	fclose(file_ptr);

	/* open or create file for appending */
	file_ptr = fopen("txt.txt", "a");

	fgets(str, 100, stdin);

	fwrite(str, sizeof(char), strlen(str), file_ptr);

	fclose(file_ptr);

	printf("%s", str2);

	return 0;
}
