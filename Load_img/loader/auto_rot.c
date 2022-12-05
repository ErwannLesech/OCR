#include "auto_rot.h"
#include <math.h>

int min(int a, int b)
{
	return a >b ? b : a;
}

void bilinear_interpolate(SDL_Surface* new_surface,SDL_Surface* surface, double x, double y, int x_val,int y_val)
{
	Uint32* pixels = surface->pixels;
	Uint32* pixels_new = new_surface->pixels;
	/*Uint8 r1,g1,b1;
   	SDL_GetRGB(pixels[((int)y)*(new_surface->w) +
	(int)x], new_surface->format, &r1, &g1,&b1);
	Uint8 r2,g2,b2;
   	SDL_GetRGB(pixels[((int)y+1)*(new_surface->w) +
	(int)x], new_surface->format, &r2, &g2,&b2);
		Uint8 r3,g3,b3;
   	SDL_GetRGB(pixels[((int)y)*(new_surface->w) +
	(int)x+1], new_surface->format, &r3, &g3,&b3);
	Uint8 r4,g4,b4;
   	SDL_GetRGB(pixels[((int)y+1)*(new_surface->w) +
	(int)x+1], new_surface->format, &r4, &g4,&b4);*/
	int x_prev = (int) floor(x);
	int x_next = x_prev+1;
	int y_prev = (int) floor(y);
	int y_next = y_prev + 1;
	/*x_prev = min(x_prev, new_surface->w-1);
	x_next = min(x_next, new_surface->w-1);
	y_prev = min(y_prev, new_surface->h-1);
	y_next = min(y_next, new_surface->h-1);*/
	Uint8 r1,g1,b1;//y_next + x_prev
	Uint8 r2,g2,b2;//y_next + x_next
	Uint8 r3,g3,b3;//y_prev + x_next
	Uint8 r4,g4,b4;//y_prev + x_prev
	SDL_GetRGB(pixels[y_next*(new_surface->w) + x_prev],new_surface->format, &r1,&g1,&b1);
	SDL_GetRGB(pixels[y_next* (new_surface->w) + x_next],new_surface->format,&r2,&g2,&b2);
	SDL_GetRGB(pixels[y_prev * (new_surface->w) + x_next], new_surface->format, &r3,&g3,&b3);
	SDL_GetRGB(pixels[y_prev * (new_surface->w) + x_prev], new_surface->format, &r4,&g4,&b4);

	/*Uint8 r = Dy_prev * (r1) * Dx_next + r2 * Dx_prev + Dy_next * r4 * Dx_next + r3 * Dx_prev;
	Uint8 g = Dy_prev * (g1) * Dx_next + g2 * Dx_prev + Dy_next * g4 * Dx_next + g3 * Dx_prev;
	Uint8 b = Dy_prev * (b1) * Dx_next + b2 * Dx_prev + Dy_next * b4 * Dx_next + b3 * Dx_prev;*/
	//printf("%d\n", r4);
	Uint8 fr1 = r4 + ((double)r3-(double)r4)*(x - (double)x_prev);
	Uint8 fr2 = r1 + ((double)r2 - (double)r1)*(x - (double)x_prev);
	Uint8 r = fr1 + (fr2-fr1) * (y-(double)y_prev);

	Uint8 fg1 = g4 + (g3-g4)*(x - x_prev);
	Uint8 fg2 = g1 + (g2 - g1)*(x - x_prev);
	Uint8 g = fg1 + (fg2-fg1) * (y-y_prev);

	Uint8 fb1 = b4 + (b3-b4)*(x - x_prev);
	Uint8 fb2 = b1 + (b2 - b1)*(x - x_prev);
	Uint8 b = fb1 + (fb2-fb1) * (y-y_prev);
	//printf("%d, %d, %d\n", r,g,b);
	pixels_new[y_val*(new_surface->w) + x_val] = SDL_MapRGB(new_surface->format, r,g,b);
		}

SDL_Surface* rotate_img(SDL_Surface* surface, double degree)
{
	if (degree == 0)
	{
		return surface;
	}
	
	//Lock the surface
	SDL_LockSurface(surface);

	//Create a new surface in SDL_PIXELFORMAT_RGB888
	SDL_Surface* new_surface = SDL_ConvertSurfaceFormat(surface, 
	 	SDL_PIXELFORMAT_RGB888, 0);
	
	//Create a copy of the surface
	SDL_Surface* surface_copy = SDL_CreateRGBSurface(0,surface->w,
			surface->h ,32,0,0,0,0);
	//SDL_Surface* surface_copy = SDL_ConvertSurfaceFormat(surface_copy_new, SDL_PIXELFORMAT_RGB888, 0);
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

			if (0 <= rx && rx < new_surface->w-1 && 0 <= ry && 
				ry < new_surface->h-1)
			{
				bilinear_interpolate(surface_copy, surface, rx,ry, x,y);
				/*Uint8 r,g,b;
           			SDL_GetRGB(pixels[((int)ry)*(new_surface->w) +
				(int)rx], new_surface->format, &r, &g,&b);

				pixels_copy[((int)y)*(new_surface->w) + (int)x] 
				= SDL_MapRGB(new_surface->format, r,g,b);*/
			
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




int auto_rot(struct Lines lines)
{
    int* histo = calloc(181, sizeof(int));
    for (size_t i = 0; i < lines.size; i++)
    {
        for (size_t j = 0; j < lines.size; j++)
        {
            int theta = (lines.lines[i].theta) * 180.0 / M_PI;
           // printf("%d\n", theta);
            histo[theta]++;
            
        }
        
    }
    int max_pos = 0;
    int max_val = histo[1];
    for (size_t i = 1; i < 180; i++)
    {
        if (histo[i] > max_val)
        {
            max_pos = i;
            max_val = histo[i];
        }
        
    }
    if (max_pos == 90 || max_pos == 135)
    {
        return 0;
    }
    if (max_pos > 90)
        return max_pos-90;
    return max_pos+90;
    
}