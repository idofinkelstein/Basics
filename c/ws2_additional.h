#ifndef __WS2_ADDITIONAL_H__
#define __WS2_ADDITIONAL_H__

/*the function IsPalindrome() checks whether str is palindromw.
  returns 1 if true or 0 if false */
int IsPalindrome(const char *str);

/* the function SwapPointers swaps between 2 int pointers. */
void SwapPointers(int *ptr1, int *ptr2);

/* the function SevenBoom receives range of integers and prints to
   the screen the numbers except that divisble by 7 or the numbers
   containing 7, insted it will print BOOM. */
void SevenBoom(int from, int to);

/* the function RemoveSpaces removes extra white-spaces from the beginning,
   the end, and between the words in str. */
char *RemoveSpaces(char *str);

/* the function AddBigNumbers adds 2 very big numbers represent in string,
   and returns the result in a string. */
char *AddBigNumbers(char *num1, char *num2);

#endif /* __WS2_ADDITIONAL_H__ */
