#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "photoutils.h"


#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)


static double defaultFilter[3][3] =
{
   { 0,0,0 },
   { 0,1,0 },
   { 0,0,0 }
};

static int FilterWidth = 3, FilterHeight = 3;
static double* Filter = (double*)defaultFilter;
static double Factor = 1.0;
static double Bias = 0.0;


BMP_IMAGE* LoadImage(FILE* bmp)
{
    int i;
    BMP_IMAGE* image = malloc(sizeof(BMP_IMAGE));

    fread(&image->Header, 1, sizeof(image->Header), bmp);

    image->Matrix = malloc(image->Header.width * image->Header.height * sizeof(RGB));
    if (image->Matrix == NULL)
        {return NULL;}

	
    /* read image upside down (glTexImage2D) */
    for (i = image->Header.height-1; i >= 0; --i)
    {
        fread(&image->Matrix[i * image->Header.width], 1, image->Header.width * sizeof(RGB), bmp);
    }

    return image;
}


BMP_IMAGE* ConstructImage(BMP_IMAGE* image)
{
    BMP_IMAGE* newImage = malloc(sizeof(BMP_IMAGE));

    memcpy(newImage, image, sizeof(image->Header));

    newImage->Matrix = malloc(image->Header.width * image->Header.height * sizeof(RGB));
    if (newImage->Matrix == NULL)
        return NULL;

    return newImage;
}


void DestructImage(BMP_IMAGE* image)
{
    if (image != 0)
    {
        free(image->Matrix);
        free(image);
    }
}


void StoreImage(FILE* bmp, BMP_IMAGE* image)
{
    fwrite(image, 1, offsetof(BMP_IMAGE,Matrix), bmp);
    fwrite(image->Matrix, 1, image->Header.width * image->Header.height * sizeof(RGB), bmp);
}


RGB GetPixel(BMP_IMAGE* image, int x, int y)
{
    return image->Matrix[x * image->Header.width + y];
}


void SetPixel(BMP_IMAGE* image, int x, int y, RGB pixel)
{
    image->Matrix[x * image->Header.width + y] = pixel;
}


void SetFilterParams(double* filter, int h, int w, double factor, double bias)
{
    Filter = filter;
    FilterHeight = h;
    FilterWidth = w;
    Factor = factor;
    Bias = bias;
}


RGB ApplyFilter(BMP_IMAGE* image, int x, int y)
{
    int xf, yf, i,x_index, y_index;
    double doublePix[3] = { 0.0, 0.0, 0.0 };
    RGB pixel;

    /* multiply every value of the filter with corresponding image pixel */
    for(xf = 0; xf < FilterHeight; ++xf)
    for(yf = 0; yf < FilterWidth; ++yf)
    {
		x_index = min(max(x + xf - 1, 0),image->Header.height - 1);
		y_index = min(max(y + yf - 1, 0),image->Header.width - 1);

		pixel = GetPixel(image, x_index, y_index);
	

        for (i=0; i < sizeof(pixel.v); ++i)
        {
            doublePix[i] += pixel.v[i] * Filter[xf * FilterWidth + yf];
        }
    }

    for (i=0; i < sizeof(pixel.v); ++i)
    {
        pixel.v[i] = min(max((int)(doublePix[i]*Factor + Bias),0), 255);
    }

    return pixel;
}


void CalcPmfCdf(BMP_IMAGE* image, int PMF[][256], double CDF[][256])
{
    int i, j, k, nPixels = image->Header.height * image->Header.width;
    int acc[3] = { 0,0,0 };

    memset(PMF, 0, 3 * sizeof(PMF[0]));

    for (i=0; i < image->Header.height; ++i)
    {
        for (j=0; j < image->Header.width; ++j)
        {
            RGB pixel = GetPixel(image, i, j);

            for (k=0; k < 3; ++k)
                PMF[k][pixel.v[k]]++;
        }
    }

    for (i=0; i < 256; ++i)
    {
        for (k=0; k < 3; ++k)
        {
            acc[k] += PMF[k][i];
            CDF[k][i] = (double)acc[k] / nPixels;
        }
    }
}
