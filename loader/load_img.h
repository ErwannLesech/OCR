#ifndef LOAD_IMG_H
#define LOAD_IMG_H
#include <SDL2/SDL.h>

SDL_Surface* init_img(char* path);
void surface_to_grayscale_and_black_white(SDL_Surface* surface);
#endif