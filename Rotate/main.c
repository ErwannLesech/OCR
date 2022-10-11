#include <err.h>
#include <math.h>
#include <SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_gfx>

void print(SDL_Renderer* renderer, SDL_Texture* texture)
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
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
					print(renderer, normal);
				}
				break;
			case SDL_KEYDOWN:
				if(t == normal)
				{
					print(renderer, turn);
					t = turn;
				}
				else
				{
					print(renderer, normal);
					t = normal;
				}
				break;
		}
	}
}

SDL_Surface* load_image(const char* path)
{
	SDL_Surface *image = IMG_Load(path);
	SDL_Surface *surface = SDL_ConvertSurfaceFormat(image,SDL_PIXELFORMAT_RGB888,0);
	if(surface == NULL)
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	SDL_FreeSurface(image);
	return surface;
}

int main(int arc, char** argv)
{
	if (argc != 3)
		errx(EXIT_FAILURE, "Error");
	SDL_Window* window = SDL_CreateWindow("Static Fractal Canopy", 0, 0,
			600, 450,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == NULL)
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
		errx(EXIT_FAILURE, "%s", SDL_GetError())
	SDL_Surface* surface = load_image(argv[1]);
	SDL_SetWindowSize(window, surface->w,surface->h);
	SDL_Texture *normal = SDL_CreateTextureFromSurface(renderer, surface);
	double angle_radian = (int)argv[2] * M_PI / 180.0;
	SDL_Surface* surfaceturn =rotozoomSurface(SDL_Surface* image,-angle_radian, 1,1);
	SDL_Texture *turn = SDL_CreateTextureFromSurface(renderer, surfaceturn);
	SDL_FreeSurface(surfaceturn);
	event_loop(renderer,normal,turn);
	SDL_DestroyTexture(normal);
	SDL_DestroyTexture(turn);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}


