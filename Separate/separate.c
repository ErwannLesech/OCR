#include "separate.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Uint32 take_pixel(SDL_Surface *surface, int x, int y)
{
    Uint8 bytes = surface->format->BytesPerPixel;
    Uint8 *pix = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes;

    switch(bytes){
        case 1:
            return *pix;
        case 2:
            return *(Uint16 *)pix;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return pix[0] << 16 | pix[1] << 8 | pix[2];
            else
                return pix[0] | pix[1] << 8 | pix[2] << 16;
        case 4:
            return *(Uint32 *)pix;
        default:
            return 0;
    }
}


void change_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{

    Uint8 bytes = surface->format->BytesPerPixel;
    Uint8 *pix = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes;

    switch(bytes){
        case 1:
            *pix = pixel;
            break;
        case 2:
            *(Uint16 *)pix = pixel;
            break;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN){
                pix[0] = (pixel >> 16) & 0xFF;
                pix[1] = (pixel >> 8) & 0xFF;
                pix[2] = pixel & 0xFF;
            }
            else{
                pix[0] = pixel & 0xFF;
                pix[1] = (pixel >> 8) & 0xFF;
                pix[2] = (pixel >> 16) & 0xFF;
            }
            break;
        case 4:
            *(Uint32 *)pix = pixel;
            break;
    }
}


int is_in_image(SDL_Surface *surface, int x, int y)
{
    return 0 <= x && x < surface->w && 0 <= y && y < surface->h;
}



SDL_Surface** separate(SDL_Surface* grid)
{
	if(grid == NULL)
	{
		return NULL;
    	}
    	
    	SDL_Surface** surfaces = malloc(9 * 9 * sizeof(grid));
    	int size = (grid->w / 9) + 1;

    	for (int i = 0; i < 9; i++)
	{
        	for (int j = 0; j < 9; j++)
		{

            		int index = i * 9 + j;
            		surfaces[index] = SDL_CreateRGBSurface(0,size,size,32,0,0,0,0);
            	
			for (int y = 0; y < size ; y++)
			{
         	       		for (int x = 0; x < size; x++)
				{
					int xGrid = j * size + x;
        	            		int yGrid = i * size + y;
       	             
					if (is_in_image(grid, xGrid, yGrid))
        	            		{
       	                 
						change_pixel(surfaces[index], x, y, take_pixel(grid, xGrid, yGrid));
					} 
					
					else 
					{
      	                  			change_pixel(surfaces[index], x, y, 0xFFFFFFFF);
      	              			}
      	          		}
     	       		}
    	    	}
	}
 	
	return surfaces;
}
            
void save_image_cut(SDL_Surface** surfaces)
{
	char name[81][7];
	for (int i = 0; i < 81; i++)
	{
		name[i][0] = (i/10) + '0';
		name[i][1] = (i%10) + '0';
		name[i][2] = '.';
		name[i][3] = 'b';
		name[i][4] = 'm';
		name[i][5] = 'p';
		name[i][6] = '\0';
		//surfaces[i]  = Resize(surfaces[i]);
		SDL_SaveBMP(surfaces[i], name[i]);
		SDL_FreeSurface(surfaces[i]);
	}
}
