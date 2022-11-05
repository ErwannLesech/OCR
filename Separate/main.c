#include "separate.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL/SDL.h>
#include "SDL/SDL_image.h"


int main_separate(int argc, char** argv)
{
	if (argc != 3)
	{
		errx(EXIT_FAILURE, "An image is needed");
	}

	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		errx(EXIT_FAILURE, "%s", SDL_GetError());

	SDL_Surface* grid = IMG_Load(argv[2]);

	SDL_Surface **surfaces = separate(grid);
	save_image(surfaces);

	SDL_FreeSurface(grid);
	
	SDL_Quit();

	return EXIT_SUCCESS;
}
