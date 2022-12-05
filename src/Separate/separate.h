#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


SDL_Surface** separate(SDL_Surface* surface);
void save_image_cut(SDL_Surface** surfaces);
SDL_Surface* clear(SDL_Surface* surface);
