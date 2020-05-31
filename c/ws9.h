/**********************
Author: Ido Finkelstein
File name: ws9.h
Reviewer: Gal Shvinkelstein
Date: 31/5/2020
***********************/

#ifndef __WS9_H__
#define __WS9_H__

/* fills the first n bytes of the memory area pointed to by
   str with the constant byte c. */
void *MemSet(void *str, int c, size_t n);

/*copies  n bytes from memory area src to memory area dest.
  The memory areas must not overlap. Use memmove(3) if the
  memory areas do overlap. */
void *MemCpy(void *dest, const void *src, size_t n);

/* copies n bytes from memory area src to memory area dest.
   The memory areas may overlap */
void *MemMove(void *dest, const void *src, size_t n);

/* converts the initial portion of the string pointed to by str to int */
int Atoi(const char *str);

/* converts int to base 10 string */
char *Itoa(int num, char *str_num);

/* converts int to base 2 (2's complement) string */
char *ItoaBin(int num, char *str_num);

/* reverses an array */
char *Reverse(char arr[]);

/* converts int to any base string */
char *ItoaAny(int num, char *str_num, int base);

/* converts the initial portion of the string in any base pointed to by str to int */
int AtoiAny(const char *str, char base);

/* prints the chars that appear in 2 arrays only */
void ThreeArrays(char *arr_a, char *arr_b, char *arr_c, size_t size_a,
				 						  size_t size_b, size_t size_c);


#endif /* __WS9_H__ */
