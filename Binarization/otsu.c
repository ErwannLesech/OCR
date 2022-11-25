#include "otsu.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
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
}
*/


void print_histo(int *histo, int x)
{
	for(int i = 0; i < x; i++)
	{
		printf("%15i", histo[i]);

		if((i+1)%10 == 0)
		{
			printf("\n");
		}
	}
}


int *build_histo(SDL_Surface *image)
{
	int *histo = calloc(256, sizeof(int));
	Uint32 *pixels = image->pixels;
	SDL_PixelFormat *format = image->format;

	for (int height = 0; height < image->h; height++)
	{
		for (int width = 0; width < image->w; width++)
		{
			Uint8 r,g,b;
			SDL_GetRGB(pixels[height * (image->w) + width], format, &r, &g, &b);   
			histo[r]++;
        	}
    	}
	
	print_histo(histo, 256);
    	return histo;
}


void image_binarize(SDL_Surface *image)
{
	int *histo = build_histo(image);
	//int threshold = get_threshold(image);

	Uint32 *pixels = image->pixels;
	SDL_PixelFormat *format = image->format;

	/*for (int height = 0; height < image->h; height++)
    	{
        	for (int width = 0; width < image->w; width++)
        	{
            		Uint8 r, g, b;
			int index = height * (image->w) + width;
            		SDL_GetRGB(pixels[i], format, &r, &g, &b);

            		if (r > threshold)
			{
                		pixels[i] = SDL_MapRGB(format, 255, 255, 255);
			}

            		else
			{
                		pixels[i] = SDL_MapRGB(format, 0, 0, 0);
			}
        	}
    	}*/

	free(histo);
}

/*
 * NOT WORKING ENOUGHT SADDLY
*/
/*Uint8 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format)
{
    Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);
    Uint8 average = 0.3*r + 0.59*g + 0.11*b;
    //Uint8 average = 0.34*r + 0.33*g + 0.33*b;
    r = g = b = average;
    return average;
    //Uint32 color = SDL_MapRGB(format, r, g, b);
    //printf("%i: %i\n", average, color);
    //return color;
    
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
	
	//int temp[25];
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

	//for(int col = 0; col < width; col++)
	//{
	//	array[0][col] = pixel_to_grayscale(pixels[col*height], format);
	//	arr[0][col] = 0;
	//}

	//print_array(array, height, width);

	for(int row = 1; row < height-1; row++)
	{
		//int temp2[6];
            	//temp2[0] = array[row-1][0];
            	//temp2[1] = array[row-1][1];
            	//temp2[2] = array[row][0];
            	//temp2[3] = array[row][1];
            	//temp2[4] = array[row+1][0];
            	//temp2[5] = array[row+1][1];

		//insertion_sort(temp2, 6);
            	//arr[row][0] = temp2[3];

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

			//temp[0] = array[row-2][col-2];
            		//temp[1] = array[row-2][col-1];
            		//temp[2] = array[row-2][col];
            		//temp[3] = array[row-2][col+1];
            		//temp[4] = array[row-2][col+2];
            		//temp[5] = array[row-1][col-2];
            		//temp[6] = array[row-1][col-1];
            		//temp[7] = array[row-1][col];
            		//temp[8] = array[row-1][col+1];
			//temp[9] = array[row-1][col+2];
            		//temp[10] = array[row][col-2];
            		//temp[11] = array[row][col-1];
            		//temp[12] = array[row][col];
            		//temp[13] = array[row][col+1];
            		//temp[14] = array[row][col+2];
            		//temp[15] = array[row+1][col-2];
            		//temp[16] = array[row+1][col-1];
            		//temp[17] = array[row+1][col];
			//temp[18] = array[row+1][col+1];
            		//temp[19] = array[row+1][col+2];
            		//temp[20] = array[row+2][col-2];
            		//temp[21] = array[row+2][col-1];
            		//temp[22] = array[row+2][col];
            		//temp[23] = array[row+2][col+1];
            		//temp[24] = array[row+2][col+2];

            		insertion_sort(temp, 9);
            		arr[row][col] = temp[4];
			//arr[row][col] = temp[12];
		}
	}
	
	for(int a = 0; a < height; a++)
	{
		for(int b = 0; b < width; b++)
		{
			//if(arr[a][b] >= 8000000)
			//{
			//	pixels[a * width + b] = SDL_MapRGB(format, 255, 255, 255);
			//}

			//else
			//{
			//	pixels[a * width + b] = SDL_MapRGB(format, 0, 0, 0);
			//}

			pixels[a * width + b] = SDL_MapRGB(format, arr[a][b], arr[a][b], arr[a][b]);
		}
	}

	//print_array(array, height, width);
	//print_array(arr, height, width);
	free(array);
	free(arr);
}*/
