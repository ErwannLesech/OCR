#include "../Load_img/main.h"
#include "../Separate/main.h"
#include "../Solver/solver.h"
#include "../Saved/main.h"
#include "../Solver/main.h"
#include "../OCR_neural_network/main.h"
#include "../Binarization/main.h"

#include <err.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ocr(char* path, int i)
{
	char* grille1;
	char* grille2;
	//BINARIZATION
	printf("binarization\n");
	//main_bin(path);

	//LOADER
	printf("loader\n");
	main_load(path);    	

	//SEPARATE
	printf("separate\n");
	main_separate("grid.png");
	
	//IA
	printf("ia\n");
	predict();
	grille1 = "./grid.txt";
	printf("saved_ocr\n");
	main_save_ocr("./grid.txt");
	
	if (i == 4)
	{
		//SOLVER
		printf("solver\n");
		main_solver(grille1, 9);
			if (i == '1')
		{
			grille2 = "./Saved/grid1";
		}
		if (i == '3')
		{
			grille2 = "./Saved/grid3";
	
		}	
	
		//SAVED
		printf("saved\n");
		main_save(grille1,grille2);
	}
}

void ocr_2(char* path, char i)
{
	char* grille1;
	char* grille2;
	//BINARIZATION
	printf("binarization\n");
	//main_bin(path);

	//LOADER
	printf("loader\n");
	main_load(path);    	

	//SEPARATE
	printf("separate\n");
	main_separate("grid.png");
	
	//IA
	printf("ia\n");
	predict();
	printf("saved_ocr\n");
	if (i == '1')
	{
		grille1 = "./Saved/grid1e";
	}
	if (i == '3')
	{
		grille1 = "./Saved/grid3e";
	
	}
	main_save_ocr(grille1);

	//SOLVER
	printf("solver\n");
	main_solver(grille1, 9);
	grille2 = "./grid.result";
	
	//SAVED
	printf("saved\n");
	main_save(grille1,grille2);
	
}
