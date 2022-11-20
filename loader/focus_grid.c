#include "focus_grid.h"
#include <stdio.h>
struct Point minPoint(struct Square square)
{
    struct Point pointmin = square.pA;
    if (square.pB.x <= pointmin.x && square.pB.y <= pointmin.y)
    {
        pointmin = square.pB;
    }
     if (square.pC.x <= pointmin.x && square.pC.y <= pointmin.y)
    {
        pointmin = square.pC;
    }
     if (square.pD.x <= pointmin.x && square.pD.y <= pointmin.y)
    {
        pointmin = square.pD;
    }
    return pointmin;
}
struct Point maxPoint(struct Square square)
{
    struct Point pointmax = square.pA;
    if (square.pB.x >= pointmax.x && square.pB.y >= pointmax.y)
    {
        pointmax = square.pB;
    }
     if (square.pC.x >= pointmax.x && square.pC.y >= pointmax.y)
    {
        pointmax = square.pC;
    }
     if (square.pD.x >= pointmax.x && square.pD.y >= pointmax.y)
    {
        pointmax = square.pD;
    }
    return pointmax;
}

SDL_Surface * focus_grid(SDL_Surface * sdl, struct Squares squares){
   SDL_Surface * sdl_surface = SDL_CreateRGBSurface(sdl->flags, squares.squares[0].len, squares.squares[0].len
    ,32,0,0,0,0);
     SDL_LockSurface(sdl_surface);
    Uint32* pixels = sdl->pixels;
    Uint32* pixels_new = sdl_surface->pixels;
   //if (squares.size == 1)
   {
        struct Point pmin = minPoint(squares.squares[0]);
        struct Point pmax = maxPoint(squares.squares[0]);
      for (int y = 0; y < sdl->h; y++)
    {
        for (int x = 0; x < sdl->w; x++)
        {
              if (pmin.x <x && pmin.y< y && pmax.x > x && pmax.y > y)
              {
                printf("+1\n");
                 pixels_new[(y-pmin.y)*sdl_surface->w + (x-pmin.x)] =  pixels[y*sdl->w + x];
              }
              // pixels[y*sdl_surface->w + x]=
        }
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
    SDL_SaveBMP(s, "grid.bmp\0");
    SDL_FreeSurface(s);
    SDL_FreeSurface(sdl);
}
