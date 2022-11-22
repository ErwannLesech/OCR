#include "otsu.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


int main(int argc, char **argv)
{
	//image_binarize(argv[1]);
	/*int arr[10] = {1, 12, 31, 4, 16, 18, 27, 2, 28, 27};
	insertionSort(arr, 10);
	for(int i = 0; i < 10; i++)
	{
		printf("%i, ",arr[i]);
	}*/

	median_filter(argv[1]);
	return EXIT_SUCCESS;
}
