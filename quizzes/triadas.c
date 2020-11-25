#include <stdio.h>

/* n^3 solution */
size_t FindNumOfTriadas(int *arr, size_t size)
{
    size_t i, j, k, zero_count_sum = 0;

    for (i = 0; i < size; ++i)
    {
        for (j = i + 1; j < size; j++)
        {
            for (k = j + 1; k < size; k++)
            {
                if (i != j && i != k && k != j &&
                    arr[i] + arr[j] + arr[k] == 0)
                {
                    zero_count_sum++;
                }    
            }            
        }        
    }

    return (zero_count_sum);
}

