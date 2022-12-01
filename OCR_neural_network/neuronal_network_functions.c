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

double softmax(double x, size_t index, matrix *m)
{
	double exp_sum = 0;
	
	for(size_t i = 0; i < 10; i++)
	{
		exp_sum += exp(get_value(&m, i, 0));
	}
	if (exp_sum == 0)
	{
		exp_sum = 0.0001;
	}
	
	return exp(get_value(&m, index, 0)) / exp_sum;
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
		int random = rand() % 10;
		int random2 = rand() % 10;
		char path[44] = "./OCR_neural_network/dataset/training/";
		path[38] = random + 48;
		path[39] = random2 + 48;
		path[40] = '.';
		path[41] = 'p';
		path[42] = 'n';
		path[43] = 'g';
		path[44] = '\0';
		insert_value(exp_output, 0, n, (double)path[38] - 48);

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
			insert_value(input, i, n, value);
		}
		SDL_FreeSurface(new_surface);
		SDL_UnlockSurface(new_surface);
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
	relu_matrix(&A1);
		
	
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