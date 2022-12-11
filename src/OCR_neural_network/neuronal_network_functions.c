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

		for (size_t j = 0; j < inputs->rows; j++)
		{
			double tmp = get_value(inputs, j, i);
			insert_value(inputs, j, i, get_value(inputs, j, r));
			insert_value(inputs, j, r, tmp);
		}
		/*for (size_t k = 0; k < exp_outputs->rows; k++)
		{
			double tmp = get_value(exp_outputs, k, 0);
			insert_value(exp_outputs, k, 0, get_value(exp_outputs, k, r));
			insert_value(exp_outputs, k, r, tmp);
		}*/
		double tmp = get_value(exp_outputs, 0, i);
		insert_value(exp_outputs, 0, i, get_value(exp_outputs, 0, r));
		insert_value(exp_outputs, 0, r, tmp);
	}
}


matrix *init_input_matrix_predict(char *path)
{
	matrix *input = init_matrix(784, 1, 0);
	SDL_Surface* surface = IMG_Load(path);
	
	SDL_Surface* new_surface = SDL_ConvertSurfaceFormat(surface, 
		SDL_PIXELFORMAT_RGB888, 0);
	Uint32* pixels = new_surface->pixels;
	SDL_PixelFormat* format = new_surface->format;
	SDL_LockSurface(new_surface);

	int rate = 0;
	
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
			rate++;
		}
		//value = (double)((r+b+g)/(double)3)/(double)255;
		insert_value(input, i, 0, value);
	}
	SDL_FreeSurface(new_surface);
	SDL_UnlockSurface(new_surface);

	if(rate < 10)
		return NULL;
	return input;
}

matrix *init_input_matrix_accuracy(char *path)
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
	matrix *exp_output = init_matrix(1, nbInputs, 0);
	srand(time(NULL));
	for (size_t n = 0; n < nbInputs; n++)
	{
		int number = rand() % 9 + 1;
		int random = rand() % 7;
		//int random2 = rand() % 10;
		char path[45] = "./OCR_neural_network/dataset/training/";
		path[38] = number + 48;
		path[39] = '/';
		path[40] = random + 48;
		//path[41] = random2 + 48;
		path[41] = '.';
		path[42] = 'p';
		path[43] = 'n';
		path[44] = 'g';
		path[45] = '\0';
		/*printf("%s\n", path);*/
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
			//value = 0.3*r + 0.59*g+0.11*b;
			insert_value(input, i, n, value);
		}
		SDL_UnlockSurface(new_surface);
		SDL_FreeSurface(new_surface);
	}
	matrices.a = input;
	matrices.b = exp_output;
	return matrices;
}

multiple_matrices init_input_matrix_mnist(size_t nbInputs)
{
	multiple_matrices matrices;
	matrix *input = init_matrix(784, nbInputs, 0);
	matrix *exp_output = init_matrix(1, nbInputs, 0);
	srand(time(NULL));
	for (size_t n = 0; n < nbInputs; n++)
	{
		int number = rand() % 9 + 1;
		// rand number 48 to 122
		int random = rand() % 75 + 48;
		char path[46] = "./OCR_neural_network/dataset/train/";
		path[35] = number + 48;
		path[36] = '/';
		path[37] = (char)random;
		path[38] = '\0';
		/*printf("%s\n", path);*/
		insert_value(exp_output, 0, n, (double)path[35] - 48);

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
			//value = 0.3*r + 0.59*g+0.11*b;
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
	int hidden_neurons, int output_neurons)
{
	matrix *w1 = init_rand_matrix(hidden_neurons, input_neurons);
	matrix *b1 = init_rand_matrix(hidden_neurons, 1);
	matrix *w2 = init_rand_matrix(output_neurons, hidden_neurons);
	matrix *b2 = init_rand_matrix(output_neurons, 1);

	multiple_matrices neurons;
	neurons.a = w1;
	neurons.b = b1;
	neurons.c = w2;
	neurons.d = b2;

	return neurons;
}


multiple_matrices forward_propagation(multiple_matrices *parameters,
	matrix *inputs)
{
	matrix *w1 = parameters->a;
	matrix *b1 = parameters->b;
	matrix *w2 = parameters->c;
	matrix *b2 = parameters->d;
	
	// HIDDEN LAYER

	matrix *Z1 = dot_matrix(w1, inputs);
	Z1 = add_matrix(Z1, b1);

	matrix *A1 = copy_matrix(Z1);
	A1 = relu_matrix(A1);

	// OUTPUT LAYER

	matrix *Z2 = dot_matrix(w2, A1);
	Z2 = add_matrix(Z2, b2);

	
	matrix *A2 = copy_matrix(Z2);
	A2 = softmax_matrix(A2);

	//printf("forward_propagation done\n");

	// Return values
	
	multiple_matrices results;
	results.a = Z1;
	results.b = A1;
	results.c = Z2;
	results.d = A2;

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
	double m = exp_outputs->cols;

	matrix *b3 = parameters->f;
	matrix *w3 = parameters->e;
	matrix *b2 = parameters->d;
	matrix *w2 = parameters->c;

	// OUTPUT LAYER

	matrix *dZ2 = substract_matrix(A2, exp_outputs);
	//dZ2 = d_sigmoid(dZ2, Z2);

	matrix *A1_t = transpose_matrix(A1);
	matrix *dW2 = dot_matrix(dZ2, A1_t);
	dW2 = multiply_matrix(dW2, (1/m));

	double dB2_value = sum_matrix(dZ2);
	dB2_value /= m;
	matrix *dB2 = init_matrix(dZ2->rows, 1, dB2_value);

	// HIDDEN LAYER

	matrix *w2_t = transpose_matrix(w2);
	matrix *dZ1 = dot_matrix(w2_t, dZ2);
	dZ1 = d_relu_matrix(dZ1, Z1);

	matrix *A0_t = transpose_matrix(inputs);
	matrix *dW1 = dot_matrix(dZ1, A0_t);
	dW1 = multiply_matrix(dW1, (1/m));

	double dB1_value = sum_matrix(dZ1);
	dB1_value /= m;
	matrix *dB1 = init_matrix(dZ1->rows, 1, dB1_value);

	// Free useless memory

	free_matrix(A1_t);
	free_matrix(w2_t);
	free_matrix(A0_t);

	//printf("back_propagation done\n");

	// Return values

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
	matrix *w1 = parameters->a;
	matrix *b1 = parameters->b;
	matrix *w2 = parameters->c;
	matrix *b2 = parameters->d;

	matrix *dW2 = back_prop->a;
	matrix *dB2 = back_prop->b;
	matrix *dW1 = back_prop->c;
	matrix *dB1 = back_prop->d;

	matrix *dw2 = multiply_matrix(dW2, lr);
	w2 = substract_matrix(w2, dw2);

	matrix *db2 = multiply_matrix(dB2, lr);
	b2 = substract_matrix(b2, db2);

	matrix *dw1 = multiply_matrix(dW1, lr);
	w1 = substract_matrix(w1, dw1);

	matrix *db1 = multiply_matrix(dB1, lr);
	b1 = substract_matrix(b1, db1);

	// Free useless memory

	free_matrix(dw2);
	free_matrix(db2);
	free_matrix(dw1);
	free_matrix(db1);

	//printf("upgrade_parameters done\n");

	// Return values

	parameters->a = w1;
	parameters->b = b1;
	parameters->c = w2;
	parameters->d = b2;

	return parameters;
}