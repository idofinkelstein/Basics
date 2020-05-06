
#include <stdio.h> /* size_t */

size_t StrLen(const char *str);

int StrCmp(const char *str1, const char *str2);

char *StrCpy(char *dest, const char *src);

char *StrnCpy(char *dest, const char *src, size_t n);

int StrCaseCmp(const char *s1, const char *s2);

char *StrDup(const char *str);

char *StrChr(const char *str, int chr);

char *StrCat(char *dest, const char *src);


