#include <stdio.h>
#include <stdlib.h>
#include "save_parameters.h"


void save_parameters(multiple_matrices *parameters, char path[])
{
	FILE *file = fopen(path, "w");

	matrix *hw = parameters->a;
	matrix *hb = parameters->b;
	matrix *ow = parameters->c;
	matrix *ob = parameters->d;

	int rows = hw->rows;
	int cols = hw->cols;

	//fprintf(file, "#1weights:\n");
	/*fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols - 1; j++)
		{
			fprintf(file, "%f ", get_value(hw, i, j));
		}
		fprintf(file, "%f", get_value(hw, i, cols - 1));
		fprintf(file, "\n");
	}

	fprintf(file, "\n");

	rows = hb->rows;
	cols = hb->cols;

	/*fprintf(file, "hb dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/
	//fprintf(file, "#1bias:\n");

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols - 1; j++)
		{
			fprintf(file, "%f ", get_value(hb, i, j));
		}
		fprintf(file, "%f", get_value(hb, i, cols - 1));
		fprintf(file, "\n");
	}

	fprintf(file, "\n");

	rows = ow->rows;
	cols = ow->cols;

	/*fprintf(file, "ow dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/
	//fprintf(file, "#2weights:\n");

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols - 1; j++)
		{
			fprintf(file, "%f ", get_value(ow, i, j));
		}
		fprintf(file, "%f", get_value(ow, i, cols - 1));
		fprintf(file, "\n");
	}

	fprintf(file, "\n");

	rows = ob->rows;
	cols = ob->cols;

	/*fprintf(file, "ob dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/
	//fprintf(file, "#1bias:\n");

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols - 1; j++)
		{
			fprintf(file, "%f ", get_value(ob, i, j));
		}
		fprintf(file, "%f", get_value(ob, i, cols - 1));
		fprintf(file, "\n");
	}
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

    matrix *hw = init_matrix(hidden_neurons, input_neurons, 0);

    matrix *hb = init_matrix(hidden_neurons, 1, 0);

    matrix *ow = init_matrix(output_neurons, hidden_neurons, 0);

    matrix *ob = init_matrix(output_neurons, 1, 0);

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
	
	if ((c == ' ' || c == '\n') && temp_index >= 7)
        {
	    dtemp = strtod(temp_value, NULL);

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

			 insert_value(&hw, rows, cols, dtemp);
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
                        insert_value(&hb, rows, 0, dtemp);
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
                        insert_value(&ow, rows, cols, dtemp);
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
                        insert_value(&ob, rows, 0, dtemp);
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
		temp_index++;
	}
   
    }
 
    fclose(input_file);
    free(temp_value);
    
    parameters.a = hw;
    parameters.b = hb;
    parameters.c = ow;
    parameters.d = ob;
    
    return parameters;
}
