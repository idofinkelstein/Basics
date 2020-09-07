#include <pthread.h> /* pthread_create, pthread_join */
#include <stdio.h>   /* malloc, free 				 */
#include <stdlib.h>  /* printf						 */

#include "photoutils.h"

#define filterWidth 3
#define filterHeight 3
#define NUM_OF_TRHEADS 4
static const unsigned num_of_threads = NUM_OF_TRHEADS;

typedef struct image_thread it_t;

struct image_thread
{
	BMP_IMAGE *image;
	BMP_IMAGE *new_image;
	int height_start;
	int height_stop;	
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
static double* Filter = (double*)embossFilter;

int main()
{
	pthread_t t[NUM_OF_TRHEADS];
	it_t *t_info = NULL;
	BMP_IMAGE *image = NULL;
	BMP_IMAGE *new_image = NULL;
	FILE *file = NULL;
	FILE *new_file = NULL;
	int status = 0;
	int height = 0;
	int width = 0;
	int num_of_lines = 0;
	int line_reminder = 0;
	unsigned i = 0;

	t_info = (it_t*)malloc(sizeof(it_t) * num_of_threads);

	if (NULL == t_info)
	{
		return(EXIT_FAILURE);
	}

	file = fopen("simphsons.bmp", "r");
	
	if (NULL == file)
	{
		free(t_info);
		return(EXIT_FAILURE);
	}

	new_file = fopen("newSimphsons.bmp", "w");

	if (NULL == new_file)
	{
		free(t_info);
		fclose(file);
		return(EXIT_FAILURE);
	}

	image = LoadImage(file);
	height = image->Header.height;
	width = image->Header.width;
	printf("height = %d\n", height);
	printf("width = %d\n", width);
	new_image = ConstructImage(image);

	/* sections the image height according to number of threads */
	num_of_lines += height / num_of_threads;	
	line_reminder = height % num_of_threads;

	for (i = 0; i < num_of_threads; ++i)
	{
		(t_info + i)->height_start = num_of_lines * i;
		(t_info + i)->height_stop = num_of_lines * (i + 1);
		(t_info + i)->image = image;
		(t_info + i)->new_image = new_image;
	}

	/* adds the remain lines to last thread */
	(t_info + --i)->height_stop += line_reminder;

	SetFilterParams(Filter, filterHeight, filterWidth, factor, bias);

	for (i = 0; i < num_of_threads && !status; ++i)
	{
		status = pthread_create(&t[i], NULL, FilterImage, t_info + i);
	}

	if (status) /* at least one thread creation failed */
	{
		fclose(file);
		fclose(new_file);

		DestructImage(image);
		DestructImage(new_image);
		free(t_info);

		return(EXIT_FAILURE);
	}
	
	for (i = 0; i < num_of_threads; ++i)
	{
		pthread_join(t[i], NULL);
	}

	StoreImage(new_file, new_image);

	fclose(file);
	fclose(new_file);

	DestructImage(image);
	DestructImage(new_image);
	free(t_info);

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
	int width = image->Header.width;
		
	for(i = height_start; i < height_stop; ++i)
	{
		for (j = 0; j < width; ++j)
		{
			pixel = ApplyFilter(image, i, j);
			SetPixel(new_image, height - i - 1, j, pixel);
		}
	}

	return (new_image);
}


