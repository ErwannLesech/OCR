#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "solver.h"

void print_sudoku(char argv[9][9]);
char a[9][9] = 
{
	{'5','3','.','.','7','.','.','.','.'},
	{'6','.','.','1','9','5','.','.','.'},
	{'.','9','8','.','.','.','.','6','.'},
	{'8','.','.','.','6','.','.','.','3'},
	{'4','.','.','8','.','3','.','.','1'},
	{'7','.','.','.','2','.','.','.','6'},
	{'.','6','.','.','.','.','2','8','.'},
	{'.','.','.','4','1','9','.','.','5'},
	{'.','.','.','.','8','.','.','7','9'}
};

int main(int argc, char** argv[9][9])
{
	/*if(argc != 2)
	{
		errx(EXIT_FAILURE, "%s", "A sudoku is needed");
	}*/

	//else
	//{
		print_sudoku(a);
		solver(a);
		print_sudoku(a);
	//}

	return EXIT_SUCCESS;
}


void print_sudoku(char argv[9][9])
{
	for(unsigned int i = 0; i < 9; i++)
	{
		if(i%3 == 0 && i != 0)
                {
			printf("\n");
                }

		for(unsigned int j = 0; j < 9; j++)
		{
			if(j%3 == 0 && j != 0)
			{
				printf(" ");
			}
			
			printf("%c", argv[i][j]);
		}

		printf("\n");

	}

	printf("\n");
}
