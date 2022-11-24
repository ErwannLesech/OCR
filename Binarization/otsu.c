#include "otsu.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/*static Uint8* image_get_pixel_ref(SDL_Surface *image, int h, int w)
{
    int bpp = image->format->BytesPerPixel;
    Uint8 *pixels = image->pixels;
    return pixels + h * image->pitch + w * bpp;
}


Uint32 image_get_pixel(SDL_Surface *image, int h, int w)
{
    Uint8 *p = image_get_pixel_ref(image, h, w);

    switch (image->format->BytesPerPixel)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *) p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *) p;
        break;

    default:
        return 0;
    }
}

void image_set_pixel(SDL_Surface *image, int h, int w, Uint32 pixel)
{
    Uint8 *p = image_get_pixel_ref(image, h, w);

    switch (image->format->BytesPerPixel)
    {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *) p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else
        {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *) p = pixel;
        break;

    default:
        break;
    }
}

int *get_histogram(SDL_Surface *image)
{
	int *histogram = calloc(256, sizeof(int));
	int *p = histogram;

	for (int height = 0; height < image->h; height++)
	{
		for (int width = 0; width < image->w; width++)
		{
			Uint8 r,g,b;
            		Uint32 pixel = image_get_pixel(image, height, width);
            		SDL_GetRGB(pixel, image->format, &r, &g, &b);
            
	    		histogram[r]++;
        }
    }

    return histogram;
}


int get_threshold(SDL_Surface *image)
{
	int threshold;
    	double current_max;
    	int sum;
    	int sum_background;
    	int weight_background;
    	int nb_pixels = image->h * image->w;

    	int *histogram = get_histogram(image);
    	for (int i = 0; i < 256; i++)
        	sum += i * histogram[i];

    	for (int i = 0; i < 256; i++)
    	{
        	weight_background += histogram[i];
        	int weight_foreground = nb_pixels - weight_background;
       		if (weight_background == 0 || weight_foreground == 0)
            		continue;

        	sum_background += i * histogram[i];
        	int sum_foreground = sum - sum_background;

        	double f_weight_background = weight_background;
        	double f_weight_foreground = weight_foreground;
        	double mean_background = sum_background / f_weight_background;
        	double mean_foreground = sum_foreground / f_weight_foreground;
        	double mean_diff = mean_background - mean_foreground;

        	double variance = f_weight_background * f_weight_foreground * mean_diff * mean_diff;
        	if (variance > current_max)
        	{
            		current_max = variance;
            		threshold = i;
        	}
    	}

    free(histogram);
    return threshold;
}


void image_binarize(SDL_Surface *image)
{
    int threshold = get_threshold(image);

    for (int h = 0; h < image->h; h++)
    {
        for (int w = 0; w < image->w; w++)
        {
            Uint8 r, g, b;
            Uint32 pixel = image_get_pixel(image, h, w);
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            Uint32 new_pixel;
            if (r > threshold)
                new_pixel = SDL_MapRGB(image->format, 255, 255, 255);
            else
                new_pixel = SDL_MapRGB(image->format, 0, 0, 0);
            image_set_pixel(image, h, w, new_pixel);
        }
    }
}*/

Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format)
{
    Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);
    Uint8 average = 0.3*r + 0.59*g + 0.11*b;
    r = g = b = average;
    Uint32 color = SDL_MapRGB(format, r, g, b);
    return color;
    
}

void insertion_sort(int arr[], int len)
{
    int key;
    int j;

    for(int i = 1; i < len; i++)
    {
        key = arr[i];
        j = i - 1;
 
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void print_array(int **array, int x, int y)
{
	for(int i = 0; i < x; i++)
	{
		for(int j = 0; j < y; j++)
		{
			//printf("%i ", array[i * y + j]);
			printf("%i ", array[i][j]);
		}

		printf("\n");
	}
}

void median_filter(SDL_Surface *image)
{
	const unsigned int height = image->h;
	const unsigned int width = image->w;
	int **array = malloc(height * sizeof(int*));
	int **arr = malloc(height * sizeof(int*));
	//int array[height * width];
	//int arr[height * width];
	//print_array(array, height, width);
	int temp[9];
	Uint32 *pixels = image->pixels;
	SDL_PixelFormat* format = image->format;

	for(int i = 0; i < height; i++)
	{
		array[i] = (int*)malloc(width * sizeof(int));
		arr[i] = (int*)malloc(width * sizeof(int));
	}
	
	//free(array);
	//free(arr);

	for(int row = 0; row < height; row++)
	{
		for(int col = 0; col < width; col++)
		{
			//printf("%i\n", pixel_to_grayscale(pixels[row * width + col], format));
			array[row][col] = pixel_to_grayscale(pixels[row * width + col], format);
			arr[row][col] = 0;
		}
	}

	/*for(int col = 0; col < width; col++)
	{
		array[0][col] = pixel_to_grayscale(pixels[col*height], format);
		arr[0][col] = 0;
	}*/

	//print_array(array, height, width);

	for(int row = 1; row < height-1; row++)
	{
		for(int col = 1; col < width-1; col++)
		{
			temp[0] = array[row-1][col-1];
            		temp[1] = array[row-1][col];
            		temp[2] = array[row-1][col+1];
            		temp[3] = array[row][col-1];
            		temp[4] = array[row][col];
            		temp[5] = array[row][col+1];
            		temp[6] = array[row+1][col-1];
            		temp[7] = array[row+1][col];
            		temp[8] = array[row+1][col+1];

            		insertion_sort(temp, 9);
            		arr[row][col] = temp[4];
		}
	}
	
	for(int a = 0; a < height; a++)
	{
		for(int b = 0; b < width; b++)
		{
			pixels[a * width + b] = arr[a][b];
		}
	}

	//print_array(array, height, width);
	//print_array(arr, height, width);
	free(array);
	free(arr);
}
