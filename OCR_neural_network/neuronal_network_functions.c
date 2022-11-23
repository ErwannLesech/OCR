#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "neuronal_network_functions.h"

char list_of_paths[9][35] = {
"./OCR_neural_network/dataset/1.jpg"
"./OCR_neural_network/dataset/2.jpg",
"./OCR_neural_network/dataset/3.jpg",
"./OCR_neural_network/dataset/4.jpg",
"./OCR_neural_network/dataset/5.jpg",
"./OCR_neural_network/dataset/6.jpg",
"./OCR_neural_network/dataset/7.jpg",
"./OCR_neural_network/dataset/8.jpg",
"./OCR_neural_network/dataset/9.jpg"
};

/*char list_of_paths[9][35] = {
"00.png",
"01.png",
"02.png",
"03.png",
"04.png",
"05.png",
"06.png",
"07.png",
"08.png",
};*/

double sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}

double sigmoid_derivative(double x)
{
	return x * (1 - x);
}

double relu(double x)
{
	if(x > 0)
		return x;
	return 0;
}

double relu_derivative(double x)
{
	return x > 0;
}

double softmax(double x, size_t index, matrix *m)
{
	double exp_sum = 0;
	
	for(size_t i = 0; i < 9; i++)
	{
		exp_sum += exp(get_value(&m, i, 0));
	}

	return exp(get_value(&m, index, 0)) / exp_sum;
}


void init_input_matrix(matrix *input, matrix *exp_output, size_t nbInputs)
{

	srand(time(NULL));
	for (size_t n = 0; n < nbInputs; n++)
	{
		int random = rand() % 9;
		char *path = list_of_paths[random];
		insert_value(exp_output, 0, n, (double)path[29] - 48);

		SDL_Surface* surface = IMG_Load(path);
		SDL_Surface* new_surface = SDL_ConvertSurfaceFormat(surface, 
			SDL_PIXELFORMAT_RGB888, 0);
		Uint32* pixels = new_surface->pixels;
		SDL_PixelFormat* format = new_surface->format;
		SDL_LockSurface(new_surface);
		printf("test\n");
		for (int i = 0; i < 784; i++)
		{
			if (pixels[i] == NULL)
			{
				continue;
			// errx(EXIT_FAILURE, "%s", SDL_GetError());
			}

			Uint8 r, g, b;
			SDL_GetRGB(pixels[i], format, &r, &g, &b);
			double value = 0;
			if ((r+b+g)/3 >= 127)
			{
				value = 1;
			}
			else
			{
				value = 0;
			}
			insert_value(input, i, n, value);
		}
		SDL_FreeSurface(new_surface);
		SDL_UnlockSurface(new_surface);
	}

	printf("end\n");
}

multiple_result initialization(int input_neurons,
	int hidden_neurons, int output_neurons)
{
	matrix hw;
	matrix hb;
	matrix ow;
	matrix ob;

	init_rand_matrix(&hw, hidden_neurons, input_neurons);
	init_matrix(&hb, hidden_neurons, 1, 0);
	init_rand_matrix(&ow, output_neurons, hidden_neurons);
	init_matrix(&ob, output_neurons, 1, 0);

	multiple_result neurons;
	neurons.a = hw;
	neurons.b = hb;
	neurons.c = ow;
	neurons.d = ob;

	return neurons;
}


multiple_result forward_propagation(multiple_result *parameters,
	matrix *inputs)
{
	matrix hw = parameters->a;
	matrix hb = parameters->b;
	matrix ow = parameters->c;
	matrix ob = parameters->d;
	
	// HIDDEN LAYER
	matrix Z1;
	Z1 = dot_matrix(&hw, inputs);

	add_matrix(&Z1, &hb);
	matrix A1 = Z1;
	print_matrix(&A1);
	relu_matrix(&A1);
	print_matrix(&A1);
	
	// OUTPUT LAYER
	matrix A2;
	A2 = dot_matrix(&ow, &A1);
	add_matrix(&A1, &ob);

	softmax_matrix(&A2);
	
	// Return values
	multiple_result results;
	results.a = Z1;
	results.b = A1;
	results.c = A2;

	return results;
}

