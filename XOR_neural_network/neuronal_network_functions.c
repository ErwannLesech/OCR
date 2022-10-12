#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "neuronal_network_functions.h"


double sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}


double sigmoid_derivative(double x)
{
	return sigmoid(x) *  (1 - sigmoid(x));
}


struct multiple_result initialization(int input_neurons, 
int hidden_neurons, int output_neurons)
{
	matrix hw;
	matrix hb;
	matrix ow;
	matrix ob;
	
	init_rand_matrix(&hw, input_neurons, hidden_neurons);
	init_rand_matrix(&hb, 1, hidden_neurons);
	init_rand_matrix(&ow, hidden_neurons, 1);
	init_rand_matrix(&ob, 1, output_neurons);

	struct multiple_result neurons;
	neurons.a = hw;
	neurons.b = hb;
	neurons.c = ow;
	neurons.d = ob;

	return neurons;
}

struct multiple_result forward_propagation(matrix *hw, matrix *hb, 
matrix *ow, matrix *ob, matrix *inputs)
{
	// HIDDEN LAYER

	matrix hidden_propagation;
	hidden_propagation = multiply_matrix(inputs, hw);
	add_matrix(&hidden_propagation, hb);
	sigmoid_matrix(&hidden_propagation);

	// OUTPUT LAYER

	matrix output_propagation;
	output_propagation = multiply_matrix(&hidden_propagation, ow);
	add_matrix(&hidden_propagation, ob);
	sigmoid_matrix(&output_propagation);

	// Return values

	struct multiple_result results;
	results.a = hidden_propagation;
	results.b = output_propagation;

	return results;
}





















