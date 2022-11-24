#include "otsu.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface* init_img(char* path)
{
    SDL_Surface* surface = IMG_Load(path);
    SDL_Surface* new_surface = SDL_ConvertSurfaceFormat(surface, 
        SDL_PIXELFORMAT_RGB888, 0);
    SDL_FreeSurface(surface);
    return new_surface;
}


void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
    SDL_RenderCopy(renderer,texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}


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


void display_img(SDL_Surface* sdl_surface)
{
   if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    
   // - Create a window.
    SDL_Window* window = SDL_CreateWindow("Display", 0, 0, 640, 400,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    
    // - Create a renderer.
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
            SDL_RENDERER_TARGETTEXTURE);
    if (renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
       
    // - Resize the window according to the size of the image.
    SDL_SetWindowSize(window, sdl_surface->w, sdl_surface->h);
    
    // - Create a texture from the colored surface.
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, sdl_surface);
     
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

int main(int argc, char **argv)
{
	//image_binarize(argv[1]);
	/*int arr[10] = {1, 12, 31, 4, 16, 18, 27, 2, 28, 27};
	insertionSort(arr, 10);
	for(int i = 0; i < 10; i++)
	{
		printf("%i, ",arr[i]);
	}*/
	
	SDL_Surface *image = init_img(argv[1]);
	
	median_filter(image);
	//display_img(image);

	SDL_SaveBMP(image, "image_median.bmp");
	free(image);
	return EXIT_SUCCESS;
}
