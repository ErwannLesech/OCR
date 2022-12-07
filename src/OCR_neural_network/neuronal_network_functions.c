#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "neuronal_network_functions.h"
#include "matrix.h"


double cost_function(double output, double exp_output)
{
	return pow((exp_output - output), 2);
}


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


double softmax(x, sum)
{
	return exp(x) / sum;
}


void init_input_matrix_test(matrix *input, char *path)
{
	SDL_Surface* surface = IMG_Load(path);
	SDL_Surface* new_surface = SDL_ConvertSurfaceFormat(surface, 
		SDL_PIXELFORMAT_RGB888, 0);
	Uint32* pixels = new_surface->pixels;
	SDL_PixelFormat* format = new_surface->format;
	SDL_LockSurface(new_surface);
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
		/*if ((r+b+g)/3 >= 127)
		{
			value = 1;
		}
		else
		{
			value = 0;
		}*/
		value = (double)((r+b+g)/(double)3)/(double)255;
		insert_value(input, i, 0, value);
	}
	SDL_FreeSurface(new_surface);
	SDL_UnlockSurface(new_surface);
}


void init_input_matrix(matrix *input, matrix *exp_output, size_t nbInputs)
{

	srand(time(NULL));
	for (size_t n = 0; n < nbInputs; n++)
	{
		int number = rand() % 10;
		int random = rand() % 8;
		int random2 = rand() % 10;
		char path[46] = "./OCR_neural_network/dataset/training/";
		path[38] = number + 48;
		path[39] = '/';
		path[40] = random + 48;
		path[41] = random2 + 48;
		path[42] = '.';
		path[43] = 'j';
		path[44] = 'p';
		path[45] = 'g';
		path[46] = '\0';
		printf("%s\n", path);
		printf("%lu\n", n);
		insert_value(exp_output, 0, n, (double)path[38] - 48);

		SDL_Surface* surface = IMG_Load(path);
		if (surface == NULL)
		{
			printf("Error: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		SDL_Surface* new_surface = SDL_ConvertSurfaceFormat(surface, 
			SDL_PIXELFORMAT_RGB888, 0);
		Uint32* pixels = new_surface->pixels;
		SDL_PixelFormat* format = new_surface->format;
		SDL_FreeSurface(surface);
		SDL_LockSurface(new_surface);
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
			/*if ((r+b+g)/3 >= 127)
			{
				value = 1;
			}
			else
			{
				value = 0;
			}*/
			value = (double)((r+b+g)/(double)3)/(double)255;
			insert_value(input, i, n, value);
		}
		SDL_UnlockSurface(new_surface);
		SDL_FreeSurface(new_surface);
	}
}


multiple_result initialization(int input_neurons,
	int hidden_neurons, int output_neurons)
{
	matrix hw;
	matrix hb;
	matrix ow;
	matrix ob;

	init_rand_matrix(&hw, hidden_neurons, input_neurons);
	init_rand_matrix(&hb, hidden_neurons, 1);
	init_rand_matrix(&ow, output_neurons, hidden_neurons);
	init_rand_matrix(&ob, output_neurons, 1);

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
	add_matrix_bias(&Z1, &hb);

	printf("test0\n");
	print_matrix(&Z1);

	matrix A1 = Z1;
	relu_matrix(&A1);

	printf("test\n");
	print_matrix(&A1);
		
	// OUTPUT LAYER
	matrix Z2;
	Z2 = dot_matrix(&ow, &A1);
	add_matrix_bias(&Z2, &ob);

	printf("test1\n");
	print_matrix(&Z2);

	matrix A2 = copy_matrix(&Z2);
	softmax_matrix(&A2);

	printf("test2\n");
	print_matrix(&A2);
	
	// Return values
	multiple_result results;
	results.a = Z1;
	results.b = A1;
	results.c = Z2;

	return results;
}


matrix exp_output_init(matrix exp_output)
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

// Backpropagation
multiple_result_bis back_propagation(matrix *exp_outputs, matrix *inputs,
	multiple_result *parameters, multiple_result *forward_prop)
{
	matrix Z1 = forward_prop->a;
	matrix A1 = forward_prop->b;
	matrix A2 = forward_prop->c;
	matrix ow = parameters->c;
	double m = exp_outputs->cols;

	matrix dZ2;
	dZ2 = substract_matrix(&A2, exp_outputs);
	
	matrix A1_t;
	A1_t = transpose_matrix(&A1);
	matrix dW2;
	dW2 = dot_matrix(&dZ2, &A1_t);
	dW2 = multiply_matrix(&dW2, (1/m));

	double dB2 = 0;
	double sum = sum_matrix(&dZ2);
	dB2 = sum/m;

	matrix dZ1;
	matrix ow_t = transpose_matrix(&ow);
	dZ1 = dot_matrix(&ow_t, &dZ2);
	d_relu_matrix(&dZ1, &Z1);
	
	matrix dW1;
	matrix A0_t;
	A0_t = transpose_matrix(inputs);
	dW1 = dot_matrix(&dZ1, &A0_t);
	dW1 = multiply_matrix(&dW1, (1/m));

	double dB1 = 0;
	sum = sum_matrix(&dZ1);
	dB1 = sum/m;

	multiple_result_bis back_prop;
	back_prop.a = dW2;
	back_prop.b = dB2;
	back_prop.c = dW1;
	back_prop.d = dB1;

	return back_prop;
}


multiple_result *upgrade_parameters(matrix inputs, multiple_result *parameters,
	multiple_result *forward_prop, multiple_result_bis *back_prop, double lr)
{
	matrix hw = parameters->a;
	matrix hb = parameters->b;
	matrix ow = parameters->c;
	matrix ob = parameters->d;

	matrix dW2 = back_prop->a;
	double dB2 = back_prop->b;
	matrix dW1 = back_prop->c;
	double dB1 = back_prop->d;
	
	matrix dOW;
	dOW = multiply_matrix(&dW2, lr);
	ow = substract_matrix(&ow, &dOW);
	
	matrix dOB;
	ob = substract_matrix_scal(&ob, dB2*lr);

	matrix dHW;
	dHW = multiply_matrix(&dW1, lr);
	hw = substract_matrix(&hw, &dHW);

	matrix dHB;
	hb = substract_matrix_scal(&hb, dB1*lr);

	parameters->a = hw;
	parameters->b = hb;
	parameters->c = ow;
	parameters->d = ob;

	return parameters;
}