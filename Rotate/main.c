#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

int main(int argc, char** argv)
{
	if (argc != 3)
        	errx(EXIT_FAILURE, "Erreur");

	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		errx(EXIT_FAILURE, "%s", SDL_GetError());

	SDL_Surface* surface= IMG_Load(argv[1]);

	long angler = (long)(argv[2]);

	SDL_Surface* turned = NULL;
	turned = rotozoomSurface(surface,(-angler), 1,1);

	SDL_SaveBMP(turned, "test.bmp");

	SDL_Quit();
	return EXIT_SUCCESS; 
	
}

