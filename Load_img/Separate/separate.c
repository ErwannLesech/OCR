#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_surface.h"
#include "separate.h"
#include "helper.h"


SDL_Surface** separate(SDL_Surface* grid)//int x1, int y1, int x2, int y2)
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
       	             
					if (IsPixelInImage(grid, xGrid, yGrid))
        	            		{
       	                 
						SetPixel(surfaces[index], x, y, GetPixel(grid, xGrid, yGrid));
					} 
					
					else 
					{
      	                  			SetPixel(surfaces[index], x, y, 0xFFFFFFFF);
      	              			}
      	          		}
     	       		}
    	    	}
	}
 	
	return surfaces;
}


void save_image(SDL_Surface** surfaces)
{
	for (int i = 0; i < 81; i++)
	{
		char name[7777777];
		int temp = i;
		int index = 0;
		while(temp != 0)
		{
			name[index] = (char)temp%10;
			temp /= 10;
			index++;
		}
		
		name[index] = '.';
		name[index] = 'b';
		name[index] = 'm';
		name[index] = 'p';
		name[index] = '\0';

		SDL_SaveBMP(surfaces[i], name);
		SDL_FreeSurface(surfaces[i]);
	}
}
