#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "neuronal_network_functions.h"
#include "matrix.h"


void free_multiple_matrices(multiple_matrices *matrices)
{
	free_matrix(matrices->a);
	free_matrix(matrices->b);
	free_matrix(matrices->c);
	free_matrix(matrices->d);
}

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


matrix *init_input_matrix_test(char *path)
{
	matrix *input = init_matrix(784, 1, 0);
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
		if ((r+b+g)/3 >= 127)
		{
			value = 1;
		}
		else
		{
			value = 0;
		}
		//value = (double)((r+b+g)/(double)3)/(double)255;
		insert_value(input, i, 0, value);
	}
	SDL_FreeSurface(new_surface);
	SDL_UnlockSurface(new_surface);
	return input;
}


multiple_matrices init_input_matrix(size_t nbInputs)
{
	multiple_matrices matrices;
	matrix *input = init_matrix(784, nbInputs, 0);
	matrix *exp_output = init_matrix(10, nbInputs, 0);
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
		/*printf("%s\n", path);
		printf("%lu\n", n);*/
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
			if ((r+b+g)/3 >= 127)
			{
				value = 1;
			}
			else
			{
				value = 0;
			}
			//value = (double)((r+b+g)/(double)3)/(double)255;
			insert_value(input, i, n, value);
		}
		SDL_UnlockSurface(new_surface);
		SDL_FreeSurface(new_surface);
	}
	return matrices;
}


multiple_matrices initialization(int input_neurons,
	int hidden_neurons, int output_neurons)
{
	matrix *hw = init_rand_matrix(hidden_neurons, input_neurons);
	matrix *hb = init_rand_matrix(hidden_neurons, 1);
	matrix *ow = init_rand_matrix(output_neurons, hidden_neurons);
	matrix *ob = init_rand_matrix(output_neurons, 1);

	multiple_matrices neurons;
	neurons.a = hw;
	neurons.b = hb;
	neurons.c = ow;
	neurons.d = ob;

	return neurons;
}


multiple_matrices forward_propagation(multiple_matrices *parameters,
	matrix *inputs)
{
	matrix *hw = parameters->a;
	matrix *hb = parameters->b;
	matrix *ow = parameters->c;
	matrix *ob = parameters->d;
	
	// HIDDEN LAYER

	matrix *Z1 = dot_matrix(hw, inputs);
	Z1 = add_matrix(Z1, hb);


	matrix *A1 = copy_matrix(Z1);
	A1 = relu_matrix(A1);
		
	// OUTPUT LAYER
	matrix *Z2 = dot_matrix(ow, A1);
	Z2 = add_matrix(Z2, ob);

	matrix *A2 = copy_matrix(Z2);
	A2 = softmax_matrix(A2);
	
	// Return values
	multiple_matrices results;
	results.a = Z1;
	results.b = A1;
	results.c = Z2;

	return results;
}


matrix *exp_output_init(matrix *exp_output)
{
	matrix *one_hot_Y = init_matrix(9, exp_output->cols, 0);

	for (size_t i = 0; i < exp_output->cols; i++)
	{
		size_t value = (int)(get_value(exp_output, 0, i));
		insert_value(one_hot_Y, value - 1, i, 1);
	}

	return one_hot_Y;
}

// Backpropagation
multiple_matrices back_propagation(matrix *exp_outputs, matrix *inputs,
	multiple_matrices *parameters, multiple_matrices *forward_prop)
{
	matrix *Z1 = forward_prop->a;
	matrix *A1 = forward_prop->b;
	matrix *A2 = forward_prop->c;
	matrix *ow = parameters->c;
	double m = exp_outputs->cols;

	matrix *dZ2 = substract_matrix(A2, exp_outputs);
	
	matrix *A1_t = transpose_matrix(A1);

	matrix *dW2 = dot_matrix(dZ2, A1_t);
	dW2 = multiply_matrix(dW2, (1/m));

	double dB2_value = 0;
	double sum = sum_matrix(dZ2);
	dB2_value = sum/m;
	matrix *dB2 = init_matrix(dZ2->rows, dZ2->cols, dB2_value);

	matrix *ow_t = transpose_matrix(ow);
	matrix *dZ1 =dot_matrix(ow_t, dZ2);
	dZ1 = d_relu_matrix(dZ1, Z1);
	
	
	matrix *A0_t = transpose_matrix(inputs);
	matrix *dW1 = dot_matrix(dZ1, A0_t);
	dW1 = multiply_matrix(dW1, (1/m));

	double dB1_value = 0;
	sum = sum_matrix(dZ1);
	dB1_value = sum/m;
	matrix *dB1 = init_matrix(dZ1->rows, dZ1->cols, dB1_value);

	multiple_matrices back_prop;
	back_prop.a = dW2;
	back_prop.b = dB2;
	back_prop.c = dW1;
	back_prop.d = dB1;

	return back_prop;
}


multiple_matrices *upgrade_parameters(matrix *inputs, multiple_matrices *parameters,
	multiple_matrices *forward_prop, multiple_matrices *back_prop, double lr)
{
	matrix *hw = parameters->a;
	matrix *hb = parameters->b;
	matrix *ow = parameters->c;
	matrix *ob = parameters->d;

	matrix *dW2 = back_prop->a;
	matrix *dB2 = back_prop->b;
	matrix *dW1 = back_prop->c;
	matrix *dB1 = back_prop->d;
	
	matrix *dOW = multiply_matrix(dW2, lr);
	ow = substract_matrix(ow, dOW);
	
	matrix *dOB = multiply_matrix(&dB2, lr);
	ob = substract_matrix(ob, dOB);

	matrix *dHW = multiply_matrix(&dW1, lr);
	hw = substract_matrix(hw, dHW);

	matrix *dHB = multiply_matrix(&dB1, lr);
	hb = substract_matrix(hb, dHB);

	parameters->a = hw;
	parameters->b = hb;
	parameters->c = ow;
	parameters->d = ob;

	return parameters;
}