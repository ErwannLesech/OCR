#include "focus_grid.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <math.h>
int dist2(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2));
}

struct Point minPoint(struct Square square)
{
    struct Point pointmin = square.pA;
    if (square.pB.x + square.pB.y<= pointmin.x + pointmin.y)
    {
        pointmin = square.pB;
    }
     if (square.pC.x+ square.pC.y <= pointmin.x+ pointmin.y)
    {
        pointmin = square.pC;
    }
     if (square.pD.x+square.pD.y <= pointmin.x+ pointmin.y)
    {
        pointmin = square.pD;
    }
    return pointmin;
}
struct Point maxPoint(struct Square square)
{
    struct Point pointmax = square.pA;
    if (square.pB.x+square.pB.y >= pointmax.x+ pointmax.y)    {
        pointmax = square.pB;
    }
    if (square.pC.x+ square.pC.y >= pointmax.x+ pointmax.y)
    {
        pointmax = square.pC;
    }
     if (square.pD.x+ square.pD.y >=pointmax.x+ pointmax.y)
    {
        pointmax = square.pD;
    }
    return pointmax;
}

SDL_Surface * focus_grid(SDL_Surface * sdl, struct Squares squares){
 
   //if (squares.size == 1)
        struct Point pmin = minPoint(squares.squares[0]);
        struct Point pmax = maxPoint(squares.squares[0]);
          SDL_Surface * sdl_surface = SDL_CreateRGBSurface(sdl->flags, pmax.x - pmin.x, pmax.y - pmin.y
    ,32,0,0,0,0);
     Uint32* pixels = sdl->pixels;
    Uint32* pixels_new = sdl_surface->pixels;
     SDL_LockSurface(sdl_surface);
        printf("%d,%d et %d,%d\n", pmin.x,pmin.y, pmax.x, pmax.y);
      for (int y = 0; y < sdl->h; y++)
    {
        for (int x = 0; x < sdl->w; x++)
        {
              if (pmin.x <x && pmin.y< y && pmax.x > x && pmax.y > y)
              {
               // printf("+1\n");
                 pixels_new[(y-pmin.y)*sdl_surface->w + (x-pmin.x)] =  pixels[y*sdl->w + x];
              }
              // pixels[y*sdl_surface->w + x]=
        }
    }
  // else{

    //TODO IF WE HAVE NEURONAL NETWORK
   //}
   SDL_UnlockSurface(sdl_surface);
    return sdl_surface;
}

void registerSurface(SDL_Surface * sdl, struct Squares squares){
    SDL_Surface * s = focus_grid(sdl, squares);
    IMG_SavePNG(s, "grid.png");
    SDL_FreeSurface(s);
    SDL_FreeSurface(sdl);
}
