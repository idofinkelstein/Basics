/*****************
file name: ws4.c
author: ido finkelstein
reviewer: Ori Komemie
date: 14.5.2020
******************/

#include <stdio.h>	 /* printf, getchar */
#include <stdlib.h>  /* system          */

#define ESC 27
#define TRUE 1
#define FALSE 0

static int CharPressed(char);
static int Esc(char);

static int If(void)
{
	char c = '\0';

	system("stty -icanon -echo");	

	while(TRUE)
	{
		c = getchar();

		if (c == 'A')
		{
			printf("A pressed\n");
		}	
		else if (c == 'T')
		{
			printf("T pressed\n");
		}		
		else if(c == ESC)
		{
			system("stty icanon echo");	
			return 0;
		}
	}	
}

static int Switch(void)
{
	char c = '\0';

	system("stty -icanon -echo");	

	while(TRUE)
	{
		c = getchar();

		switch(c)
		{
			case 'A':
				puts("A pressed");
				break;
			case 'T':
				puts("T pressed");
				break;
			case ESC:
				system("stty icanon echo");	
				return 0;
			default:
				break;
		}
	}	
}

static int LUT(void)
{
	static int (*PtrLUT[256])(char);
	int i = 0;
	char c = '\0';
	char no_esc = ESC;
	
	for (i = 0; i < 256; ++i)
	{
		PtrLUT[i] = NULL;
	}

	PtrLUT['A'] = CharPressed;
	PtrLUT['T'] = CharPressed;	
	PtrLUT[ESC] = Esc;

	system("stty -icanon -echo");	
	
	while (no_esc)
	{
		c = getchar();
	
		if (PtrLUT[(unsigned char)c] != NULL)
		{
			no_esc = PtrLUT[(unsigned char)c](c);
		}	
	}

	return 0;
}

static int CharPressed(char c)
{
	printf("%c pressed\n", c);
	
	return TRUE;
}

static int Esc(char c)
{
	c = FALSE;

	system("stty icanon echo");

	return (c);
}

int main ()
{
	If();
	Switch();	
	LUT();	

	return 0;
}


