#include "otsu.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface* init_image(char* path)
{
    SDL_Surface* surface = IMG_Load(path);
    SDL_Surface* new_surface = SDL_ConvertSurfaceFormat(surface, 
        SDL_PIXELFORMAT_RGB888, 0);
    SDL_FreeSurface(surface);
    return new_surface;
}

int main_bin(char *filename)
{
	SDL_Surface *image = init_image(filename);
	
	//blur_filter(image);
	median_filter(image);
	blur_filter(image);
	image_binarize(image);
	//median_filter(image);

	IMG_SavePNG(image, "image_otsu.png");
	free(image);
	return EXIT_SUCCESS;
}

/*int main(int argc, char **argv)
{
	SDL_Surface *image = init_image(argv[1]);
	
	//blur_filter(image);
	median_filter(image);
	blur_filter(image);
	image_binarize(image);
	//median_filter(image);

	IMG_SavePNG(image, "image_otsu.png");
	free(image);
	return EXIT_SUCCESS;
}*/
