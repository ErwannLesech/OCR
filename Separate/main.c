#include "separate.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"


int main_separate(int argc, char** argv)
{
	//Verify the number of arguments
	if (argc != 3)
	{
		errx(EXIT_FAILURE, "An image is needed");
	}
	
	//Init the SDL
	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	
	// Creat a surface from the path
	SDL_Surface* surface = IMG_Load(argv[2]);
	
	//Separate + save the surface
	SDL_Surface **surfaces = separate(surface);
	save_image_cut(surfaces);

	SDL_FreeSurface(surface);
	
	SDL_Quit();

	return EXIT_SUCCESS;
}
