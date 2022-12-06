#include <SDL2/SDL.h>


int Truncate(int a)
{
    if (a > 255)
    {
        return 255;
    }
    if (a < 0)
    {
        return 0;
    }
    return a;
    
    
}

void add_128_contrast(SDL_Surface * sdl)
{
    int contrast = -10;
    int factor = (259 * (contrast + 255)) / (255 * (259 - contrast));
    SDL_LockSurface(sdl);
    Uint32 *pixels = sdl->pixels;
    	for (int x = 0; x < sdl->w; x++)
	    {
		    for (int y = 0; y < sdl->h; y++)
		    {
                Uint8 r,g,b;
                SDL_GetRGB(pixels[y*(sdl->w) + (int)x],sdl->format, &r,&g,&b);
                r = Truncate(factor*r-128) +128;
                g = Truncate(factor*g -128) +128 ;
                b = Truncate(factor*b -128) +128;
                pixels[((int)y)*(sdl->w) + (int)x] 
				= SDL_MapRGB(sdl->format, r,g,b);
            }
        }	
        SDL_UnlockSurface(sdl);
}