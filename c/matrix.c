#include <stdio.h>
#include <stdlib.h>

void Fill(int *A, size_t rows, size_t cols);
void Print(int *A, size_t rows, size_t cols);


int main()
{
    size_t rows = 7;
    size_t cols = 9;
    int *A = malloc(sizeof(int) * rows * cols);

    Fill(A, rows, cols);
    Print(A, rows, cols);


    free(A);
    return 0;
}

void Fill(int *A, size_t rows, size_t cols)
{
    size_t i,j;

    for ( i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; ++j)
        {
            A[j * rows + i] = i + j;
        }
    }  
}


void Print(int *A, size_t rows, size_t cols)
{
    /* int (*tmp)[cols] = (int (*)[cols])A; */
    size_t i,j;

    for ( i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; ++j)
        {
            printf("%d, ",A[j * rows + i]);
        }
        puts("");
    }  

    puts("");
}