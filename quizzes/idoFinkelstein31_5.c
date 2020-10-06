#define MAX(A, B ,C) (((A) > (C) ? (A) : (C)) > (B) ? ((A) > (C) ? (A) : (C)) : (B)) 

#define TO_LOWER(a) (if((a) > 'A' && (a) < 'Z') { return (a) + ' ';} else { return (a); })

#define OFFSET (s, f) (return (((char*)&f) - ((char*)&s);)

/*s
{
	int num - 4byte
	char ch1 - 1byte
	pading   - 3 byte
	int ptr - 4 byte
	char ch2 - 1byte
	padding -  3byte 
}   size = 4 + 1 + 3 + 4 + 1 + 3 = 16byte

4.2 הכתובת צריכה להתחיל בערך שמתחלק במשתנה הגדול ביותר ולהסתיים בערך שמתחלק במשתנה הגדול ביותר.
5. ה s1 הוא משתנה של מבנה ללא שם.
6. 
7. (int)4byte + (5chars)5byte + (padding)3byte = 12

8. היגיון ונוחות קריאה למשל ברשימת אנשים כלשהיא נרצה את שם הבנאדם באיבר הראשון.
