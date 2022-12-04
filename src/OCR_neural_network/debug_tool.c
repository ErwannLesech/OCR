#include "debug_tool.h"
#include "matrix.h"
#include "SDL2/SDL.h"
#include <err.h>

SDL_Surface * translate_mat(matrix mat)
{
    SDL_Surface* surface = SDL_CreateRGBSurface(0,28, 28, 32,0,0,0,0);
    SDL_LockSurface(surface);
    Uint32* pixels = surface->pixels;
    
   for (size_t i = 0; i < mat.rows; i++)
    {
        for (size_t j = 0; j < mat.cols; j++)
        {
            if(get_value(&mat, i,j) == 1){
            pixels[i*mat.cols + j] = SDL_MapRGB(surface->format,255,255,255);
            }
            else 
            {
                 pixels[i*mat.cols + j] = SDL_MapRGB(surface->format,0,0,0);
            }
        }
        
    }
    
    SDL_UnlockSurface(surface);
    return surface;
}

void draw2(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer,texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}


void event_loop2(SDL_Renderer* renderer, SDL_Texture* colored)
{
    SDL_Event event;
    draw2(renderer, colored);
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
                draw2(renderer, colored);
                }
                break;
        }
    }
}


void display_mat(matrix mat){
    SDL_Surface * sdl_surface = translate_mat(mat);
    printf("test\n");
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
    event_loop2(renderer, texture);
    // - Destroy the objects.
     SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}