/*******************************************
* File Name: utility.h					   *
* Name: Matan Yankovich				       *
* Topic: Utilitys						   *
********************************************/
#include <stdio.h>		/* printf */


#define UNUSED(x) (void)(x)
#define ALLOCATION_FAILED(COND, MSG, RET) if(COND){printf(MSG); RET;}
#define MEASURE_SIZE_OF_WORD sizeof(void*)
#define BITS_IN_BYTE 8
#define BYTES_IN_WORD 8
#define POINTERS_SCOPE(x) *(x*)
#define FREE_MEMORY_AND_POINTER(FLAG, POINTER) \
if (FLAG)\
{\
	free(POINTER);\
	(POINTER) = NULL;\
}

#define COPY_CHAR_ONE_BY_ONE(REMAINDER_TO_COPY, COND, TEMP_ARR, CHR) \
while ((REMAINDER_TO_COPY) > 0 && (COND))\
{\
	*(TEMP_ARR) = (CHR);\
	--(REMAINDER_TO_COPY);\
	++(TEMP_ARR);\
}

#define WRITE_STRING_END(STR, LENGTH) (*((STR) + (LENGTH)) = '\0')

/* minus sign */
#define MINUS 45

/* convert char to int number, 10 base */
#define CHAR_TO_TEN_BASE_NUMBER(x) ((int)x - 48)
/* convert char to int number, 36 base */
#define CHAR_TO_ANY_BASE_NUMBER(x) (((int)x > 96 && (int)x < 123) * (-87) +\
									((int)x > 64 && (int)x < 91) * (-55) +\
								    ((int)x > 47 && (int)x < 58) * (-48)) 
/* convert int to char, 10 base */
#define INT_TO_CHAR(x) ((char)x + 48)

#define MEASURE_NUMBER_LENGTH(x, BASE, COUNTER) (\
while (x)\
{\
	++COUNTER;\
	x /= BASE;\
}\
)

#define MAX(A,B) (A * (A > B) + B * (B >= A))

#define ASCII_TABLE_SIZE 128
#define CONVERT_INT_TO_CHAR 48

/* SList Additional */
#define SIMPLE_LIST_SIZE 3

enum number
{
	MINUS_ONE = -1,
	ZERO = 0,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN
};

typedef enum number number_t;


enum status
{
	SUCCESS = 0
};

typedef enum status status_t;

