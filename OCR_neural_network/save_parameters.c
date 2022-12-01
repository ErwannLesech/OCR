#include <stdio.h>
#include <stdlib.h>
#include "save_parameters.h"


void save_parameters(multiple_result *parameters, char path[])
{
	FILE *file = fopen(path, "w");

	matrix hw = parameters->a;
	matrix hb = parameters->b;
	matrix ow = parameters->c;
	matrix ob = parameters->d;

	int rows = hw.rows;
	int cols = hw.cols;

	//fprintf(file, "#1weights:\n");
	/*fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols - 1; j++)
		{
			fprintf(file, "%f ", get_value(&hw, i, j));
		}
		fprintf(file, "%f", get_value(&hw, i, cols - 1));
		fprintf(file, "\n");
	}

	fprintf(file, "\n");

	rows = hb.rows;
	cols = hb.cols;

	/*fprintf(file, "hb dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/
	//fprintf(file, "#1bias:\n");

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols - 1; j++)
		{
			fprintf(file, "%f ", get_value(&hb, i, j));
		}
		fprintf(file, "%f", get_value(&hb, i, cols - 1));
		fprintf(file, "\n");
	}

	fprintf(file, "\n");

	rows = ow.rows;
	cols = ow.cols;

	/*fprintf(file, "ow dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/
	//fprintf(file, "#2weights:\n");

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols - 1; j++)
		{
			fprintf(file, "%f ", get_value(&ow, i, j));
		}
		fprintf(file, "%f", get_value(&ow, i, cols - 1));
		fprintf(file, "\n");
	}

	fprintf(file, "\n");

	rows = ob.rows;
	cols = ob.cols;

	/*fprintf(file, "ob dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/
	//fprintf(file, "#1bias:\n");

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols - 1; j++)
		{
			fprintf(file, "%f ", get_value(&ob, i, j));
		}
		fprintf(file, "%f", get_value(&ob, i, cols - 1));
		fprintf(file, "\n");
	}
}


multiple_result load_parameters(char path[], int input_neurons,
	int hidden_neurons, int output_neurons)
{
	FILE *input_file = fopen(path, "r");
    char c;
    int i = 0;
    char *temp;
    char *useless;
    double dtemp = 0;

    matrix hw;
    init_matrix(&hw, hidden_neurons, input_neurons, 0);
	matrix hb;
    init_matrix(&hb, hidden_neurons, 1, 0);
	matrix ow;
    init_matrix(&ow, output_neurons, hidden_neurons, 0);
	matrix ob;
    init_matrix(&ob, output_neurons, 1, 0);

    multiple_result parameters;

    int z = 0;

    for (size_t j = 0; j < hidden_neurons * input_neurons * 2; j++)
    {
        temp[j] = '\0';
    }
    i = 0;

    while((c=fgetc(input_file)) != EOF)
	{
        temp[i] = c;
        i++;
        
        if (c == ' ' || c == '\n')
        {
            
            if(temp[1] != '\0' && temp[1] != ' ')
            {
                dtemp = strtod(temp, &useless);

                switch (z)
                {
                    case 0:
                        insert_value(&hw, 0, 0, dtemp);
                        break;

                    case 1:
                        insert_value(&hw, 0, 1, dtemp);
                        break;

                    case 2:
                        insert_value(&hw, 1, 0, dtemp);
                        break;

                    case 3:
                        insert_value(&hw, 1, 1, dtemp);
                        break;

                    case 4:
                        insert_value(&hb, 0, 0, dtemp);
                        break;
                    
                    case 5:
                        insert_value(&hb, 0, 1, dtemp);
                        break;

                    case 6:
                        insert_value(&ow, 0, 0, dtemp);
                        break;
                    
                    case 7:
                        insert_value(&ow, 1, 0, dtemp);
                        break;

                    case 8:
                        insert_value(&ob, 0, 0, dtemp);
                        break;
                    
                    default:
                        break;
                }
                for (size_t j = 0; j < 50; j++)
                {
                    temp[j] = '\0';
                }
                i = 0;
                z++;
                dtemp = 0;
            }
        }
	}
    fclose(input_file);

	parameters.a = hw;
	parameters.b = hb;
	parameters.c = ow;
	parameters.d = ob;

	return parameters;
}