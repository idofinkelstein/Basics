/*---Interview questions----*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    size_t row;
    size_t col;
}point;


/* Interview question functions */
char *URLify(char *str, size_t r_len);
int IsPermutationOfPalindrome(char *str);
int IsEditedOnce(char *str1, char *str2);
int *Rotate90(int *A, size_t n);
void ZeroRC(int *A, size_t n, size_t m);
/* Test functions */
void URLifyTest();
void IsPermutationOfPalindromeTest(void);
void Rotate90Test();
void IsEditedOnceTest();
void ZeroRCTest();
void PrintMatrix(int *mat, size_t rows, size_t cols);



/*---------------------------------------------------------------------------*/
int main()
{
    URLifyTest();
    IsPermutationOfPalindromeTest();
    IsEditedOnceTest();
    Rotate90Test();
    ZeroRCTest();

    return 0;
}
/*---------------------------------------------------------------------------*/
char *URLify(char *str, size_t r_len)
{
    char *sub = "%20", *curr = str;
    size_t len = strlen(str);

    while (r_len)
    {
        if (*str == ' ')
        {
            memmove(str + 3, str + 1, r_len+1);
            memcpy(str, sub, 3);
            str += 3;
            r_len -= 3;
        }
        else
        {
            ++str;
            --r_len;
        }
    }

    return curr;
}
/*---------------------------------------------------------------------------*/
int IsPermutationOfPalindrome(char *str)
{
    size_t len = strlen(str);
    int table[128] = {0}, table_sum = 0;
    int i = 0;

    for (i = 0; i < len; ++i)
    {
        if (str[i] != ' ' && table[str[i]] == 0)
        {
            table[str[i]]++;
        }
        else if (str[i] != ' ' && table[str[i]] == 1)
        {
            table[str[i]]--;
        }
    }
    for (i = 0; i < 128; ++i)
    {
        table_sum += table[i];
    }

    return (table_sum == 1) || (table_sum == 0);
}
/*---------------------------------------------------------------------------*/


int IsEditedOnce(char *str1, char *str2)
{
    size_t len1 = strlen(str1), len2 = strlen(str2), len = 0;
    int found = 0, i = 0;
    int table[128] = {0};

    if (len1 == len2)
    {
        for (i = 0; i < len1; ++i)
        {
            if (str1[i] != str2[i])
            {
                if (found)
                {
                    return 0;
                }
                found = 1;
            }
        }
        return 1;
    }

    else if(len1 + 1 == len2 || len2 + 1 == len1)
    {
        if (len1 > len2)
        {
            table[str1[len1 - 1]]++;
            len = len2;
        }
        else
        {
            table[str2[len2 - 1]]++;
            len = len1;
        }
        for (i = 0; i < len; ++i)
        {
            table[str1[i]]++;
            table[str2[i]]++;
        }
        for (i = 0; i < 128; ++i)
        {
            if (table[i] == 1)
            found += 1;
        }
        return found  == 1;
    }

    return 0;
}

int *Rotate90(int *A, size_t n)
{
    int i = 0, j = 0;
    int temp = 0;
    size_t k = n;
#if 1
    int *B = malloc(sizeof(int) * n * n);
    if (!B) {return NULL;}
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            B[j * n + (n - i - 1)] = A[i * n + j];
        }
    }
#else


    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < k; ++j)
        {
            temp = A[i * n + j];
            A[i * n + j] = A[j * n + (n - i - 1)];
            A[j * n + (n - i - 1)] = temp;
        }
        --k;
    }
    

#endif
    return B;
    /* return A; */
}

void ZeroRC(int *A, size_t n, size_t m)
{
    int i = 0, j = 0, k = 0,t = 0;
    int cnt = 0;
    point *p;

    /* get num of null cells */
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j)
        {
            if (A[i * m + j] == 0)
            {++cnt;}
        }
    }

    p = malloc(cnt * sizeof(point));

    /* set array of rows and cols of null cells */
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j)
        {
            if (A[i * m + j] == 0)
            {
                p[k].row = i;
                p[k].col = j;
                ++k;
            }
        }
    }
  
    /* nullify rows and cols containing zero */
    for (t = 0; t < cnt; t ++)
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < m; ++j)
            {
                if (i == p[t].row || j == p[t].col)
                {
                    A[i * m + j] = 0;
                }
            }
        }   
    }
    free(p);
}

void IsPermutationOfPalindromeTest(void)
{
    char str[] = "tact coa";
    char str2[] = "dddkkazaz";
    char str3[] = " ffhtrejedssd";
    puts("---------------testing IsPermutationOfPalindrome----------------");
    puts(str);
    printf("Is [%s] Permutation Of Palindrome: %d\n", str, IsPermutationOfPalindrome(str));
    printf("Is [%s] Permutation Of Palindrome: %d\n", str2, IsPermutationOfPalindrome(str2));
    printf("Is [%s] Permutation Of Palindrome: %d\n", str3, IsPermutationOfPalindrome(str3));
    puts("");

}


void URLifyTest()
{
    char str[] = "Mr Jhon Smith    ";
    puts("---------------testing URLify----------------");
    puts(str);
    URLify(str, 13);
    puts(str); 
    puts("");
}

void IsEditedOnceTest()
{
    char str1[] = "pale";
    char str2[] = "ple";
    char str3[] = "pales";
    char str4[] = "pale";
    char str5[] = "pale";
    char str6[] = "bale";
    char str7[] = "pale";
    char str8[] = "bae";

    puts("---------------testing IsEditedOnce----------------");

    printf("Are [%s] and [%s] edited once: %d\n", str1, str2, IsEditedOnce(str1, str2));
    printf("Are [%s] and [%s] edited once: %d\n", str3, str4, IsEditedOnce(str3, str4));
    printf("Are [%s] and [%s] edited once: %d\n", str5, str6, IsEditedOnce(str5, str6)); 
    printf("Are [%s] and [%s] edited once: %d\n", str7, str8, IsEditedOnce(str7, str8));
    puts("");

}

void Rotate90Test()
{
    int i = 0, j = 0, k = 1;
    size_t n = 3;
    int *A = malloc(sizeof(int) * n * n);
    int *B;
    if (!A) {return;}

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            A[i * n + j] = k++;
        }
    }

    puts("---------------testing Rotate90----------------");

    PrintMatrix(A, n, n);
    B = Rotate90(A, n);
    PrintMatrix(B, n, n);

    free(A);
    free(B);
}
void ZeroRCTest()
{
    int i = 0, j = 0, k = 1;
    size_t n = 3, m = 4;
    int *A = malloc(sizeof(int) * n * m);
    if (!A) {return;}

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j)
        {
            A[i * m + j] = k++;
        }
    }
    A[7] = 0;
    A[5] = 0;
    puts("---------------testing ZeroRC----------------");

    PrintMatrix(A,n,m);
    ZeroRC(A,n,m);
    PrintMatrix(A,n,m);
    free(A);
}

void PrintMatrix(int *mat, size_t rows, size_t cols)
{
    int i,j;

    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < cols; ++j)
        {
            printf("%d, ", mat[i * cols + j]);
        }
        puts("");
    }
    puts("");
}