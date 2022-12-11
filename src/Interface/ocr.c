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

void ocr(char* path)
{
	//BINARIZATION
	//printf("binarization\n");
	//main_bin(path);

	//LOADER
	printf("loader\n");
	main_load(path);    	

	//SEPARATE
	printf("separate\n");
	main_separate("grid.bmp");
	
	//IA
	printf("ia\n");
	//predict();	
	//char* grille1 = "../OCR_neural_network/grid.txt";
	char* grille1 = "./Saved/test_grid_01";

	//SOLVER
	printf("solver\n");
	main_solver(grille1);
	//char* grille2 = "../Solver/grid.result.txt";
	char* grille2 = "./Saved/test_grid_01.result";
	
	//SAVED
	printf("saved\n");
	main_save(grille1,grille2);
}
