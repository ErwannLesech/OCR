#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

int main_rotate(int argc, char** argv)
{
	if (argc != 4)
        	errx(EXIT_FAILURE, "Not enougth arguments");

	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		errx(EXIT_FAILURE, "%s", SDL_GetError());

	SDL_Surface* surface= IMG_Load(argv[2]);

	long int angler = strtol(argv[3], NULL, 10);
	
	SDL_Surface* turned;

	turned = rotozoomSurface(surface,angler, 1,10);
	
	SDL_FreeSurface(surface);

	SDL_SaveBMP(turned, "test2.bmp");
	
	SDL_FreeSurface(turned);
	
	SDL_Quit();
	
	return EXIT_SUCCESS; 
	
}

