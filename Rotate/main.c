#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL2/SDL_image.h>

void draw(SDL_Renderer* renderer, SDL_Texture* texture)
{
     SDL_RenderCopyEx(renderer, texture, NULL, NULL);
     SDL_RenderPresent(renderer);
}

void event_loop(SDL_Renderer* renderer, SDL_Texture* normal, SDL_Texture* turn)
{
	SDL_Event event;
	SDL_Texture* t = normal;

	while(1)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				return;
		
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					draw(renderer, normal);
				}
				break;
			/*case SDL_KEYDOWN:
				if(t == normal)
				{
					draw(renderer, turn);
					t = turn;
				}
				else
				{
					draw(renderer, normal);
					t = normal;
				}
				break;*/
		}
	}	
}

/*SDL_Surface* load_image(const char* path)
{
	SDL_Surface *image = IMG_Load(path);
    	SDL_Surface *surface = SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_RGB888,0);
    	if(!surface)
	    	errx(EXIT_FAILURE, "%s", SDL_GetError());
	SDL_FreeSurface(image);
	return surface;
}*/

int main(int argc, char** argv)
{
	if (argc != 3)
        	errx(EXIT_FAILURE, "Erreur");
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	
	SDL_Window* window = SDL_CreateWindow("Window", 0, 0,
			800, 800,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (window == NULL)
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);

	if (renderer == NULL)
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	SDL_Surface* surface= SDL_LoadBMP(argv[1]);

	//SDL_SetWindowSize(window, surface->w,surface->h);
	SDL_Texture* normal = IMG_LoadTexture(renderer,argv[1]);
	int angler = (int)(argv[2]) * M_PI / 180.0;
	
	SDL_Surface* surfaceturn =rotozoomSurface(surface,(-180), 1,1);
	
	SDL_Texture *turn = SDL_CreateTextureFromSurface(renderer, surfaceturn);
	
	SDL_FreeSurface(surface);

	event_loop(renderer,normal,turn);

	SDL_DestroyTexture(normal);
	printf("a");

	SDL_DestroyTexture(turn);
	printf("a");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;    
}


