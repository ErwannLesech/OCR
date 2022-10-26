#pragma once
#include <SDL2/SDL.h>
struct Line
{
    int x_start;
    int y_start;
    int x_end;
    int y_end;
    int val;
};
struct Lines
{
    struct Line* lines;
    int size;
};
void change_mat(SDL_Surface * sdl_surface,struct Lines lines);