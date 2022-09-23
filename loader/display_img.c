#include <stdlib.h>
#include <SDL2/SDL.h>
#include "display_img.h"
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>

Uint8 RGBToUint(float gray){
   float grayinInt = (gray)*3;
    return (Uint8) (((int)(grayinInt*255.0f) << 16) + ((int)(grayinInt*255.0f) << 8) + ((int)(grayinInt*255.0f)<< 0));
}

SDL_Surface* get_surface(float** array, int height, int width)
{
    char pixels[sizeof(float)*height*width];
    int count = 0;
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            pixels[count++] = RGBToUint(array[i][j]);
        }
    }
    return SDL_CreateRGBSurfaceFrom(
        (void*)pixels,
        width,
        height,
        24,
        3*width,
        0x0000FF,             
        0x00FF00,             
        0xFF0000,              
        0);
}


void display_img(float** array, int height, int width){
    SDL_Surface* image = get_surface(array, height, width);
    bool quit = false;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);  	
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect dstrect = { 0, 0, width, height };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(renderer);
    while (!quit)
    {
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}