#ifndef __WS2_STRING_H__
#define __WS2_STRING_H__

#include <stdio.h> /* size_t */

/* The strlen() function calculates the length of the string pointed to by
   s, excluding the terminating null byte ('\0'). */ 
size_t StrLen(const char *str);

/* The  strcmp()  function compares the two strings str1 and str2.  It returns
   an integer less than, equal to, or greater than zero if  str1  is  found,
   respectively, to be less than, to match, or be greater than str2. */
int StrCmp(const char *str1, const char *str2);

/* The  strcpy()  function  copies the string pointed to by src, including
   the terminating null byte ('\0'), to the buffer  pointed  to  by  dest.
   The  strings  may  not overlap, and the destination string dest must be
   large enough to receive the copy.  Beware  of  buffer  overruns!   (See
   BUGS.) */
char *StrCpy(char *dest, const char *src);

/* The  strncpy()  function is similar, except that at most n bytes of src
   are copied.  Warning: If there is no null byte among the first n  bytes
   of src, the string placed in dest will not be null-terminated. */
char *StrnCpy(char *dest, const char *src, size_t n);

/* The  strcasecmp()  function  performs  a byte-by-byte comparison of the
   strings str1 and str2, ignoring the case of the characters.  It returns  an
   integer  less  than,  equal  to,  or  greater than zero if str1 is found,
   respectively, to be less than, to match, or be greater than str2. */
int StrCaseCmp(const char *str1, const char *str2);

/* The  strdup()  function  returns  a  pointer to a new string which is a
   duplicate of the string s.  Memory for the new string is obtained  with
   malloc(3), and can be freed with free(3). */
char *StrDup(const char *str);

/* The  strchr() function returns a pointer to the first occurrence of the
   character c in the string str. */
char *StrChr(const char *str, int chr);

/* The  strcat() function appends the src string to the dest string, over‐
   writing the terminating null byte ('\0') at the end of dest,  and  then
   adds  a  terminating  null  byte.  The strings may not overlap, and the
   dest string must have enough space for the  result.   If  dest  is  not
   large  enough, program behavior is unpredictable; */
char *StrCat(char *dest, const char *src);

/* The strncat() function is similar, except that
   *  it will use at most n bytes from src; and
   *  src does not need to be null-terminated if it  contains  n  or  more
      bytes. */
char *StrnCat(char *dest, const char *src, size_t n);

/* The strstr() function finds the first occurrence of the substring nee‐
   dle in the string haystack.  The terminating null bytes ('\0') are not
   compared. */
char *StrStr(const char *haystack, const char *needle);

#endif  /* __WS2_STRING_H__ */
