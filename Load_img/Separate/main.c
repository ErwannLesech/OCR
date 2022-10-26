#include "helper.h"
#include "separate.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_surface.h"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		errx(EXIT_FAILURE, "An image is needed");
	}

	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		errx(EXIT_FAILURE, "%s", SDL_GetError());

	SDL_Surface* grid = IMG_Load(argv[1]);

	/*SDL_Surface **surfaces = separate(grid);
	save_image(surfaces);*/

	SDL_FreeSurface(grid);
	
	SDL_Quit();

	return EXIT_SUCCESS;
}
