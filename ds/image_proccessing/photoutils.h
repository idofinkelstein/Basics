#pragma once

#ifdef __cplusplus
extern "C"
{
#endif


#include <stdio.h>

#pragma pack(1)
typedef struct
{
    unsigned char v[3];
} RGB;


typedef struct
{
    unsigned short bfType;      /* specifies the file type */
    unsigned int bfSize;        /* specifies the size in bytes of the bitmap file */
    unsigned int bfReserved;    /* reserved; must be 0 */
    unsigned int bOffBits;      /* species the offset in bytes from the bitmapfileheader to the bitmap bits */

    unsigned int size;
    unsigned int width, height;
    unsigned short planes;
    unsigned short bpp;
    unsigned int compression;
    unsigned int imagesize;
    unsigned int xresolution, yresolution;
    unsigned int colours;
    unsigned int impcolours;
} BMP_HEADER;

typedef struct
{
    BMP_HEADER Header;
    RGB* Matrix;
} BMP_IMAGE;
#pragma pack()


BMP_IMAGE* LoadImage(FILE* bmp);
BMP_IMAGE* ConstructImage(BMP_IMAGE* image);
void DestructImage(BMP_IMAGE* image);
void StoreImage(FILE* bmp, BMP_IMAGE* image);
RGB GetPixel(BMP_IMAGE* image, int x, int y);
void SetPixel(BMP_IMAGE* image, int x, int y, RGB pixel);
void SetFilterParams(double* filter, int h, int w, double factor, double bias);
RGB ApplyFilter(BMP_IMAGE* info, int x, int y);
void CalcPmfCdf(BMP_IMAGE* image, int PMF[][256], double CDF[][256]);


#ifdef __cplusplus
}
#endif /* __cplusplus */
