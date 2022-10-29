#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "XOR_neural_network/main.h"
#include "Solver/main.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("main: Argv missing");
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
    else if (strcmp(argv[1], "-help") == 0)
    {
        printf("\n-xor: xor gate neural network\n");
        printf("    -train: train the network\n");
        printf("    -predict: predict after training an input\n\n");
        printf("-solver: sudoku solver\n");
        printf("    -solve @arg: solve a sudoku.\n");
        printf("    -print: print a sudoku solved.\n");
        printf("    -printAndSolve: Solve a sudoku and print it.\n");
    }
    else
    {
        printf("main: incorrect argv. -help for help.\n");
    }

    return EXIT_SUCCESS;
}