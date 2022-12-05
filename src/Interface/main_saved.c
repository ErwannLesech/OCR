#include "main_saved.h"
#include "../Solver/solver.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "../Separate/separate.h"



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

            change_pixel(grid, x + i, y + j, take_pixel(cell, i , j));
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

int main_save(int argc, char** argv)
{
	if(argc != 3)
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
