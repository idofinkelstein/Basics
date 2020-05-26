/**********************************
file name: ws8_macros.c
author: Ido Finkelstein
reviewer: Shahrazad Tarboush Sirhan
date: 26.5.2020
***********************************/

#include <stdio.h> /* printf */

#define MAX(A, B) ((A) > (B) ? (A) : (B))

#define MAX3(A, B, C) (((A) > (C) ? (A) : (C)) > (B) ? ((A) > (C) ? (A) : (C)) : (B))

#define SIZEOF_VAR(A) ((char*)(&(A) + 1) - (char*)&(A)) 

#define SIZEOF_TYPE(TYPE) ((long)(1 + (TYPE*)0))

int main()
{	
	int x = 34;
	long int y = 12;
	
	char a = 2;
	char b = 6;
	char c = 5;
	long l = 1;
	int *px = &x;

	/* testing MAX and MAX3 */
	printf("%ld\n", MAX(x, y));
	printf("%d\n", MAX3(a, b, c));

	/* SIZEOF_VAR*/
	printf("%ld\n", SIZEOF_VAR(a));	
	printf("%ld\n",SIZEOF_VAR(px));
	printf("%ld\n",SIZEOF_VAR(l));

	/* testing SIZEOF_TYPE */
	printf("%ld\n", SIZEOF_TYPE(char));	
	printf("%ld\n",SIZEOF_TYPE(int));
	printf("%ld\n",SIZEOF_TYPE(long));

	return 0;
}
