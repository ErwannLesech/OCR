#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include "solver_hexa.h"

#define ROW_SIZE 16
#define COL_SIZE 16


int isValidMove(char sudoku[16][16], int row, int col, char c)
{
    for(unsigned int i = 0; i < 16; i++)
    {
        if(sudoku[i][col] != '.' && sudoku[i][col] == c)
        {
            return 0;
        }

        if (sudoku[row][i] != '.' && sudoku[row][i] == c)
        {
            return 0;
        }

        if (sudoku[4*(row/4) + i/4][4*(col/4) + i%4] != '.' 
                && sudoku[4*(row/4) + i/4][4*(col*4) + i%4] == c)
        {
            return 0;
        }
    }

    return 1;
}

int solver_hexa(char sudoku[16][16])
{
    for(unsigned int i = 0; i < 16; i++)
    {
        for(unsigned int j = 0; j < 16; j++)
        {
            if(sudoku[i][j] == '.')
            {
                for(char c = '1'; c <= 'F'; c++)
                {
                    printf("c = %c", c);
                    if(isValidMove(sudoku, i, j, c))
                    {
                        sudoku[i][j] = c;

                        if(solver_hexa(sudoku))
                        {
                            return 1;
                        }

                        else
                        {
                            sudoku[i][j] = '.';
                        }
                    }

                    if (c == '9')
                    {
                        c = ('A' - 1);
                    }
                }

                return 0;
            }
        }
    }

    return 1;    
}
