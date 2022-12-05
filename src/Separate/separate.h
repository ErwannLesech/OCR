#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Uint32 take_pixel(SDL_Surface *surface, int x, int y);
void change_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
SDL_Surface** separate(SDL_Surface* surface);
void save_image_cut(SDL_Surface** surfaces);
SDL_Surface* clear(SDL_Surface* surface);