matrix one_hot(matrix exp_output)
{
	matrix one_hot_Y;
	init_matrix(&one_hot_Y, 9, exp_output.cols, 0);
	for (size_t i = 0; i < exp_output.cols; i++)
	{
		size_t value = (int)(get_value(&exp_output, 0, i));
		insert_value(&one_hot_Y, value - 1, i, 1);
	}
	return one_hot_Y;
}


multiple_result back_propagation(matrix *exp_outputs, matrix *inputs,
	multiple_result *parameters, multiple_result *forward_prop)
{
	matrix Z1 = forward_prop->a;
	matrix A1 = forward_prop->b;
	matrix A2 = forward_prop->c;
	matrix ow = parameters->c;
	double m = exp_outputs->cols;

	matrix dZ2;
	dZ2 = substract_matrix(&A2, exp_outputs);
	
	matrix A2_t;
	A2_t = transpose_matrix(&A1);
	matrix dW2;
	dW2 = dot_matrix(&dZ2, &A2_t);
	dW2 = multiply_matrix(&dW2, (1/m));

	matrix dB2;
	dB2 = add_col_matrix(&dZ2);
	dB2 = multiply_matrix(&dB2, (1/m));

	matrix dZ1;
	matrix ow_t = transpose_matrix(&ow);
	dZ1 = dot_matrix(&ow_t, &dZ2);
	d_relu_matrix(&dZ1, &Z1);
	
	matrix dW1;
	matrix A0_t;
	A0_t = transpose_matrix(inputs);
	dW1 = dot_matrix(&dZ1, &A0_t);
	dW1 = multiply_matrix(&dW1, (1/m));

	matrix dB1;
	dB1 = add_col_matrix(&dZ1);
	dB1 = multiply_matrix(&dB1, (1/m));

	multiple_result back_prop;
	back_prop.a = dW2;
	back_prop.b = dB2;
	back_prop.c = dW1;
	back_prop.d = dB1;

	return back_prop;
}

multiple_result *upgrade_parameters(matrix inputs, multiple_result *parameters,
	multiple_result *forward_prop, multiple_result *back_prop, double lr)
{
	matrix hw = parameters->a;
	matrix hb = parameters->b;
	matrix ow = parameters->c;
	matrix ob = parameters->d;

	matrix dW2 = back_prop->a;
	matrix dB2 = back_prop->b;
	matrix dW1 = back_prop->c;
	matrix dB1 = back_prop->d;
	
	matrix dOW;
	dOW = multiply_matrix(&dW2, lr);
	ow = substract_matrix(&ow, &dOW);
	
	matrix dOB;
	dOB = multiply_matrix(&dB2, lr);
	ob = substract_matrix(&ob, &dOB);

	matrix dHW;
	dHW = multiply_matrix(&dW1, lr);
	hw = substract_matrix(&hw, &dHW);

	matrix dHB;
	dHB = multiply_matrix(&dW1, lr);
	hb = substract_matrix(&hb, &dHB);

	parameters->a = hw;
	parameters->b = hb;
	parameters->c = ow;
	parameters->d = ob;

	return parameters;
}



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

multiple_result load_parameters(char path[])
{
	FILE *input_file = fopen(path, "r");
    char c;
    int i = 0;
    char temp[50];
    char *useless;
    double dtemp = 0;

    matrix hw;
    init_matrix(&hw, 2, 2, 0);
	matrix hb;
    init_matrix(&hb, 1, 2, 0);
	matrix ow;
    init_matrix(&ow, 2, 1, 0);
	matrix ob;
    init_matrix(&ob, 1, 1, 0);
    multiple_result parameters;

    int z = 0;

    for (size_t j = 0; j < 50; j++)
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