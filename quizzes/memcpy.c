#include <stdio.h>

void *align(size_t what, size_t to);
size_t CreateByteMask(size_t num_of_bytes);


void *Memcpy(void *dest, const void *src, size_t n)
{
    const size_t addr_mask = sizeof(size_t) - 1;
    const size_t word = sizeof(size_t);
    size_t dest_offset = ((size_t)dest & addr_mask) ? word - ((size_t)dest & addr_mask) : 0;
    size_t src_offset = 0;
    size_t tail = dest_offset;
    void *work_src = (void*)src, *start = dest;
    size_t word_mask = 0;
    size_t bytes_to_shift = 0;

    printf("tail = %ld\n", tail);
    while (n-- && tail--)
    {
        *(char*)dest = *(char*)src;
        src = (char*)src + 1;
        dest = (char*)dest + 1;
    }

    src_offset = ((size_t)src & addr_mask) ? word - ((size_t)src & addr_mask) : 0;
    bytes_to_shift = (size_t)src & addr_mask;
    work_src = align((size_t)src, word);
    work_src = (size_t*)work_src - 1;
    word_mask = CreateByteMask(src_offset);

    while(n >= word)
    {
        *(size_t*)dest = (word_mask & *(size_t*)work_src) >> bytes_to_shift * word;
        work_src = (size_t*)work_src + 1;
        word_mask = ~word_mask;
        *(size_t*)dest = (word_mask & *(size_t*)work_src) << word * (word - bytes_to_shift);
        dest = (size_t*)dest + 1;
        word_mask = ~word_mask;
        n -= word;
        /* puts("hi"); */
    }


    while (n--)
    {
        *(char*)dest = *(char*)src;
        src = (char*)src + 1;
        dest = (char*)dest + 1;
    }

    return start;
}

void *align(size_t what, size_t to)
{
    return (void*)((what - 1 - to) & -to);
}

size_t CreateByteMask(size_t num_of_bytes)
{
    if(!num_of_bytes)
    {
        return ~0;
    }

    return ((1ul << num_of_bytes) - 1);
}

int main()
{
    int src[200] = {0};
    int dest[200] = {0};
    int i = 0;

    for (i = 0; i < 200; ++i)
    {
        src[i] = i;
    }

    Memcpy(dest, src, 800);

    for (i = 0; i < 150; ++i)
    {
        printf("%d\n", dest[i]);
    }

    return 0;
}