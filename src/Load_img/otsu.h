
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void image_binarize(SDL_Surface *image);
void blur_filter(SDL_Surface* sdl_surface);
void median_filter(SDL_Surface *image);