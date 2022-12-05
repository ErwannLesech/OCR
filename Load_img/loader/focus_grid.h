#pragma once
#include <SDL2/SDL.h>
#include "find_square.h"
SDL_Surface * focus_grid(SDL_Surface * sdl, struct Squares squares);
void registerSurface(SDL_Surface * sdl, struct Squares squares);