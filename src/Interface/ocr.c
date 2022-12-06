#include "../Load_img/main.h"
#include "../Separate/main.h"
#include "../Solver/solver.h"
#include "../Saved/main.h"
#include "../Solver/main.h"
#include "../OCR_neural_network/main.h"

#include <err.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ocr(char* path)
{
	//LOADER
	printf("loader");
	main_load(path);    	

	//SEPARATE
	printf("separate");
	main_separate("grid.png");
	
	//IA
	printf("ia");
	predict();	
	char* grille1 = "../OCR_neural_network/grid.txt";

	//SOLVER
	printf("solver");
	main_solver(grille1);
	char* grille2 = "../Solver/grid.result.txt";
	
	//SAVED
	printf("saved");
	main_save(grille1,grille2);
}
