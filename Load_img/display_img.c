#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "display_img.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <err.h>

void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer,texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

// Event loop that calls the relevant event handler.
//
// renderer: Renderer to draw on.
// colored: Texture that contains the colored image.
// grayscale: Texture that contains the grayscale image.
void event_loop(SDL_Renderer* renderer, SDL_Texture* colored)
{
    SDL_Event event;
    draw(renderer, colored);
    while (1)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                return;
            case SDL_WINDOWEVENT:
             if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                draw(renderer, colored);
                }
                break;
        }
    }
}

void display_img(SDL_Surface* sdl_surface){
    printf("aaaa");
   if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    // - Create a window.
     SDL_Window* window = SDL_CreateWindow("Display", 0, 0, 640, 400,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    // - Create a renderer.
      SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
    if (renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    // - Create a surface from the colored image.
    // - Resize the window according to the size of the image.
    SDL_SetWindowSize(window, sdl_surface->w, sdl_surface->h);
    // - Create a texture from the colored surface.
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, sdl_surface);
    // - Convert the surface into grayscale.
    // - Create a new texture from the grayscale surface.
 
    // - Free the surface.
    SDL_FreeSurface(sdl_surface);
    // - Dispatch the events.
    event_loop(renderer, texture);
    // - Destroy the objects.
     SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    //return EXIT_SUCCESS;
}