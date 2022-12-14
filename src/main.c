#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Rotate/main.h"
#include "OCR_neural_network/main.h"
#include "Solver/main.h"
#include "Load_img/main.h"
#include "Separate/main.h"
#include "Interface/main.h"
#include "Saved/main.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("main: Argv missing\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-nn") == 0)
    {
        main_neural_network(argc, argv);
    }

    else if (strcmp(argv[1], "-solver") == 0)
    {
        main_solver(argv[2], 9);
    }

    else if (strcmp(argv[1], "-rotate") == 0)
    {
        main_rotate(argc, argv);
    }

    else if(strcmp(argv[1], "-load_img") == 0)
    {
        main_load(argv[2]);
    }

    else if(strcmp(argv[1], "-separate") == 0)
    {
        main_separate(argv[2]);
    }
    else if(strcmp(argv[1], "-save") == 0)
    {
	main_save(argc,argv);
    }
    else if(strcmp(argv[1], "-interface") == 0)
    {
	main_interface(argc,argv);
    }

    else if (strcmp(argv[1], "-help") == 0)
    {
        printf("\n-xor: xor gate neural network\n");
        printf("    -train: train the network\n");
        printf("    -weights: load and print weights of the network\n\n");
        printf("    -predict @arg1 @arg2: predict after training\n\n");
        printf("-solver: sudoku solver\n");
        printf("    -solve @arg: solve a sudoku\n");
        printf("    -print: print a sudoku solved\n");
        printf("    -printAndSolve: Solve a sudoku and print it\n");
        /*printf("-dataset: extract dataset for neural network\n");
        printf("    -train: extract train dataset for neural network\n");
        printf("    -test: extract test dataset for neural network\n");*/
    }
    else
    {
        printf("main: incorrect argv. -help for help.\n");
    }

    return EXIT_SUCCESS;
}
