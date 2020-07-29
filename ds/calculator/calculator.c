/**********************
File name: calculator.c
Author: Ido Finkelstein
Reviewer: Ori Barak
Date: 29/7/2020
***********************/

#include <stdlib.h> /* malloc, free, strtod */
#include <string.h> /* strlen */
#include <assert.h>

#include "calculator.h"

#define MULTI 42
#define DIV 47
#define ADD 43
#define SUB 45

typedef struct token
{
	char* (*char_check)(f_stack_t *numbers, c_stack_t *operators, char *input);
	void (*operation)(f_stack_t *numbers, c_stack_t *operators);
	int precedene;
}token_t;

/* utility functions declaration */
static void DoNothing(f_stack_t *numbers, c_stack_t *operators);
static char *PushOperator(f_stack_t *numbers, c_stack_t *operators, char *input);
static char *open_bracket(f_stack_t *numbers, c_stack_t *operators, char *input);
static char *close_bracket(f_stack_t *numbers, c_stack_t *operators, char *input);
static char *ToDo(f_stack_t *numbers, c_stack_t *operators, char *input);
static void Operate(f_stack_t *numbers, c_stack_t *operators);
static char *Insert(f_stack_t *numbers, c_stack_t *operators, char *input);
static void InitArray();
static token_t g_lut[128];



float Calculator(const char *input)
{
	size_t len = strlen(input);
	float sum = 0;
	static int initiated = 0;

	f_stack_t *numbers = FStackCreate(len);
	c_stack_t *operators = CStackCreate(len);

	if (!initiated)
	{
		initiated = 1;
		InitArray();
	}
	
	while ('\0' != *input)
	{
		input = g_lut[(size_t)*input].char_check(numbers, operators, (char*)input);
	}

	while (!CStackIsEmpty(operators))
	{
		Operate(numbers,operators);
	}

	sum = FStackPeek(numbers);

	FStackDestroy(numbers);
	CStackDestroy(operators);

	return (sum);
}

static char *open_bracket(f_stack_t *numbers, c_stack_t *operators, char *input)
{
	assert(operators);

	(void)numbers;

	CStackPush(operators, *input);
	++input;

	return (input);
}

static char *close_bracket(f_stack_t *numbers, c_stack_t *operators, char *input)
{
	assert(numbers);
	assert(operators);

	++input;

	while (CStackPeek(operators) != '(')
	{
		Operate(numbers, operators);
	}

	CStackPop(operators);

	return (input);
}

static char *Insert(f_stack_t *numbers, c_stack_t *operators, char *input)
{
	assert(numbers);

	(void)operators;

	FStackPush(numbers, (float)strtod(input, (char**)&input));

	return (input);
}

static void Operate(f_stack_t *numbers, c_stack_t *operators)
{
	float l_operand = 0;
	float r_operand = 0;
	float ret = 0;

	assert(numbers);
	assert(operators);
	 
	r_operand = FStackPeek(numbers);
	FStackPop(numbers);

	l_operand = FStackPeek(numbers);
	FStackPop(numbers);

	ret = (l_operand * r_operand) * (CStackPeek(operators) == MULTI) +
		  (l_operand / r_operand) * (CStackPeek(operators) == DIV) +
		  (l_operand + r_operand) * (CStackPeek(operators) == ADD) +
		  (l_operand - r_operand) * (CStackPeek(operators) == SUB);

	FStackPush(numbers, ret);
	CStackPop(operators);
}

static char *ToDo(f_stack_t *numbers, c_stack_t *operators, char *input)
{
	size_t operation = 0;

	assert(numbers);
	assert(operators);

	/* checks if stack is empty OR input operator bigger than previous operator,
	   empty stack returns 1 so it always wins */
	operation = (g_lut[(size_t)*input].precedene > 
			 	 g_lut[(size_t)CStackPeek(operators)].precedene) || CStackIsEmpty(operators);
	
	/* chooses operation according to result of previous statement */
	g_lut[operation].operation(numbers, operators);
	
	CStackPush(operators, *input);

	++input;

	return (input);
}

static char *PushOperator(f_stack_t *numbers, c_stack_t *operators, char *input)
{
	(void)numbers;

	assert(operators);

	CStackPush(operators, *input);

	return input;
}

static void DoNothing(f_stack_t *numbers, c_stack_t *operators)
{
	(void)(numbers);
	(void)(operators);
}

static void InitArray()
{
	g_lut[0].char_check = PushOperator;
	g_lut[0].operation = Operate;
	g_lut[1].char_check = PushOperator;
	g_lut[1].operation = DoNothing;

	g_lut['*'].char_check = ToDo;
	g_lut['/'].char_check = ToDo;
	g_lut['+'].char_check = ToDo;
	g_lut['-'].char_check = ToDo;
	g_lut['('].char_check = open_bracket;
	g_lut[')'].char_check = close_bracket;
	g_lut['0'].char_check = Insert;
	g_lut['1'].char_check = Insert;
	g_lut['2'].char_check = Insert;
	g_lut['3'].char_check = Insert;
	g_lut['4'].char_check = Insert;
	g_lut['5'].char_check = Insert;
	g_lut['6'].char_check = Insert;
	g_lut['7'].char_check = Insert;
	g_lut['8'].char_check = Insert;
	g_lut['9'].char_check = Insert;
	g_lut['.'].char_check = Insert;

	g_lut['*'].operation = Operate;
	g_lut['/'].operation = Operate;
	g_lut['+'].operation = Operate;
	g_lut['-'].operation = Operate;
	g_lut['('].operation = Operate;
	g_lut[')'].operation = Operate;
	g_lut['0'].operation = NULL;
	g_lut['1'].operation = NULL;
	g_lut['2'].operation = NULL;
	g_lut['3'].operation = NULL;
	g_lut['4'].operation = NULL;
	g_lut['5'].operation = NULL;
	g_lut['6'].operation = NULL;
	g_lut['7'].operation = NULL;
	g_lut['8'].operation = NULL;
	g_lut['9'].operation = NULL;
	g_lut['.'].operation = NULL;

	g_lut['*'].precedene = 3;
	g_lut['/'].precedene = 3;
	g_lut['+'].precedene = 2;
	g_lut['-'].precedene = 2;
	g_lut[')'].precedene = 1;
	g_lut['('].precedene = 0;
	g_lut['0'].precedene = 0;
	g_lut['1'].precedene = 0;
	g_lut['2'].precedene = 0;
	g_lut['3'].precedene = 0;
	g_lut['4'].precedene = 0;
	g_lut['5'].precedene = 0;
	g_lut['6'].precedene = 0;
	g_lut['7'].precedene = 0;
	g_lut['8'].precedene = 0;
	g_lut['9'].precedene = 0;
	g_lut['.'].precedene = 0;
}

	/*if (CStackIsEmpty(operators))  if 1
	{

		CStackPush(operators, *input);
		++input;
		return (input);

	} */
	/* if input operator > prev operator : -> push input  (1) */
	/*else if (g_lut[(size_t)*input].precedene > 
			 g_lut[(size_t)CStackPeek(operators)].precedene)
	{

		CStackPush(operators, *input);

	}
*/
	/* if input operator < prev operator : -> perform operation on prev operator and push input  (0) */
	/*else
	{
		g_lut[(size_t)CStackPeek(operators)].operation(numbers, operators);
		CStackPush(operators, *input);
	}
*/


