#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ML_functions.h"

// Input datasets

void forward_propagation(float hidden_weights[], float hidden_bias[], 
		float output_weights[], float output_bias[]);

float inputs[8] = 
{
	0, 0, 
	0, 1, 
	1, 0, 
	1, 1
};

// Output datasets expected

float expected_output[4] =
{
	0,
	1, 
	1, 
	0
};

// Number of iterations

const unsigned long epochs = 10000;

// Learning rate (distance for Gradient Descent)

const float learning_rate = 0.9;

// Neural network architecture

const unsigned int input_neurons = 2;
const unsigned int hidden_neurons = 2;
const unsigned int output_neurons = 1;

// Initialization of weights and bias

void initialization()
{
	srand( time( NULL ) );
	
	float hidden_weights[] =
	{	
        	((rand() % 10000) / 10000.0), ((rand() % 10000) / 10000.0),
        	((rand() % 10000) / 10000.0), ((rand() % 10000) / 10000.0)
	};
	
	float hidden_bias[] =
	{
        	((rand() % 10000) / 10000.0), ((rand() % 10000) / 10000.0),
	};

	float output_weights[] =
	{
        	((rand() % 10000) / 10000.0), ((rand() % 10000) / 10000.0),
	};

	float output_bias[] =
	{
	 	((rand() % 10000) / 10000.0),
	};


	printf("Hidden weights: \n");
	print_matrix(hidden_weights, input_neurons, 2);

	printf("Hidden bias: \n");
	print_matrix(hidden_bias, 1, 2);

	printf("Output weights: \n");
	print_matrix(output_weights, 1, 2);

	printf("Output bias: \n");
	print_matrix(output_bias, output_neurons, 1);

	forward_propagation(hidden_weights, hidden_bias, output_weights, output_bias);
}

void forward_propagation(float hidden_weights[], float hidden_bias[], 
		float output_weights[], float output_bias[])
{
	// HIDDEN

	float hidden_weights_propagation[8];
	multiply_matrix(hidden_weights, inputs, 2, 2, 4, hidden_weights_propagation);
       	printf("\n");
	printf("hidden_weights_propagation:\n");
	print_matrix(hidden_weights_propagation, 4, 2);
	add_matrix(hidden_weights_propagation, 
			hidden_bias, 1, 2, hidden_weights_propagation);
	printf("\n");
	printf("hidden_weights_propagation after bias:\n");
	print_matrix(hidden_weights_propagation, 4, 2);
	float hidden_layer_output[8];
	for(size_t idx = 0; idx < 8; idx++)
	{
		hidden_layer_output[idx] = sigmoid(hidden_weights_propagation[idx]);
	}
	printf("hidden_layer_output (sigmoid):\n");
	print_matrix(hidden_layer_output, 4, 2);

	// OUTPUT
	
	float output_weights_propagation[4];
	multiply_matrix(hidden_layer_output, output_weights, 2, 4, 1, output_weights_propagation);
       	printf("\n");
	printf("output_weights_propagation:\n");
	print_matrix(output_weights_propagation, 4, 1);
	add_matrix(output_weights_propagation, 
			output_bias, 1, 2, output_weights_propagation);
	printf("\n");
	printf("output_weights_propagation after bias:\n");
	print_matrix(output_weights_propagation, 4, 1);
	float output_layer_output[4];
	for(size_t idx = 0; idx < 4; idx++)
	{
		output_layer_output[idx] = sigmoid(output_weights_propagation[idx]);
	}
	printf("output_layer_output (sigmoid):\n");
	print_matrix(output_layer_output, 4, 1);

}

/*void back_propagation()
{
}*/
