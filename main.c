#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Rotate/main.h"
#include "XOR_neural_network/main.h"
#include "Solver/main.h"
#include "Load_img/main.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("main: Argv missing\n");
        return EXIT_FAILURE;
    }
    if (strcmp(argv[1], "-xor") == 0)
    {
        main_xor(argc, argv);
    }
    else if (strcmp(argv[1], "-solver") == 0)
    {
        main_solver(argc, argv);
    }
    else if (strcmp(argv[1], "-rotate") == 0)
    {
        main_rotate(argc, argv);
    }
    else if(strcmp(argv[1], "-load_img") == 0)
    {
        main_load(argc, argv);
    }
    else if (strcmp(argv[1], "-help") == 0)
    {
        printf("\n-xor: xor gate neural network\n");
        printf("    -train: train the network\n");
        printf("    -weights: load and print weights of the trained network\n\n");
        printf("    -predict @arg1 @arg2: predict after training with input 1,2\n\n");
        printf("-solver: sudoku solver\n");
        printf("    -solve @arg: solve a sudoku\n");
        printf("    -print: print a sudoku solved\n");
        printf("    -printAndSolve: Solve a sudoku and print it\n");
    }
    else
    {
        printf("main: incorrect argv. -help for help.\n");
    }

    return EXIT_SUCCESS;
}
