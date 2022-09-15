#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "ML_functions.h"

// Input datasets

const unsigned int inputs[4][2] = 
{
	{0, 0}, 
	{0, 1}, 
	{1, 0}, 
	{1, 1}
};

// Output datasets expected

const unsigned int expected_outputs[4][1] = 
{
	{0},
	{1}, 
	{1}, 
	{0}
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


//float[][hidden_neurons] hidden_bias = ((rand() % 10000) / 10000.0);

//float[][hidden_neurons] output_weights = ((rand() % 10000) / 10000.0);
//float[][output_neurons] output_bias = ((rand() % 10000) / 10000.0);

void test()
{
	srand( time( NULL ) );
	float hidden_weights[][2] =
	{	
        	{((rand() % 10000) / 10000.0), ((rand() % 10000) / 10000.0)},
        	{((rand() % 10000) / 10000.0), ((rand() % 10000) / 10000.0)}
	};

	print_matrix(hidden_weights, 2);
}
