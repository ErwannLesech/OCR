#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "separate.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Uint32 GetPixel(SDL_Surface *surface, int x, int y)
{
    Uint8 bytePerPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytePerPixel;

    switch(bytePerPixel){
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


void SetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{

    Uint8 bytePerPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytePerPixel;

    switch(bytePerPixel){
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


int IsPixelInImage(SDL_Surface *surface, int x, int y)
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

/*SDL_Surface* Resize(SDL_Surface* gridCase){
    	if(gridCase == NULL){
        	return NULL;
    	}
    	int wLen = 28;
    	int ratio = gridCase->w % wLen;
	SDL_Surface* result = SDL_CreateRGBSurface(0,wLen,wLen,32,0,0,0,0);


    float ratio = gridCase->w / wLen;
    SDL_Surface* result = SDL_CreateRGBSurface(0,wLen,wLen,32,0,0,0,0);
    for(int y = 0; y < wLen; y++){
        for(int x = 0; x < wLen; x++){
            int startX = x * ratio;
            int startY = y * ratio;
            int cpt = 0;
            for (int y1 = 0; y1 < ratio; y1++){
                for (int x1 = 0; x1 < ratio; x1++){
                    if(IsPixelInImage(gridCase, startX, startY))
                        cpt += GetPixel(gridCase, startX+x1,
                                    startY+y1) == 0x00000000;
                }
            }
            int limit = (int)(ratio * ratio) / 2;
            SetPixel(result, x, y, cpt > limit ? 0x00000000 : 0xFFFFFFFF);
        }
    }
    for (int i = 0; i < wLen; i++){
        for (int j = 0; j < wLen; j++){
            if (GetPixel(result, i, j) == 0x00000000){
                int cpt = 0;
                if(i != 0){
                    cpt += GetPixel(result, i-1, j) == 0x00000000;
                }
                if(!cpt && j != 0){
                    cpt += GetPixel(result, i, j-1) == 0x00000000;
                }
                if(!cpt && i != wLen-1){
                    cpt += GetPixel(result, i+1, j) == 0x00000000;
                }
                if(!cpt && j != wLen-1){
                    cpt += GetPixel(result, i, j+1) == 0x00000000;
                }
                if(!cpt){
                    SetPixel(result, i, j, 0xFFFFFFFF);
                }
            }

        }
    }
    return result;
}*/


void save_image(SDL_Surface** surfaces)
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
