#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stddef.h>
#include "load_img.h"
#include "display_img.h"
#include <err.h>

Uint32 pixels_in_black_and_white(Uint32 pixel_color, SDL_PixelFormat* format){
     Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);
    if ((r+b+g)/3 >= 127)
    {
        return SDL_MapRGB(format, 255, 255, 255);
    }
    else{
        return SDL_MapRGB(format, 0, 0, 0);
    }
  
}

Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format)
{
    Uint8 r, g, b;
    SDL_GetRGB(pixel_color, format, &r, &g, &b);
    Uint8 average = 0.3*r + 0.59*g+0.11*b;
    r = g = b = average;
    Uint32 color = SDL_MapRGB(format, r, g, b);
    return color;
    
}

void surface_to_grayscale_and_black_white(SDL_Surface* surface)
{
    Uint32* pixels = surface->pixels;
    int len = (surface->w)*(surface->h);
    SDL_PixelFormat* format = surface->format;
    SDL_LockSurface(surface);
    for (int i = 0; i < len; i++)
    {   
        if (pixels[i] == NULL)
        {
            SDL_UnlockSurface(surface);
            return;
           // errx(EXIT_FAILURE, "%s", SDL_GetError());
        }
        
       pixels[i]= pixel_to_grayscale(pixels[i], format);
      // pixels[i] = pixels_in_black_and_white(pixels[i], format);
    }
    SDL_UnlockSurface(surface);
}

SDL_Surface* init_img(char* path){
     SDL_Surface* surface = IMG_Load(path);
    SDL_Surface* new_surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB888, 0);
    SDL_FreeSurface(surface);
    //surface_to_grayscale(new_surface);
    return new_surface;
}



//height = hauteur width = largeur
