#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "neuronal_network_functions.h"

char **list_of_paths = {
	"./OCR_neural_network/dataset/1.jpg",
	"./OCR_neural_network/dataset/2.jpg",
	"./OCR_neural_network/dataset/3.jpg",
	"./OCR_neural_network/dataset/4.jpg",
	"./OCR_neural_network/dataset/5.jpg",
	"./OCR_neural_network/dataset/6.jpg",
	"./OCR_neural_network/dataset/7.jpg",
	"./OCR_neural_network/dataset/8.jpg",
	"./OCR_neural_network/dataset/9.jpg"
};

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
		exp_sum += exp(get_value(&m, i, 0));
	
	return exp(get_value(&m, index, 0)) / exp_sum;
}


void init_input_matrix(matrix *input, matrix *exp_output, size_t nbInputs)
{
	printf("test");
	srand(time(NULL));
	printf("test");
	for (size_t n = 0; n < nbInputs; n++)
	{
		char *path = list_of_paths[rand() % 9];
		printf("%s\n", path);
		insert_value(exp_output, 0, n, (double)path[30] - 48);

		SDL_Surface* surface = IMG_Load(path);
		SDL_Surface* new_surface = SDL_ConvertSurfaceFormat(surface, 
			SDL_PIXELFORMAT_RGB888, 0);
		Uint32* pixels = surface->pixels;
		SDL_PixelFormat* format = surface->format;
		SDL_LockSurface(surface);
		for (int i = 0; i < 28; i++)
		{
			for (size_t j = 0; j < 28; j++)
			{
				if (pixels[i * 28 + j] == NULL)
				{
					printf("null\n");
					SDL_UnlockSurface(surface);
					return;
				// errx(EXIT_FAILURE, "%s", SDL_GetError());
				}

				Uint8 r, g, b;
				SDL_GetRGB(pixels[i * 28 + j], format, &r, &g, &b);
				double value = 0;
				printf("test:%d\n", (r+b+g)/3);
				if ((r+b+g)/3 >= 127)
				{
					value = 1;
				}
				else
				{
					value = 0;
				}
				insert_value(input, i, j, value);
			}
		}
		SDL_FreeSurface(surface);
		SDL_UnlockSurface(surface);
	}
}

multiple_result initialization(int input_neurons,
	int hidden_neurons, int output_neurons)
{
	matrix hw;
	matrix hb;
	matrix ow;
	matrix ob;

	init_rand_matrix(&hw, input_neurons, hidden_neurons);
	init_matrix(&hb, 1, hidden_neurons, 0);
	init_rand_matrix(&ow, hidden_neurons, output_neurons);
	init_matrix(&ob, 1, output_neurons, 0);

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

	matrix hidden_propagation;
	hidden_propagation = dot_matrix(&hw, inputs);

	add_matrix(&hidden_propagation, &hb);
	relu_matrix(&hidden_propagation);
	
	// OUTPUT LAYER
	matrix output_propagation;
	output_propagation = dot_matrix(&ow, &hidden_propagation);
	add_matrix(&hidden_propagation, &ob);

	softmax_matrix(&output_propagation);

	// Return values

	multiple_result results;
	results.a = hidden_propagation;
	results.b = output_propagation;


	return results;
}

multiple_result back_propagation(matrix *exp_outputs,
	multiple_result *parameters, multiple_result *forward_prop)
{

	matrix hidden_prop = forward_prop->a;
	matrix output_prop = forward_prop->b;
	matrix ow = parameters->c;

	matrix error_output_layer;
	error_output_layer = substract_matrix(exp_outputs, &output_prop);
	
	d_sigmoid_matrix(&error_output_layer, &output_prop);

	matrix ow_t;
	ow_t = transpose_matrix(&ow);

	matrix error_hidden_layer;
	error_hidden_layer = dot_matrix(&error_output_layer, &ow_t);
	
	d_sigmoid_matrix(&error_hidden_layer, &hidden_prop);

	multiple_result back_prop;
	back_prop.a = error_output_layer;
	back_prop.b = error_hidden_layer;

	return back_prop;
}

multiple_result *upgrade_parameters(matrix inputs, multiple_result *parameters,
	multiple_result *forward_prop, multiple_result *back_prop, double lr)
{
	matrix hw = parameters->a;
	matrix hb = parameters->b;
	matrix ow = parameters->c;
	matrix ob = parameters->d;

	matrix hidden_prop = forward_prop->a;
	// matrix output_prop = forward_prop->b;

	matrix d_predicted_output = back_prop->a;
	matrix d_hidden_layer = back_prop->b;

	matrix hidden_prop_t;
	hidden_prop_t = transpose_matrix(&hidden_prop);

	matrix w2_delta;
	w2_delta = dot_matrix(&hidden_prop_t, &d_predicted_output);
	w2_delta = multiply_matrix(&w2_delta, lr);
	add_matrix(&ow, &w2_delta);
	matrix b2_delta;
	b2_delta = add_row_matrix(&d_predicted_output);
	b2_delta = multiply_matrix(&b2_delta, lr);
	add_matrix(&ob, &b2_delta);

	matrix inputs_t;
	inputs_t = transpose_matrix(&inputs);

	matrix w1_delta;
	w1_delta = dot_matrix(&inputs_t, &d_hidden_layer);
	w1_delta = multiply_matrix(&w1_delta, lr);
	add_matrix(&hw, &w1_delta);

	matrix b1_delta;
	b1_delta = add_row_matrix(&d_hidden_layer);
	b1_delta = multiply_matrix(&b1_delta, lr);
	add_matrix(&hb, &b1_delta);
	

	parameters->a = hw;
	parameters->b = hb;
	parameters->c = ow;
	parameters->d = ob;

	return parameters;
}

double predict_xor(multiple_result *parameters, matrix inputs, 
	int inputA, int inputB)
{
	matrix hw = parameters->a;
	matrix hb = parameters->b;
	matrix ow = parameters->c;
	matrix ob = parameters->d;

	matrix hidden_propagation;
	hidden_propagation = dot_matrix(&inputs, &hw);

	add_matrix(&hidden_propagation, &hb);
	sigmoid_matrix(&hidden_propagation);
	
	// OUTPUT LAYER
	matrix output_propagation;
	output_propagation = dot_matrix(&hidden_propagation, &ow);
	add_matrix(&output_propagation, &ob);

	sigmoid_matrix(&output_propagation);
	
	double result = 0;
	// print values
	if(inputA == 0 && inputB == 0)
	{
		result = get_value(&output_propagation, 2, 0);
		printf("Input [0, 0] = %i\n", (int)round(result));
	}
	else if (inputA == 1 && inputB == 1)
	{
		result = get_value(&output_propagation, 3, 0);
		printf("Input [1, 1] = %i\n", (int)round(result));
	}
	else if (inputA == 1 && inputB == 0)
	{
		result = get_value(&output_propagation, 0, 0);
		printf("Input [1, 0] = %i\n", (int)round(result));
	}
	else if (inputA == 0 && inputB == 1)
	{
		result = get_value(&output_propagation, 1, 0);
		printf("Input [0, 1] = %i\n", (int)round(result));
	}

	free_matrix(&inputs);
	free_matrix(&hidden_propagation);
	free_matrix(&output_propagation);

	return result;
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