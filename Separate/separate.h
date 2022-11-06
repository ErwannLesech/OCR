#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


SDL_Surface** separate(SDL_Surface* grid);
//SDL_Surface* Resize(SDL_Surface* gridCase);
void save_image_cut(SDL_Surface** surfaces);
