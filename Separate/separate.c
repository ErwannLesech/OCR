#include "separate.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Take the pixel

Uint32 take_pixel(SDL_Surface *surface, int x, int y)
{
    Uint8 byte = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * byte;

    switch(byte)
    {
        case 1:
            return *p;
        case 2:
            return *(Uint16 *)p;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32 *)p;
        default:
            return 0;
    }
}

//Change the color of the pixel

void change_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{

    Uint8 byte = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * byte;

    switch(byte)
    {
        case 1:
            *p = pixel;
            break;
        case 2:
            *(Uint16 *)p = pixel;
            break;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN){
                p[0] = (pixel >> 16) & 0xFF;
                p[1] = (pixel >> 8) & 0xFF;
                p[2] = pixel & 0xFF;
            }
            else{
                p[0] = pixel & 0xFF;
                p[1] = (pixel >> 8) & 0xFF;
                p[2] = (pixel >> 16) & 0xFF;
            }
            break;
        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

//Verify if the (x,y) is in the surface

int is_in_image(SDL_Surface *surface, int x, int y)
{
    return 0 <= x && x < surface->w && 0 <= y && y < surface->h;
}

//Clean the black on surfaces

SDL_Surface* clear(SDL_Surface* surface)
{
	Uint32 pixelb =SDL_MapRGBA(surface->format, 255, 255, 255, 255);
	for(int i =0; i < surface->w; i ++)
	{
		if(i<=surface->w/6 || i>=5*surface->w/6)
		{
			for(int j = 0;j<surface->h; j++)
			{
				change_pixel(surface,i,j, pixelb);
			}
		}
		
	}
	for(int i = 0; i<surface->h;i ++)
	{	
		if(i<=surface->h/6 || i>=5*surface->h/6)
		{

			for(int j = 0; j < surface->w; j++)
			{
				change_pixel(surface,j,i,pixelb);
			}
		}
	}



	return surface;
}

//Separate the surface in 9x9 surfaces

SDL_Surface** separate(SDL_Surface* surface)
{
	if(surface == NULL)
	{
		return NULL;
    	}
    	
    	SDL_Surface** surfaces = malloc(9 * 9 * sizeof(surface));
    	int size = (surface->w / 9) + 1;

    	for (int i = 0; i < 9; i++)
	{
        	for (int j = 0; j < 9; j++)
		{

            		int index = i * 9 + j;
            		surfaces[index] = SDL_CreateRGBSurface(0,size,size,
						32,0,0,0,0);
            	
			for (int y = 0; y < size ; y++)
			{
         	       		for (int x = 0; x < size; x++)
				{
					int xsurface = j * size + x;
        	            		int ysurface = i * size + y;
       	             
					if (is_in_image(surface, xsurface, 
								ysurface))
        	            		{
       	                 
						change_pixel(surfaces[index],
						x, y, take_pixel(surface,
						    xsurface,ysurface));
					} 
					
					else 
					{
      	                  			change_pixel(surfaces[index], 
							x, y, 0xFFFFFFFF);
      	              			}
      	          		}
     	       		}
    	    	}
	}
 	
	return surfaces;
}


//Save the 9x9 surfaces in .png
            
void save_image_cut(SDL_Surface** surfaces)
{
	mkdir("./cells", 0777);
	char name[81][15];
	for (int i = 0; i < 81; i++)
	{
		SDL_Surface *new = SDL_CreateRGBSurface(0, 28, 28, 32, 0, 0, 0, 0);
		SDL_BlitScaled(surfaces[i], NULL, new, NULL);

		name[i][0] = '.';
		name[i][1] = '/';
		name[i][2] = 'c';
		name[i][3] = 'e';
		name[i][4] = 'l';
		name[i][5] = 'l';
		name[i][6] = 's';
		name[i][7] = '/';
		name[i][8] = (i/10) + '0';
		name[i][9] = (i%10) + '0';
		name[i][10] = '.';
		name[i][11] = 'p';
		name[i][12] = 'n';
		name[i][13] = 'g';
		name[i][14] = '\0';
		IMG_SavePNG(new, name[i]);
		SDL_FreeSurface(surfaces[i]);
	}
}
