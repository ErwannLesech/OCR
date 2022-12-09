#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

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

int solve_hexadoku(char sudoku[16][16])
{
    for(unsigned int i = 0; i < 16; i++)
    {
        for(unsigned int j = 0; j < 16; j++)
        {
            if(sudoku[i][j] == '.')
            {
                for(char c = '1'; c <= '9'; c++)
                {
                    if(isValidMove(sudoku, i, j, c))
                    {
                        sudoku[i][j] = c;

                        if(solve_hexadoku(sudoku))
                        {
                            return 1;
                        }

                        else
                        {
                            sudoku[i][j] = '.';
                        }
                    }
                }

                for(char c = 'A'; c <= 'F'; c++)
                {
                    if(isValidMove(sudoku, i, j, c))
                    {
                        sudoku[i][j] = c;

                        if(isValidMove(sudoku, i, j, c))
                        {
                            return 1;
                        }

                        else
                        {
                            sudoku[i][j] = '.';
                        }
                    }
                }

                return 0;
            }
        }
    }

    return 1;    
}