#ifndef __INT64_H__
#define __INT64_H__

typedef struct Int64
{
    int lsi;
    int msi;
}Int64_t;


/*
	Use example:

Int64_t foo()
{
    Int64_t x1;

    x1 = Int64("783642356");

    return I64Add( I64Add((x1, Int64(5)), Int64(17) );
}

*/

Int64_t Int64(const char *val);

Int64_t Int64Add(Int64_t num1, Int64_t num2);

void Int64Assign(Int64_t *num1, Int64_t num2);

Int64_t I64CompAdd(Int64_t num1, Int64_t num2);

Int64_t I64Shiftl(Int64_t num, int shift);
Int64_t I64Shiftl2(Int64_t num, int shift);

int I64IsEqual(Int64_t num1, Int64_t num2);

Int64_t I64Tilde(Int64_t num);

#endif /* __INT64_H__ */
