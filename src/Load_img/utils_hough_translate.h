#pragma once
#include <SDL2/SDL.h>
#include "find_square.h"
struct Line
{
    int x_start;
    int y_start;
    int x_end;
    int y_end;
    int val;
    double theta;
};
struct Lines
{
    struct Line* lines;
    int size;
};
void change_mat(SDL_Surface * sdl_surface,struct Lines lines);

void draw_squares(SDL_Surface * sdl_surface, struct Squares squares);
void draw_points(SDL_Surface * sdl, struct Points points);