#include <err.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

SDL_Surface* rotate_img(SDL_Surface* surface, double degree)
{
	//Lock the surface
	SDL_LockSurface(surface);

	//Create a new surface in SDL_PIXELFORMAT_RGB888
	SDL_Surface* new_surface = SDL_ConvertSurfaceFormat(surface, 
	 	SDL_PIXELFORMAT_RGB888, 0);
	
	//Create a copy of the surface
	SDL_Surface* surface_copy = SDL_CreateRGBSurface(0,surface->w,
			surface->h ,32,0,0,0,0);

	//Lock the surfaces
	SDL_LockSurface(surface_copy);
	SDL_LockSurface(new_surface);

	//Get the pixels
	Uint32* pixels_copy = surface_copy->pixels;
	Uint32* pixels = new_surface->pixels;

	//Convert the angle in degree to angle in radian
	double angle_rad = degree* M_PI/ 180.0;


	double center_x = (surface->w/(double)2);
	double center_y = (surface->h/(double)2);

	for (int x = 0; x < surface->w; x++)
	{
		for (int y = 0; y < surface->h; y++)
		{	
			//Rotate the pixels one by one
			double rx = (x - center_x) * cos(angle_rad) -
			       	(y - center_y) * sin(angle_rad) + center_x;

			double ry =  (x - center_x) * sin(angle_rad) + 
				(y - center_y) * cos(angle_rad) + center_y;

			if (0 <= rx && rx < new_surface->w && 0 <= ry && 
				ry < new_surface->h)
			{
				Uint8 r,g,b;
           			SDL_GetRGB(pixels[((int)ry)*(new_surface->w) +
				(int)rx], new_surface->format, &r, &g,&b);

				pixels_copy[((int)y)*(new_surface->w) + (int)x] 
				= SDL_MapRGB(new_surface->format, r,g,b);
			
			}
			else
			{
				pixels_copy[((int)y)*(new_surface->w) + (int)x] 
				= SDL_MapRGB(new_surface->format, 0,0,0);
			}
			
		}
		
	}
	SDL_UnlockSurface(surface_copy);
	SDL_UnlockSurface(surface);
	return surface_copy;
}
int main_rotate(char* path,int angle)
{
	//Init the SDL
	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	
	//Create the SDL_Surface from a .jpeg
	SDL_Surface* surface = IMG_Load(path);
	
	//Convert the angle given in long int
	long int angler = angle;
	
	//Rotation of the surface
	SDL_Surface* turned = rotate_img(surface, -angler);

	//Save of the rotation
	SDL_Surface *new = SDL_CreateRGBSurface(0, turned->w-10, turned->h-10, 32, 0, 0, 0, 0);
	SDL_BlitScaled(turned, NULL, new, NULL);

	IMG_SavePNG(new, "rotate.png");
	
	SDL_FreeSurface(surface);
	SDL_FreeSurface(turned);
	SDL_Quit();
	
	return EXIT_SUCCESS; 
	
}

/*int main(int argc, char** argv)
{
	//Check the number of arguments
	if (argc != 4)
        	errx(EXIT_FAILURE, "Not enougth arguments");
	
	//Init the SDL
	SDL_Init(SDL_INIT_VIDEO);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	
	//Create the SDL_Surface from a .jpeg
	SDL_Surface* surface= IMG_Load(argv[2]);
	
	//Convert the angle given in long int
	long int angler = strtol(argv[3], NULL, 10);
	
	//Rotation of the surface
	SDL_Surface* turned = rotate_img(surface, -angler);

	//Save of the rotation
	SDL_Surface *new = SDL_CreateRGBSurface(0, turned->w-10, turned->h-10, 32, 0, 0, 0, 0);
	SDL_BlitScaled(turned, NULL, new, NULL);

	IMG_SavePNG(new, "rotate.png");
	
	SDL_FreeSurface(surface);
	SDL_FreeSurface(turned);
	SDL_Quit();
	
	return EXIT_SUCCESS; 
	
}*/

