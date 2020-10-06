קודים למבחן

#include<stdio.h>

int FlipDigitsInNum(int num)
{
	int fliped_num = 0;
	int is_negative = num < 0;
	int sign = -1;

	sign = -is_negative + !is_negative;
	num *= sign;

	while (num)
	{
		fliped_num += fliped_num * 10 + num % 10;

		num /= 10;
	} 

	return (fliped_num * sign);
}

2. the num is 0xCE99D8F7

3.. ערך לא מאותחל במשתנה auto מקומי שווה ל"זבל" - ערך קודם שהיה באותו תא זכרון.
משתנים גלובלים לא מאותחלים מאותחלים אוטומטית ע"י הקומפיילר ל0.


unsigned char MirrorByte(unsigned char byte)
{
	byte = (byte >> 4) | (byte << 4);

	byte = (byte & 0x33) << 2 | (byte & 0xCC) >> 2;

	byte = (byte & 0x55) << 1 | (byte & 0xAA) >> 1;

	return (byte);
}

4. השיטה המהירה ביותר היא ללא לולאה בסיבוכיות של logn.

5.
int FlipBit(int val, unsigned int n)
{
	return (val ^ (1u << n));
}

6.
size_t CountBits(unsigned char byte)
{
	size_t bits_on = 0;

	for (; byte; byte &= (byte - 1))
	{
		++bits_on;
	}

	return (bits_on);
} 
8.
char RotateLeft(char byte, unsigned int nbits)
{
	unsigned int bits_in_byte = 8;	

	if (nbits >= bits_in_byte)
	{
		nbits %= bits_in_byte;
	}

	return ((byte << nbits) | (byte >> (bits_in_byte - nbits)));
}
9. ה-endianess של המערכת תיקבע את כיוון הקריאה מהזכרון וזה יכול להשפיע על כיוון הכתיבה כך שבמערכת
אחרת זה יכול להקרא מהכיוון ההפוך.

10.
void SwapPtr(int **ptr1, int **ptr2)
{
	int *tmp = *ptr1;

	ptr1 = ptr2;
	*ptr2 = tmp;
}

size_t StrLen(char *str)
{
	char *start = str;

	while (*str)
	{
		++str;
	}

	return(str - start);
}

int StrCmp(char *str1, char *str2)
{
	while (*str1 && *str1 == *str2)
	{
		++str1;
		++str2;
	}

	return (*str1 - *str2);
}

char *StrCpy(char *dest, char *src)
{
	char *dest_start = dest;

	while (*src)
	{
		*(dest++) = *(src++);
	}

	*dest = '\0';

	return (dest_start);
}

char *StrnCpy(char *dest, char *src, size_t n)
{
	char *dest_start = dest;

	while (*src && n)
	{
		*(dest++) = *(src++);
		
		--n;
	}

	*dest = '\0';

	return (dest_start);
}

char *StrCat(char *dest, char *src)
{
	char *dest_start = dest;
	dest = dest + StrLen(dest);

	while (*src)
	{
		*(dest++) = *(src++)
	}

	*dest = '\0';

	return (dest_start);
}

unsigned long GetNFibonacciElement(unsigned int n)
{
	unsigned long *fib_arr = (unsigned long*)malloc(sizeof(unsigned long) * n);
	unsigned long res = 0;
	size_t i = 0;
	*fib_arr = 1;
	*(fib_arr + 1) = 1;

	if (NULL == fib_arr)
	{
		return 0;
	}
	
	if (0 == n)
	{
		printf("out of range\n");
		return 0;
	}

	for (i = 2; i < n; ++i)
	{
		fib_arr[i] = fib_arr[i - 1] + fib_arr[i - 2];
	}

	res = fib_arr[n - 1];

	free(fib_arr);

	return (res);
	
}

int IntToString(int num)
{
	char *str[12]; /* size: 10 digits max + sign + '\0' */

	sprintf(str, "%d", num);

	return (str);
}

long MultiplyBy8(int num)
{
	return ((long)num << 3);
}

void swap1(int *num1, int *num2)
{
	int *temp = num1;

	*num1 = *num2;
	*num2 = *temp;
}

void swap2(int *num1, int *num2)
{
	*num1 = *num1 + *num2;
	*num2 = *num1 - *num2;
	*num1 = *num1 - *num2;
}

void swap3(int *num1, int *num2)
{
	*num1 = *num1 ^ *num2;
	*num2 = *num1 ^ *num2;
	*num1 = *num1 ^ *num2;
}

15. השיטה הבטוחה ביותר שתמיד תעבוד היא השיטה בעזרת המשתנה עזר מכיוון שאין סכנה של over flow
וגם זה לא משנה אם שני המספרים בעלי אותה כתובת (אותו מספר נשלח פעמיים).

16. 8,8,5,5
segmentetion fault

17. כמו שכבר ראינו:
array[val] = val[array]
מכיוון ש:
*(array + val) = *(val + array)

התשובה שלי: 3.

18. א. משתנה בעל אורך חיים כאורך התכונית, זמין לכל הקובץ בו הוא קיים וזמין רק לו
ב. משתנה שאורך חייו כאורך התכנית מהרגע שנוצר, זמין רק לבלוק שבו הוא חיי וערכו נשמר בכל קריאה לבלוק זה.
ג. פונקציה שזמינה רק בקובץ שבו הוגדרה.
ד. לא מכיר.
ה. לא מכיר.

19. א. משתנה אוטומטי, בברירת מחדל של C משתנה שהוגדר בתוך פונקציה הוא אוטומטי. חיי רק בבלוק
שבו נמצא.
ב. זהו storage class. מאותתת לקומפיילר שהמשתנה הנ''ל יהיה בשימוש תדיר וכדי לשקול לשים אותו ברגיסטר. לא ניתן לקחת כתובת (&) למשתנה זה.
 בנוסף זה לא מחייב שהקומפיילר יבצע זאת.
ג. זהו qualifier. הגדרה מחייבת. אומר לקומפיילר לא לבצע אופטימיזציות על המשתנה הנ''ל מכיוון 
שיש סיכוי שרכיב חומרה כלשהוא שלא קשור לקוד עלול לפנות לאותה כתובת זכרון ולשנות את ערכה.
ד. לא זוכר
ה. הצהרה עבור משתנה גלובלי שהגדרתו נמצאת בקובץ אחר אבל יעשה בו שימוש בקובץ הנוכחי.

20. א. 4
ב. 4

21.

a. 4 + 1 + 1(padding) + 2 + 4 = 12
b. 8 + 1 + 5(padding) + 2 + 8 = 24

22.
a. 4 + 1 + 1(padding) + 2 + 4 + 1 + 3(padding) = 16
b. 4 + 1 + 1(padding) + 2 + 8 + 1 + 7(padding) = 24

23. א. jack הוא משתנה מסוג union בלי שם
ב. הגודל הוא 8.
ג. אני חושב שזה לא אפשרי מכיוון שאין שם לunion של jack.

