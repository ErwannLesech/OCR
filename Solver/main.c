#include <stdio.h>
#include <stdlib.h>

#include "solver.h"

int main(int argc, char argv[9][9])
{
	if(argc != 2)
	{
		errx(EXIT_FAILURE, "%s", "A sudoku is needed");
	}

	else
	{
		print_sudoku(argv);
		solver(ardv);
		print_sudoku(argv);
	}

	return EXIT_SUCCESS;
}


void print_sudoku(char argv[9][9])
{
	for(unsigned int i = 0; i < 9; i++)
	{
		for(unsigned int j = 0; j < 9; j++)
		{
			if(j%3 == 0)
			{
				printf(" ");
			}

			printf("%s", argv[i][j]);
		}

		if(j%3 == 0)
                {
			printf("\n");
                }

		printf("\n");

	}

}
