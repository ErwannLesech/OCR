#include "../Load_img/main.h"
#include "../Separate/separate.h"
#include "../Solver/solver.h"
#include "../Saved/main.h"

#include <err.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ocr(char* path)
{
	//MANU-ROTATE
	//VALENTIN
	main_load(path);    	

	//SEPARATE
	
	SDL_Surface* surface = IMG_Load(path);
	SDL_Surface **surfaces = separate(surface);
	for (int i = 0; i < 81; i++)
	{
		surfaces[i]= clear(surfaces[i]);
	}
	save_image_cut(surfaces);
	SDL_FreeSurface(surface);

	
	//IA
	//SOLVER
	//SAVED
}
