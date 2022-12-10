#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include "solver.h"
#include "solver_hexa.h"

char simple_grid[9][9] = 
{
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'}
};

char hexa_grid[16][16] = 
{
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.'}
};


void read_sudoku(char *filename, unsigned int max)
{
	FILE *input_file = fopen(filename, "r");
	unsigned int i = 0;
	unsigned int j = 0;
	char c;
	
	while((c=fgetc(input_file)) != EOF)
	{
		if(c != ' ' && c != '\n')
		{
			if(max == 9)
			{
				simple_grid[i][j] = c;
			}

			else
			{
				hexa_grid[i][j] = c;
			}
			j++;

			if(j > max-1)
			{
				j = 0;
				i++;
			}
		}
	}
	
	/*char *content;
	while(fscanf(input_file, "%[n]", content) != EOF)
	{
		printf("> %s\n", content);
	}*/
	fclose(input_file);
}


void print_sudoku(unsigned int max)
{
	unsigned int mod;

	if(max == 9)
	{
		mod = 3;
	}

	else
	{
		mod = 4;
	}

	for(unsigned int i = 0; i < max; i++)
	{
		if(i%mod == 0 && i != 0)
                {
			printf("\n");
                }

		for(unsigned int j = 0; j < max; j++)
		{
			if(j%mod == 0 && j != 0)
			{
				printf(" ");
			}
			
			if(max == 9)
			{
				printf("%c", simple_grid[i][j]);
			}

			else
			{
				printf("%c", hexa_grid[i][j]);
			}
		}

		printf("\n");

	}

	printf("\n");
}


void save_sudoku(char *filename, unsigned int max)
{
	FILE* output_file = fopen(filename, "w");

	unsigned int mod;

	if(max == 9)
	{
		mod = 3;
	}

	else
	{
		mod = 4;
	}


	for(unsigned int i = 0; i < max; i++)
	{
		if(i%mod == 0 && i != 0)
                {
			//fwrite('\n', 1, 1, output_file);
			//write(output_file, "space", 5);
			fprintf(output_file, "\n");
                }

		for(unsigned int j = 0; j < max; j++)
		{
			if(j%mod == 0 && j != 0)
			{
				//fwrite(" ", 1, 1, output_file);
				//write(output_file, " ", 1);
				fprintf(output_file, " ");
			}
			
			//fwrite(a[i][j], 1, 1, output_file);
			//write(output_file, a[i][j], 1);
			/*printf("%c", a[i][j]);
			printf("%i", i);
			printf("%i\n", j);*/
			
			if(max == 9)
			{
				fprintf(output_file, "%c", simple_grid[i][j]);
			}

			else
			{
				fprintf(output_file, "%c", hexa_grid[i][j]);
			}
		}

		//fwrite('\n', 1, 1, output_file);
		//write(output_file, "space", 5);
		fprintf(output_file, "\n");
	}

	//fwrite('\n', 1, 1, output_file);
	//write(output_file, "space", 5);
	fprintf(output_file, "\n");
	fclose(output_file);
}


int main_solver(char* sudoku, unsigned int simple_or_hexa)
{
	read_sudoku(sudoku, simple_or_hexa);
	print_sudoku(simple_or_hexa);

	if(simple_or_hexa == 9)
	{
		solver(simple_grid);
	}

	else
	{
		solver_hexa(hexa_grid);
	}

	print_sudoku(simple_or_hexa);

	char filename[strlen((sudoku + 8))];
	size_t i = 0;
	for (i = 0; i < strlen((sudoku)); i++)
	{
		filename[i] = sudoku[i];
	}

	filename[i] = '.';
	filename[i+1] = 'r';
	filename[i+2] = 'e';
	filename[i+3] = 's';
	filename[i+4] = 'u';
	filename[i+5] = 'l';
	filename[i+6] = 't';
	filename[i+7] = '\0';
	save_sudoku(filename, simple_or_hexa);

	return 0;
}


int main(int argc, char **argv)
{
	if(argc < 3)
	{
		errx(EXIT_FAILURE, "%s", "A valid sudoku is needed");
	}
	
	unsigned int simple_or_hexa = 16;//(unsigned int)argv[2];
	printf("%u\n", simple_or_hexa);
	main_solver(argv[1], simple_or_hexa);
		
	return EXIT_SUCCESS;
}

