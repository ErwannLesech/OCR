#include <stdio.h>
#include <stdlib.h>

#include "solver.h"

int is_valid(char argv[9][9], int row, int col, char c);

int solver(char argv[9][9])
{
	for(unsigned int i = 0; i < 9; i++)
	{
		for(unsigned int j = 0; j < 9; j++)
		{
			if(argv[i][j] == '.')
			{
				for(char c = '1'; c <= '9'; c++)
				{
					if(is_valid(argv, i, j, c))
					{
						argv[i][j] = c;

						if(solver(argv))
						{
							return 1;
						}

						else
						{
							argv[i][j] = '.';
						}
					}
				}

				return 0;
			}
		}
	}

	return 1;	
}

int is_valid(char argv[9][9], int row, int col, char c)
{
	for(unsigned int i = 0; i < 9; i++)
	{
		if(argv[i][col] != '.' && argv[i][col] == c)
		{
			return 0;
		}

		if (argv[row][i] != '.' && argv[row][i] == c)
		{
        		return 0;
		}

		if (argv[3*(row/3) + i/3][3*(col/3) + i%3] != '.' 
				&& argv[3*(row/3) + i/3][3*(col/3) + i%3] == c)
		{
			return 0;
		}
	}
	
	return 1;
}
