#include <pthread.h> /* pthread_create, pthread_join */
#include <stdio.h>   /* malloc, free 				 */
#include <stdlib.h>  /* printf						 */

#include "photoutils.h"

#define filterWidth 3
#define filterHeight 3

typedef struct image_thread it_t;

struct image_thread
{
	BMP_IMAGE *image;
	BMP_IMAGE *new_image;
	int height_start;
	int height_stop;	
	int width_start;
	int width_stop;
};

it_t *CreateThreadStruct(BMP_IMAGE *image,
						 BMP_IMAGE *new_image,
						 int height_start,
						 int height_stop,	
						 int width_start,
						 int width_stop);

void *FilterImage(void *image_thread);

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
	pthread_t t1, t2, t3, t4;
	it_t *t_info1 = NULL;
	it_t *t_info2 = NULL;
	it_t *t_info3 = NULL;
	it_t *t_info4 = NULL;
	BMP_IMAGE *image = NULL;
	BMP_IMAGE *new_image = NULL;
	FILE *file = NULL;
	FILE *new_file = NULL;
	int height = 0;
	int width = 0;

	file = fopen("simphsons.bmp", "r");
	new_file = fopen("newSimphsons.bmp", "w");

	image = LoadImage(file);
	height = image->Header.height;
	width = image->Header.width;
	printf("height = %d\n", height);
	printf("width = %d\n", width);
	new_image = ConstructImage(image);

	t_info1 = CreateThreadStruct(image,
						 		   new_image,
						           0,
								   height / 2,	
								   0,
								   width / 2);
	if (NULL == t_info1)
	{
		DestructImage(image);
		DestructImage(new_image);
		return (EXIT_FAILURE);
	}


	t_info2 = CreateThreadStruct(image,
						 		   new_image,
						           0,
								   height / 2,	
								   width / 2,
								   width);
	if (NULL == t_info2)
	{
		free(t_info1);
		DestructImage(image);
		DestructImage(new_image);
		return (EXIT_FAILURE);
	}

	t_info3 = CreateThreadStruct(image,
						 		   new_image,
						           height / 2,
								   height,	
								   0,
								   width / 2);
	if (NULL == t_info3)
	{
		free(t_info1);
		free(t_info2);
		DestructImage(image);
		DestructImage(new_image);
		return (EXIT_FAILURE);
	}

	t_info4 = CreateThreadStruct(image,
						 		   new_image,
						           height / 2,
								   height,	
								   width / 2,
								   width);
	if (NULL == t_info4)
	{
		free(t_info1);
		free(t_info2);
		free(t_info3);
		DestructImage(image);
		DestructImage(new_image);
		return (EXIT_FAILURE);
	}


	SetFilterParams(Filter, 5, 5, somefactor, somebias);

	pthread_create(&t1, NULL, FilterImage, t_info1);
	pthread_create(&t2, NULL, FilterImage, t_info2);
	pthread_create(&t3, NULL, FilterImage, t_info3);
	pthread_create(&t4, NULL, FilterImage, t_info4);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);


	StoreImage(new_file, new_image);

	fclose(file);
	fclose(new_file);

	DestructImage(image);
	DestructImage(new_image);
	free(t_info1);
	free(t_info2);
	free(t_info3);
	free(t_info4);

	return 0;
}

void *FilterImage(void *image_thread)
{
	it_t *t_info = (it_t*)image_thread;

	BMP_IMAGE *image = t_info->image;
	BMP_IMAGE *new_image = t_info->new_image;
	RGB pixel;
	int height = image->Header.height;
	int i = 0;
	int j = 0;
	int height_start = t_info->height_start;
	int height_stop = t_info->height_stop;	
	int width_start = t_info->width_start;
	int width_stop = t_info->width_stop; 
	
	for(i = height_start; i < height_stop; ++i)
	{
		for (j = width_start; j < width_stop; ++j)
		{
			pixel = ApplyFilter(image, i, j);
			SetPixel(new_image, height - i - 1, j, pixel);
		}
	}

	return (new_image);
}

it_t *CreateThreadStruct(BMP_IMAGE *image,
						 BMP_IMAGE *new_image,
						 int height_start,
						 int height_stop,	
						 int width_start,
						 int width_stop)
{
	it_t *t_info = NULL;
	
	t_info = (it_t*)malloc(sizeof(it_t));

	if (NULL == t_info)
	{
		return (NULL);
	}

	t_info->image = image;
	t_info->new_image = new_image;
	t_info->height_start = height_start;
	t_info->height_stop = height_stop;
	t_info->width_start = width_start;
	t_info->width_stop = width_stop;

	return (t_info);
}
