#include "otsu.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
	
	//print_histo(histo, 256);
    	return histo;
}


int get_threshold(SDL_Surface *image, int *histo)
{
	unsigned long sum = 0, sum_back = 0, total_back = 0;
	double weight_fore = 0, weight_back = 0;
    	double mean_fore = 0, mean_back = 0;
    	double variance = 0, max = 0;
    	int threshold1 = 0;
	int leng = image->w * image->h;

    	for(int i = 0; i < 256; i++)
	{
		sum += i * histo[i];
	}
	//printf("sum %lu", sum);

    	for(int i = 0; i < 256; i++)
    	{
        	total_back += histo[i];

		weight_back = (double)total_back / (double)leng;
		//printf("total_back %lu leng %i = %f ", total_back, leng, weight_back);
               	weight_fore = 1 - weight_back;
		//printf("weight_back %f weight_fore %f ", weight_back, weight_fore);

		sum_back += i * histo[i];
		//printf("sum_back %lu ", sum_back);
		
		if(total_back == 0 || total_back == leng)
		{
			continue;
		}

        	mean_back = sum_back / total_back;
		//printf("mean_back %f ", mean_back);
        	mean_fore = (sum - sum_back) / (leng - total_back);
		//printf("mean_fore %f \n", mean_fore);

        	variance = weight_back * weight_fore * (mean_back - mean_fore) * (mean_back - mean_fore);
		//printf("variance %f\n", i);

		if(variance >= max)
        	{
			//printf("threshold %i => variance %f\n", i, variance);
            		threshold1 = i;
            		max = variance;
        	}
    	}

    	//printf("threshold = %i\n", threshold1);
    	return threshold1;
}


void image_binarize(SDL_Surface *image)
{
	int *histo = build_histo(image);
	int threshold = get_threshold(image, histo);

	Uint32 *pixels = image->pixels;
	SDL_PixelFormat *format = image->format;

	for (int height = 0; height < image->h; height++)
    	{
        	for (int width = 0; width < image->w; width++)
        	{
            		Uint8 r, g, b;
			int index = height * (image->w) + width;
            		SDL_GetRGB(pixels[index], format, &r, &g, &b);

            		if (r >= threshold)
			{
                		pixels[index] = SDL_MapRGB(format, 0, 0, 0);
			}

            		else
			{
                		pixels[index] = SDL_MapRGB(format, 255, 255, 255);
			}
        	}
    	}
}    
/*
 * MEDIAN FILTER NOT WORKING ENOUGHT SADDLY
*/



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

void print_array_e(int **array, int x, int y)
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
}
