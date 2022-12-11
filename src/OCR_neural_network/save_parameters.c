#include <stdio.h>
#include <stdlib.h>
#include "save_parameters.h"


void save_parameters(multiple_matrices parameters, char path[])
{
	FILE *file = fopen(path, "w");

	matrix *w1 = parameters.a;
	matrix *b1 = parameters.b;
	matrix *w2 = parameters.c;
	matrix *b2 = parameters.d;

	int rows = w1->rows;
	int cols = w1->cols;

	//fprintf(file, "#1weights:\n");
	/*fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols - 1; j++)
		{
			fprintf(file, "%f ", get_value(w1, i, j));
		}
		fprintf(file, "%f", get_value(w1, i, cols - 1));
		fprintf(file, "\n");
	}

	fprintf(file, "\n");

	rows = b1->rows;
	cols = b1->cols;

	/*fprintf(file, "hb dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/
	//fprintf(file, "#1bias:\n");

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols - 1; j++)
		{
			fprintf(file, "%f ", get_value(b1, i, j));
		}
		fprintf(file, "%f", get_value(b1, i, cols - 1));
		fprintf(file, "\n");
	}

	fprintf(file, "\n");

	rows = w2->rows;
	cols = w2->cols;

	/*fprintf(file, "ow dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/
	//fprintf(file, "#2weights:\n");

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols - 1; j++)
		{
			fprintf(file, "%f ", get_value(w2, i, j));
		}
		fprintf(file, "%f", get_value(w2, i, cols - 1));
		fprintf(file, "\n");
	}

	fprintf(file, "\n");

	rows = b2->rows;
	cols = b2->cols;

	/*fprintf(file, "ob dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/
	//fprintf(file, "#1bias:\n");

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols - 1; j++)
		{
			fprintf(file, "%f ", get_value(b2, i, j));
		}
		fprintf(file, "%f", get_value(b2, i, cols - 1));
		fprintf(file, "\n");
	}

	fprintf(file, "\n");

	fclose(file);

}


multiple_matrices load_parameters(char path[], int input_neurons,
	int hidden_neurons, int output_neurons)
{
    FILE *input_file = fopen(path, "r");
    char c;
    double dtemp;
    //char temp_value[8];
    char *temp_value = calloc(8, sizeof(char));
    //char *p = temp_value;
    int temp_index = 0;
    int negative = 0;
    int matrix_number = 0;
    int rows = 0, cols = 0;

    matrix *w1 = init_matrix(hidden_neurons, input_neurons, 0);

    matrix *b1 = init_matrix(hidden_neurons, 1, 0);

    matrix *w2 = init_matrix(output_neurons, hidden_neurons, 0);

    matrix *b2 = init_matrix(output_neurons, 1, 0);


    multiple_matrices parameters;


    while((c=fgetc(input_file)) != EOF)
    {
	//printf("%f", hw.data[0]);
	//printf("mn: %i\n", matrix_number);
        

	/*if(i <= hidden_neurons * input_neurons * 8)
	{
		if(c != ' ' && c != '\n' && c != '-')
		{
			i++;
		}
	}*/
	printf("%c", c);
	
	if ((c == ' ' || c == '\n') && temp_index >= 7)
        {
		printf("%f ", temp_value);
	    dtemp = strtod(temp_value, NULL);
		printf("%f ", dtemp);

	    if(negative)
	    {
		    dtemp *= -1;
	    }
	   
            switch(matrix_number)
	    {
		    case 0:
			    /*if(rows == 0 && cols == 0)
			    {
			    	for(int i = 0; i < 8; i++)
				{
			    		printf("%c", temp_value[i]);
				}
			    	printf("\n");

				printf("%f\n", dtemp);
				insert_value(&hw, 0, 0, dtemp);
				printf("%f", hw.data[0]);
				rows++;
				cols++;
				
			    }*/
			 printf("%f\n ", dtemp);
			 insert_value(w1, rows, cols, dtemp);
			 //printf("row: %i, col: %i\n", rows, cols);
			 if(rows  >= hidden_neurons-1 && cols >= input_neurons-1)
			 {
				//iprintf("%f", dtemp);
			 	rows = 0;
				cols = 0;
				matrix_number++;
			 }
			 
			 else if(cols >= input_neurons-1)
			 {
			 	rows++;
				cols = 0;
			 }

			 else
			 {
			 	cols++;
			 }

			 break;

            case 1:
				/*for(int i = 0; i < 8; i++)
				{
					printf("%c", temp_value[i]);
				}*/

				//printf("row: %i, col: %i, temp: %f\n", rows, cols, dtemp);
				insert_value(b1, rows, 0, dtemp);
				if(rows == hidden_neurons-1)
				{
					rows = 0;
					cols = 0;
					matrix_number++;
				}
				
				else
				{
					rows++;
				}

				break;
                    
            case 2:
                insert_value(w2, rows, cols, dtemp);
				if(rows == output_neurons-1 && cols == hidden_neurons-1)
				{
					rows = 0;
					cols = 0;
					matrix_number++;
				}
				
				else if(cols == hidden_neurons-1)
				{
					rows++;
					cols = 0;
				}

				else
				{
					cols++;
				}

                break;
                    
            case 3:
                insert_value(b2, rows, 0, dtemp);
				if(rows == output_neurons-1)
				{
					rows = 0;
					cols = 0;
					matrix_number++;
				}

				else
				{
					rows++;
				}

				break;
						
			default:
				break;
		}

		temp_index = 0;
		negative = 0;
        }
	
	else if(c == '-')
	{
		negative = 1;
	}

	else
	{
		temp_value[temp_index] = c;
		printf("%c - %c\n", c, temp_value[temp_index]);
		temp_index++;
	}
   
    }
 
    fclose(input_file);
    free(temp_value);
    
    parameters.a = w1;
    parameters.b = b1;
    parameters.c = w2;
    parameters.d = b2;
	print_matrix(w1);
	print_matrix(b1);
	print_matrix(w2);
	print_matrix(b2);
    
    return parameters;
}
