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

static int A(void);
static int T(void);
static int Esc(void);

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
	int (*PtrLUT[256])(void);
	int i = 0;
	unsigned char c = '\0';
	int quit = TRUE;
	
	for (i = 0; i < 256; ++i)
	{
		PtrLUT[i] = NULL;
	}

	PtrLUT['A'] = A;
	PtrLUT['T'] = T;
	PtrLUT[ESC] = Esc;

	system("stty -icanon -echo");	
	
	while (quit)
	{
		c = (unsigned char)getchar();
		quit = (*PtrLUT[c])();
	}

	return 0;
}

static int A(void)
{
	puts("A pressed");
	
	return TRUE;
}

static int T(void)
{	
	puts("T pressed");
	
	return TRUE;
}

static int Esc(void)
{
	system("stty icanon echo");
	return FALSE;
}

int main ()
{
	If();
	Switch();	
	LUT();	

	return 0;
}


