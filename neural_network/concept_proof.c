#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ML_functions.h"

// Input datasets

void forward_propagation(double hidden_weights[], double hidden_bias[], 
		double output_weights[], double output_bias[]);

double inputs[8] = 
{
	0, 0, 
	0, 1, 
	1, 0, 
	1, 1
};

// Output datasets expected

double expected_output[4] =
{
	0,
	1, 
	1, 
	0
};

// Number of iterations

const unsigned long epochs = 10000;

// Learning rate (distance for Gradient Descent)

const float learning_rate = 0.15;

// Neural network architecture

const unsigned int input_neurons = 2;
const unsigned int hidden_neurons = 2;
const unsigned int output_neurons = 1;

// Initialization of weights and bias

// hw -> hidden_weights | hb -> hidden_bias
// ow -> output_weights | ob -> output_bias

void initialization()
{
	srand( time( NULL ) );
	
	double hw[] =
	{	
        	((rand() % 10000) / 10000.0), ((rand() % 10000) / 10000.0),
        	((rand() % 10000) / 10000.0), ((rand() % 10000) / 10000.0)
	};
	
	double hb[] =
	{
        	((rand() % 10000) / 10000.0), ((rand() % 10000) / 10000.0),
	};

	double ow[] =
	{
        	((rand() % 10000) / 10000.0), ((rand() % 10000) / 10000.0),
	};

	double ob[] =
	{
	 	((rand() % 10000) / 10000.0),
	};


	printf("Hidden weights: \n");
	print_matrix(hw, input_neurons, 2);

	printf("Hidden bias: \n");
	print_matrix(hb, 1, 2);

	printf("Output weights: \n");
	print_matrix(ow, 1, 2);

	printf("Output bias: \n");
	print_matrix(ob, output_neurons, 1);

	forward_propagation(hw, hb, ow, ob);
}

// hw -> hidden_weights | hb -> hidden_bias
// ow -> output_weights | ob -> output_bias

void forward_propagation(double hw[], double hb[], double ow[], double ob[])
{
	// HIDDEN

	double hw_propagation[8];
	multiply_matrix(hw, inputs, 2, 2, 4, hw_propagation);
       	printf("\n");
	printf("hidden_weights_propagation:\n");
	print_matrix(hw_propagation, 4, 2);
	add_matrix(hw_propagation, hb, 1, 2, hw_propagation);
	printf("\n");
	printf("hidden_weights_propagation after bias:\n");
	print_matrix(hw_propagation, 4, 2);
	double hidden_layer_output[8];
	for(size_t idx = 0; idx < 8; idx++)
	{
		hidden_layer_output[idx] = sigmoid(hw_propagation[idx]);
	}
	printf("hidden_layer_output (sigmoid):\n");
	print_matrix(hidden_layer_output, 4, 2);

	// OUTPUT
	
	double ow_propagation[4];
	multiply_matrix(hidden_layer_output, ow, 2, 4, 1, ow_propagation);
       	printf("\n");
	printf("output_weights_propagation:\n");
	print_matrix(ow_propagation, 4, 1);
	add_matrix(ow_propagation, ob, 1, 2, ow_propagation);
	printf("\n");
	printf("output_weights_propagation after bias:\n");
	print_matrix(ow_propagation, 4, 1);
	double output_layer_output[4];
	for(size_t idx = 0; idx < 4; idx++)
	{
		output_layer_output[idx] = sigmoid(ow_propagation[idx]);
	}
	printf("output_layer_output (sigmoid):\n");
	print_matrix(output_layer_output, 4, 1);

}

/*void back_propagation()
{
}*/
