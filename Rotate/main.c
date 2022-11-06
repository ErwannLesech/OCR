#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

SDL_Surface* rotate_img(SDL_Surface* sdl, double degree){
	SDL_LockSurface(sdl);
	 SDL_Surface* new_surface = SDL_ConvertSurfaceFormat(sdl, 
	 	SDL_PIXELFORMAT_RGB888, 0);
    SDL_FreeSurface(sdl);
	SDL_Surface* sdl_copy = SDL_CreateRGBSurface(0,sdl->w,sdl->h,
		32,0,0,0,0);
	SDL_LockSurface(sdl_copy);
	SDL_LockSurface(new_surface);
	Uint32* pixels_copy = sdl_copy->pixels;
	Uint32* pixels = new_surface->pixels; 
	double angle_rad = degree* M_PI/ 180.0;
	double center_x = (sdl->w/(double)2);
	double center_y = (sdl->h/(double)2);
	for (int x = 0; x < sdl->w; x++)
	{
		for (int y = 0; y < sdl->h; y++)
		{
			double rx = (x - center_x) * cos(angle_rad) - (y - center_y) * 
				sin(angle_rad) + center_x;
			double ry =  (x - center_x) * sin(angle_rad) + (y - center_y) * 
				cos(angle_rad) + center_y;
			if (0 <= rx && rx < new_surface->w && 0 <= ry && 
				ry < new_surface->h)
			{
				  Uint8 r,g,b;
           		SDL_GetRGB(pixels[((int)ry)*(new_surface->w) + (int)rx], 
					new_surface->format, &r, &g,&b);
				pixels_copy[((int)y)*(new_surface->w) + (int)x] = 
					SDL_MapRGB(new_surface->format, r,g,b);
				//pixels[sdl->pixels[y*w +x]];
			}
			else{
				pixels_copy[((int)y)*(new_surface->w) + (int)x] = 
					SDL_MapRGB(new_surface->format, 0,0,0);
			}
			
		}
		
	}
	SDL_UnlockSurface(sdl_copy);
	SDL_UnlockSurface(sdl);
	return sdl_copy;
}


int main_rotate(int argc, char** argv)
{
	if (argc != 4)
        	errx(EXIT_FAILURE, "Not enougth arguments");

	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		errx(EXIT_FAILURE, "%s", SDL_GetError());

	SDL_Surface* surface= IMG_Load(argv[2]);

	long int angler = strtol(argv[3], NULL, 10);
	
	/*SDL_Surface* turned;

	turned = surface;//rotozoomSurface(surface, -angler, 1,10);
	*/
	SDL_Surface* turned = rotate_img(surface, angler);


	SDL_SaveBMP(turned, "test2.bmp");
	
	SDL_FreeSurface(surface);
	SDL_FreeSurface(turned);
	SDL_Quit();
	
	return EXIT_SUCCESS; 
	
}

