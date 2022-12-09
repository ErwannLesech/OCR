#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "neuronal_network_functions.h"
#include "matrix.h"


void free_multiple_matrices(multiple_matrices matrices)
{
	if(matrices.a != NULL)
		free_matrix(matrices.a);
	if(matrices.b != NULL)
		free_matrix(matrices.b);
	if(matrices.c != NULL)
		free_matrix(matrices.c);
	if(matrices.d != NULL)
		free_matrix(matrices.d);
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


double softmax(double x, double sum)
{
	return exp(x) / sum;
}

double softmax_derivative(double x)
{
	return x * (1 - x);
}

void shuffle(matrix *inputs, matrix *exp_outputs)
{
	srand(time(NULL));
	for (size_t i = 0; i < inputs->cols; i++)
	{
		size_t r = rand() % inputs->cols;
		printf("r = %zu i = %zu \n", r, i);

		for (size_t j = 0; j < inputs->rows; j++)
		{
			double tmp = get_value(inputs, j, i);
			insert_value(inputs, j, i, get_value(inputs, j, r));
			insert_value(inputs, j, r, tmp);
		}
		for (size_t k = 0; k < exp_outputs->rows; k++)
		{
			double tmp = get_value(exp_outputs, k, 0);
			insert_value(exp_outputs, k, 0, get_value(exp_outputs, k, r));
			insert_value(exp_outputs, k, r, tmp);
		}
	}
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
	return init_matrix(784, 1, 0);
}


multiple_matrices init_input_matrix(size_t nbInputs)
{
	multiple_matrices matrices;
	matrix *input = init_matrix(784, nbInputs, 0);
	matrix *exp_output = init_matrix(1, nbInputs, 0);
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
		/*printf("%s\n", path);*/
		printf("%c\n", path[38]);
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
	matrices.a = input;
	matrices.b = exp_output;
	return matrices;
}


multiple_matrices initialization(int input_neurons,
	int hidden_neurons1, int hidden_neurons2, int output_neurons)
{
	matrix *w1 = init_rand_matrix(hidden_neurons1, input_neurons);
	matrix *b1 = init_rand_matrix(hidden_neurons1, 1);
	matrix *w2 = init_rand_matrix(hidden_neurons2, hidden_neurons1);
	matrix *b2 = init_rand_matrix(hidden_neurons2, 1);
	matrix *w3 = init_rand_matrix(output_neurons, hidden_neurons2);
	matrix *b3 = init_rand_matrix(output_neurons, 1);

	multiple_matrices neurons;
	neurons.a = w1;
	neurons.b = b1;
	neurons.c = w2;
	neurons.d = b2;
	neurons.e = w3;
	neurons.f = b3;

	return neurons;
}


multiple_matrices forward_propagation(multiple_matrices *parameters,
	matrix *inputs)
{
	matrix *w1 = parameters->a;
	matrix *b1 = parameters->b;
	matrix *w2 = parameters->c;
	matrix *b2 = parameters->d;
	matrix *w3 = parameters->e;
	matrix *b3 = parameters->f;
	
	// HIDDEN LAYER1

	matrix *Z1 = dot_matrix(w1, inputs);
	Z1 = add_matrix_bias(Z1, b1);

	matrix *A1 = copy_matrix(Z1);
	A1 = sigmoid_matrix(A1);
		
	// HIDDEN LAYER2

	matrix *Z2 = dot_matrix(w2, A1);
	Z2 = add_matrix_bias(Z2, b2);

	matrix *A2 = copy_matrix(Z2);
	A2 = sigmoid_matrix(A2);

	// OUTPUT LAYER

	matrix *Z3 = dot_matrix(w3, A2);
	Z3 = add_matrix_bias(Z3, b3);

	matrix *A3 = copy_matrix(Z3);
	A3 = softmax_matrix(A3);

	print_matrix(A3);

	printf("forward_propagation done\n");

	// Return values
	
	multiple_matrices results;
	results.a = Z1;
	results.b = A1;
	results.c = Z2;
	results.d = A2;
	results.e = Z3;
	results.f = A3;

	return results;
}


matrix *exp_output_init(matrix *exp_output)
{
	matrix *one_hot_Y = init_matrix(10, exp_output->cols, 0);

	for (size_t i = 0; i < exp_output->cols; i++)
	{
		size_t value = (int)(get_value(exp_output, 0, i));
		insert_value(one_hot_Y, value, i, 1);
	}

	return one_hot_Y;
}

// Backpropagation
multiple_matrices back_propagation(matrix *exp_outputs, matrix *inputs,
	multiple_matrices *parameters, multiple_matrices *forward_prop)
{
	matrix *Z1 = forward_prop->a;
	matrix *A1 = forward_prop->b;
	matrix *Z2 = forward_prop->c;
	matrix *A2 = forward_prop->d;
	matrix *Z3 = forward_prop->e;
	matrix *A3 = forward_prop->f;
	double m = exp_outputs->cols;

	matrix *b3 = parameters->f;
	matrix *w3 = parameters->e;
	matrix *b2 = parameters->d;
	matrix *w2 = parameters->c;
	matrix *b1 = parameters->b;
	matrix *w1 = parameters->a;

	// OUTPUT LAYER

	matrix *dZ3 = substract_matrix(A3, exp_outputs);
	matrix *A2_t = transpose_matrix(A2);
	matrix *dW3 = dot_matrix(dZ3, A2_t);
	dW3 = multiply_matrix(dW3, (1/m));

	double dB3_value = 0;
	double sum = sum_matrix(dZ3);
	dB3_value = sum/m;
	matrix *dB3 = init_matrix(dZ3->rows, 1, dB3_value);

	// HIDDEN LAYER2

	matrix *w3_t = transpose_matrix(w3);
	matrix *dZ2 = dot_matrix(w3_t, dZ3);
	dZ2 = d_sigmoid_matrix(dZ2, Z2);

	matrix *A1_t = transpose_matrix(A1);
	matrix *dW2 = dot_matrix(dZ2, A1_t);
	dW2 = multiply_matrix(dW2, (1/m));

	double dB2_value = 0;
	sum = sum_matrix(dZ2);
	dB2_value = sum/m;
	matrix *dB2 = init_matrix(dZ2->rows, 1, dB2_value);

	// HIDDEN LAYER1

	matrix *w2_t = transpose_matrix(w2);
	matrix *dZ1 = dot_matrix(w2_t, dZ2);
	dZ1 = d_sigmoid_matrix(dZ1, Z1);

	matrix *A0_t = transpose_matrix(inputs);
	matrix *dW1 = dot_matrix(dZ1, A0_t);
	dW1 = multiply_matrix(dW1, (1/m));

	double dB1_value = 0;
	sum = sum_matrix(dZ1);
	dB1_value = sum/m;
	matrix *dB1 = init_matrix(dZ1->rows, 1, dB1_value);

	// Free useless memory

	free_matrix(A2_t);
	free_matrix(A1_t);
	free_matrix(w3_t);
	free_matrix(w2_t);
	free_matrix(A0_t);

	printf("back_propagation done\n");

	// Return values

	multiple_matrices back_prop;
	back_prop.a = dW3;
	back_prop.b = dB3;
	back_prop.c = dW2;
	back_prop.d = dB2;
	back_prop.e = dW1;
	back_prop.f = dB1;

	return back_prop;
}


multiple_matrices *upgrade_parameters(matrix *inputs, multiple_matrices *parameters,
	multiple_matrices *forward_prop, multiple_matrices *back_prop, double lr)
{
	matrix *w1 = parameters->a;
	matrix *b1 = parameters->b;
	matrix *w2 = parameters->c;
	matrix *b2 = parameters->d;
	matrix *w3 = parameters->e;
	matrix *b3 = parameters->f;

	matrix *dW3 = back_prop->a;
	matrix *dB3 = back_prop->b;
	matrix *dW2 = back_prop->c;
	matrix *dB2 = back_prop->d;
	matrix *dW1 = back_prop->e;
	matrix *dB1 = back_prop->f;

	matrix *dw3 = multiply_matrix(dW3, lr);
	w3 = substract_matrix(w3, dw3);

	matrix *db3 = multiply_matrix(dB3, lr);
	b3 = substract_matrix(b3, db3);

	matrix *dw2 = multiply_matrix(dW2, lr);
	w2 = substract_matrix(w2, dw2);

	matrix *db2 = multiply_matrix(dB2, lr);
	b2 = substract_matrix(b2, db2);

	matrix *dw1 = multiply_matrix(dW1, lr);
	w1 = substract_matrix(w1, dw1);

	matrix *db1 = multiply_matrix(dB1, lr);
	b1 = substract_matrix(b1, db1);

	// Free useless memory

	free_matrix(dw3);
	free_matrix(db3);
	free_matrix(dw2);
	free_matrix(db2);
	free_matrix(dw1);
	free_matrix(db1);

	printf("upgrade_parameters done\n");

	// Return values

	parameters->a = w1;
	parameters->b = b1;
	parameters->c = w2;
	parameters->d = b2;
	parameters->e = w3;
	parameters->f = b3;

	return parameters;
}