#include "photoutils.h"

#define filterWidth 3
#define filterHeight 3

   double embossFilter[3][3] =
{
   {-1, -1, +0},
   {-1, +0, +1},
   {+0, +1, +1}
};

double somefilter[5][5] =
{
   {0,  0, -1,  0,  0},
   {0,  0, -1,  0,  0},
   {0,  0,  4,  0,  0},
   {0,  0, -1,  0,  0},
   {0,  0, -1,  0,  0}
};

double somefactor = 1.0;
double somebias = 0.0;

double factor = 1.0;
double bias = 60.0;
static double* Filter = (double*)somefilter;

int main()
{
	BMP_IMAGE *image = NULL;
	BMP_IMAGE *new_image = NULL;
	FILE *file = NULL;
	FILE *new_file = NULL;
	int i = 0;
	int j = 0;
	int height = 0;
	int width = 0;
	RGB pixel;

	file = fopen("simphsons.bmp", "r");
	new_file = fopen("newSimphsons.bmp", "w");

	image = LoadImage(file);
	height = image->Header.height;
	width = image->Header.width;
	printf("height = %d\n", height);
	printf("width = %d\n", width);
	SetFilterParams(Filter, 5, 5, somefactor, somebias);

	new_image = ConstructImage(image);

	for(i = 0; i < height; ++i)
	{
		for (j = 0; j < width; ++j)
		{
			pixel = GetPixel(image, height - i - 1, j);
			SetPixel(new_image,  i, j, pixel);
		}
	}
	
	for(i = 0; i < height; ++i)
	{
		for (j = 0; j < width; ++j)
		{
			pixel = ApplyFilter(image, i , j);
			SetPixel(new_image, height - i - 1, j, pixel);
		}
	}

	StoreImage(new_file, new_image);

	fclose(file);
	fclose(new_file);

	DestructImage(image);
	DestructImage(new_image);

	return 0;
}
