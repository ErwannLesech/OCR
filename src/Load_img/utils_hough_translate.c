#include "utils_hough_translate.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"
#include <SDL2/SDL.h>
#include <math.h>

int aff(int x, struct Line line){
        double a = (line.y_start - line.y_end)/(line.x_start - line.x_end);
        double b = line.y_start - a*line.x_start;
        return a*x+b;
    }

void draw_right(SDL_Surface *image,struct Line line)
{
    //x_start = 0 and y_end = 0
    Uint32* pixels = image->pixels;
    int w =(image->w) ;
    for (int x = 1; x < image->w; x++)
    {
      if (line.x_start == 0 || line.x_end == line.x_start)
      {
        continue;
      }
      
        int y = aff(x, line);
        if (y >= image->h || x < 0 ||y < 0)
        {
            continue;
        }
      //  printf("x:%i,y:%i\n", x,y);  
        pixels[y*w +x] = SDL_MapRGB(image->format, 127,32,127);
    }
    

}

void draw_line(SDL_Surface *image, int w, int h,struct Line line, 
               int thickness)
{
    Uint32 * pixels = image->pixels;
    // printf("Drawing line\n");
    int x0 = line.x_start;
    int y0 = line.y_start;

    int x1 = line.x_end;
    int y1 = line.y_end;

    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;

    int err = dx + dy;

    while (1)
    {
        if (0 <= x0 && x0 < w && 0 <= y0 && y0 < h)
        {
         
                pixels[y0*w + x0]=SDL_MapRGB(image->format, 127,32,127);

                if (thickness == 2)
                {
                    if (0 <= (x0 + 1) && (x0 + 1) < w && 0 <= (y0 + 1)
                        && (y0 + 1) < h)
                    {
                       pixels[(x0 + 1) + w*(y0 + 1)] = 
                        SDL_MapRGB(image->format, 127,32,127);
                    }
                    if (0 <= (x0 - 1) && (x0 - 1) < w && 0 <= (y0 - 1)
                        && (y0 - 1) < h)
                    {
                       pixels[(x0 - 1) + w*(y0 - 1)] = 
                        SDL_MapRGB(image->format, 127,32,127);
                    }
                }
    
        }

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void change_mat(SDL_Surface * sdl_surface,struct Lines lines){
    SDL_LockSurface(sdl_surface);
    for (int i = 0; i <lines.size; i++)
        {

            struct Line l = lines.lines[i];
            //printf("start:%i,%i, end:%i,%i\n", l.x_start, l.y_start, l.x_end, l.y_end);
           
           // draw_right(sdl_surface, l);
            draw_line(sdl_surface, sdl_surface->w, sdl_surface->h, l, 1);
        }
       // printf("x,y coord: %i,%i, x,y coord_f: %i,%i", lines.lines[1].x_start, lines.lines[1].y_start, lines.lines[1].x_end, lines.lines[1].y_end);
    //draw_right(sdl_surface, lines.lines[1]);
    //draw_line(sdl_surface, lines.lines[100]);
    SDL_UnlockSurface(sdl_surface);
}

void draw_square(SDL_Surface * sdl, struct Square square){
    SDL_LockSurface(sdl);
    Uint32* pixels = sdl->pixels;
    int w = sdl->w;
    for (int i = square.pA.x; i < square.pB.x; i++)
    {
        pixels[square.pA.y*w + i] = SDL_MapRGB(sdl->format, 255,32,0);
        pixels[square.pD.y*w + i] = SDL_MapRGB(sdl->format, 255,32,0);
    }
    for (int i = square.pB.y; i > square.pC.y; i--)
    {
        pixels[i*w + square.pC.x] = SDL_MapRGB(sdl->format, 255,32,0);
        pixels[i*w + square.pD.x] = SDL_MapRGB(sdl->format, 255,32,0);
    }
    for (int i = square.pB.x; i < square.pA.x; i++)
    {
        pixels[square.pA.y*w + i] = SDL_MapRGB(sdl->format, 255,32,0);
        pixels[square.pD.y*w + i] = SDL_MapRGB(sdl->format, 255,32,0);
    }
    for (int i = square.pC.y; i > square.pB.y; i--)
    {
        pixels[i*w + square.pC.x] = SDL_MapRGB(sdl->format, 255,32,0);
        pixels[i*w + square.pD.x] = SDL_MapRGB(sdl->format, 255,32,0);
    }
    SDL_UnlockSurface(sdl);
}

void draw_squares(SDL_Surface * sdl_surface, struct Squares squares){
    for (size_t i = 0; i < squares.size; i++)
    {
        draw_square(sdl_surface, squares.squares[i]);
    }
    
}

void draw_points(SDL_Surface * sdl, struct Points points){
    SDL_LockSurface(sdl);
    Uint32* pixels = sdl->pixels;
    int w = sdl->w; 
    for (size_t i = 0; i < points.size; i++)
    {
        pixels[(points.points[i].y-1)*w + points.points[i].x -1] = SDL_MapRGB(sdl->format, 255,0,0);
        pixels[points.points[i].y*w + points.points[i].x] = SDL_MapRGB(sdl->format, 255,0,0);
        pixels[(points.points[i].y)*w + points.points[i].x +1] = SDL_MapRGB(sdl->format, 255,0,0);
        pixels[(points.points[i].y+1)*w + points.points[i].x +1] = SDL_MapRGB(sdl->format, 255,0,0);
        pixels[(points.points[i].y+1)*w + points.points[i].x ] = SDL_MapRGB(sdl->format, 255,0,0);
    }
    
}