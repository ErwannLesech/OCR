#include "main.h"
#include "../Solver/solver.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

//Take the pixel

Uint32 take(SDL_Surface *surface, int x, int y)
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

void change(SDL_Surface *surface, int x, int y, Uint32 pixel)
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

void FillGrid(SDL_Surface* grid, SDL_Surface* cell, int pos)
{
    int x = pos % 9;
    int y = pos / 9;
    x = x *22 + 2 * (x / 3) + x + 3;
    y = y * 22 + 2 * (y / 3) + y + 3;
    int cellSize = cell->w;
    
    for(int i = 0; i < cellSize; i++)
    {
        for(int j = 0; j < cellSize; j++)
	{

            change(grid, x + i, y + j, take(cell, i , j));
        }
    }
}


void PrettyGrid(char* old, char* solved)
{
    SDL_Surface* grid = IMG_Load("Grille.png");
    SDL_Surface** red = calloc(9,sizeof(grid));
    SDL_Surface** black = calloc(9,sizeof(grid));
    char redstr[] = "Data/0r.png";
    char blackstr[] = "Data/0b.png";
    for(int i = 0; i < 9; i++)
    {
        redstr[5] = i + '1';
        blackstr[5] = i + '1';
        red[i] = IMG_Load(redstr);
        black[i] = IMG_Load(blackstr);
    }
    for(int i = 0; i < 81; i++)
    {

	    if(solved[i] == old[i])
	    {
		    int indice = solved[i] - '0';
		    FillGrid(grid,black[indice -1],i);
	    }
	    else
	    {
		int indice = solved[i] - '0';
		FillGrid(grid,red[indice-1], i);
	    }
    }
    for(int i = 0; i < 9; i++)
    {
        SDL_FreeSurface(red[i]);
        SDL_FreeSurface(black[i]);
    }
    free(red);
    free(black);
    SDL_Surface *save =SDL_CreateRGBSurface(0,500,500,32,0,0,0,0);
    SDL_BlitScaled(grid,NULL,save,NULL);
    IMG_SavePNG(save, "saved.png");
    SDL_FreeSurface(save);
    SDL_FreeSurface(grid);
}


int main_save(char* grille1, char* grille2)
{
	
	FILE *old = fopen(grille1, "r");
	char* o = calloc(81,sizeof(char));
	char* n = calloc(81,sizeof(char));
	char c;
	char *i = o;
	while((c=fgetc(old)) != EOF)
	{
		if(c != ' ' && c != '\n')
		{
			
			if(c != '.')
			{
				*i = c;
				i +=1;
			}
			else
			{
				*i = ' ' - 32;
				i+=1;
			}
		}
	}
	fclose(old);
	FILE *new = fopen(grille2, "r");
	char *j = n;
	while((c=fgetc(new)) != EOF)
	{
		if(c != ' ' && c != '\n')
		{
			*j = c;
			j+=1;
		}
	}
	PrettyGrid(o,n);
	fclose(new);
	free(o);
	free(n);
	return 1;
}


/*int main(int argc, char** argv)
{
	if(argc != 4)
	{
		errx(EXIT_FAILURE, "You need two files");
	}
	
	FILE *old = fopen(argv[1], "r");
	char* o = calloc(81,sizeof(char));
	char* n = calloc(81,sizeof(char));
	char c;
	char *i = o;
	while((c=fgetc(old)) != EOF)
	{
		if(c != ' ' && c != '\n')
		{
			
			if(c != '.')
			{
				*i = c;
				i +=1;
			}
			else
			{
				*i = ' ' - 32;
				i+=1;
			}
		}
	}
	fclose(old);
	FILE *new = fopen(argv[2], "r");
	char *j = n;
	while((c=fgetc(new)) != EOF)
	{
		if(c != ' ' && c != '\n')
		{
			*j = c;
			j+=1;
		}
	}
	PrettyGrid(o,n);
	fclose(new);
	free(o);
	free(n);
	return 1;
}
*/