#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "solver.h"

char a[9][9] = 
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


void read_sudoku(char *filename)
{
	FILE *input_file = fopen(filename, "r");
	int i = 0;
	int j = 0;
	char c;
	
	while((c=fgetc(input_file)) != EOF)
	{
		if(c != ' ' && c != '\n')
		{
			a[i][j] = c;
			j++;

			if(j > 8)
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


void print_sudoku()
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
			
			printf("%c", a[i][j]);
		}

		printf("\n");

	}

	printf("\n");
}


void save_sudoku(char *filename)
{
	FILE* output_file = fopen(filename, "w");

	for(unsigned int i = 0; i < 9; i++)
	{
		if(i%3 == 0 && i != 0)
                {
			//fwrite('\n', 1, 1, output_file);
			//write(output_file, "space", 5);
			fprintf(output_file, "\n");
                }

		for(unsigned int j = 0; j < 9; j++)
		{
			if(j%3 == 0 && j != 0)
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

			fprintf(output_file, "%c", a[i][j]);
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


int main(int argc, char **argv)
{
	if(argc != 2)
	{
		errx(EXIT_FAILURE, "%s", "A valid sudoku is needed");
	}

	else
	{
		read_sudoku(argv[1]);
		printf("a");
		solver(a);
		printf("b");
		char *filename = "test_grid.result";
		save_sudoku(filename);
	}

	return EXIT_SUCCESS;
}
