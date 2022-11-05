#pragma once

#include <SDL/SDL.h>
#include "SDL/SDL_image.h"


SDL_Surface** separate(SDL_Surface* grid);
//SDL_Surface* Resize(SDL_Surface* gridCase);
void save_image(SDL_Surface** surfaces);
