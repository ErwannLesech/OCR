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
    if (i < 5)
    {
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
    }
    
    if (i == 5)
    {
        //SOLVER
        printf("solver\n");
        main_solver("./grid.txt", 9);
        grille2 = "./grid.result";
        //SAVED
        printf("saved\n");
        main_save(grille1,grille2);
    }
}

void ocr_2(char* path, char i)
{
    char* grille1 = "./grid.txt";
    char* grille2 = "./grid.result";

    if (i < 1)
    {
        //BINARIZATION
        printf("binarization\n");
        //main_bin(path);

        //LOADER
        printf("loader\n");
        main_load(path);

        //SEPARATE
        printf("separate\n");
        main_separate("grid.png");

        printf("ia\n");
        predict();
        printf("saved_ocr\n");
        
        main_save_ocr(grille1);
    }

    //IA
    if (i == 1)
    {
        //SOLVER
        printf("solver\n");
        main_solver(grille1, 9);

        //SAVED
        printf("saved\n");
        main_save(grille1,grille2);
    }
}
