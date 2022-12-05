#pragma once
#include <SDL2/SDL.h>
#include "utils_hough_translate.h"

SDL_Surface* rotate_img(SDL_Surface* surface, double degree);
int auto_rot(struct Lines lines);