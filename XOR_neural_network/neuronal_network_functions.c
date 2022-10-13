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


multiple_result initialization(int input_neurons, 
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
	hidden_propagation = multiply_matrix(inputs, &hw);
	add_matrix(&hidden_propagation, &hb);
	sigmoid_matrix(&hidden_propagation);

	// OUTPUT LAYER

	matrix output_propagation;
	output_propagation = multiply_matrix(&hidden_propagation, &ow);
	add_matrix(&hidden_propagation, &ob);
	sigmoid_matrix(&output_propagation);

	// Return values

	multiple_result results;
	results.a = hidden_propagation;
	results.b = output_propagation;

	return results;
}

multiple_result back_propagation(matrix *inputs, matrix *exp_outputs, 
multiple_result *parameters, multiple_result *forward_prop)
{
	matrix hidden_prop = forward_prop->a;
    matrix output_prop = forward_prop->b;
	matrix ow = parameters->c;

	matrix dZ2;
	dZ2 = substract_matrix(&output_prop, exp_outputs);

	matrix hidden_prop_t;
	hidden_prop_t = transpose_matrix(&hidden_prop);

	matrix dW2;
	dW2 = multiply_matrix(&hidden_prop_t, &dZ2);
	matrix dB2;
	dB2 = add_col_matrix(&dZ2);

	matrix dZ1;
	matrix ow_transposed;
	ow_transposed = transpose_matrix(&ow);
	dZ1 = multiply_matrix(&dZ2, &ow_transposed);
	dZ1 = multiply_matrix(&dZ1, &hidden_prop_t);

	matrix one_mat;
	init_matrix(&one_mat, 4, 2, 1);
	one_mat = substract_matrix(&one_mat, &hidden_prop);
	matrix one_mat_t;
	one_mat_t = transpose_matrix(&one_mat);
	dZ1 = multiply_matrix(&one_mat_t, &dZ1);
	
	matrix dW1;
	dW1 = multiply_matrix(inputs, &dZ1);
	
	matrix dB1;
	dB1 = add_col_matrix(&dZ1);

	multiple_result back_prop;
	back_prop.a = dW1;
	back_prop.b = dB1;
	back_prop.c = dW2;
	back_prop.d = dB2;

	return back_prop;
}

multiple_result *upgrade_parameters(multiple_result *parameters, 
multiple_result *back_prop, double lr)
{
	matrix hw = parameters->a;
	matrix hb = parameters->b;
	matrix ow = parameters->c;
	matrix ob = parameters->d;

	matrix dW1 = back_prop->a;
	matrix dB1 = back_prop->b;
	matrix dW2 = back_prop->c;
	matrix dB2 = back_prop->d;

	matrix undot_w1;
	undot_w1 = undot_matrix(&dW1, lr);
	matrix undot_w2;
	undot_w2 = undot_matrix(&dW2, lr);
	matrix undot_b1;
	undot_b1 = undot_matrix(&dB1, lr);
	matrix undot_b2;
	undot_b2 = undot_matrix(&dB2, lr);

	print_matrix(&hw);
	print_matrix(&undot_b1);
	
	hw = substract_matrix(&hw, &undot_w1);
	hb = substract_matrix(&hb, &undot_b1);
	ow = substract_matrix(&ow, &undot_w2);
	ob = substract_matrix(&ob, &undot_b2);

	parameters->a = hw;
	parameters->b = hb;
	parameters->c = ow;
	parameters->d = ob;

	return parameters;
}

int predict(matrix *inputs, multiple_result *parameters)
{
	multiple_result forward_prop;
	forward_prop = forward_propagation(parameters, inputs);
	matrix A2 = forward_prop.d;
	return A2.data[0] >= 0.5;
}


void save_parameters(multiple_result *parameters, char path[])
{
	FILE *file = fopen(path, "w");

	matrix hw = parameters->a;
	matrix hb = parameters->b;
	matrix ow = parameters->c;
	matrix ob = parameters->d;

	int rows = hw.rows ;
	int cols = hw.cols;

	fprintf(file, "hw dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);

	for (int i = 0; i < rows; i++)
    {
		fprintf(file, "[");
        for (int j = 0; j < cols; j++)
        {
            fprintf(file," %f ", get_value(&hw, i, j));
        }
		fprintf(file, "]\n");
    }

	fprintf(file, "\n");

	rows = hb.rows ;
	cols = hb.cols;

	fprintf(file, "hb dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);

	for (int i = 0; i < rows; i++)
    {
		fprintf(file, "[");
        for (int j = 0; j < cols; j++)
        {
            fprintf(file," %f ", get_value(&hb, i, j));
        }
		fprintf(file, "]\n");
    }

	fprintf(file, "\n");

	rows = ow.rows ;
	cols = ow.cols;

	fprintf(file, "ow dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);

	for (int i = 0; i < rows; i++)
    {
		fprintf(file, "[");
        for (int j = 0; j < cols; j++)
        {
            fprintf(file," %f ", get_value(&ow, i, j));
        }
		fprintf(file, "]\n");
    }

	fprintf(file, "\n");

	rows = ob.rows ;
	cols = ob.cols;

	fprintf(file, "ob dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);

	for (int i = 0; i < rows; i++)
    {
		fprintf(file, "[");
        for (int j = 0; j < cols; j++)
        {
            fprintf(file," %f ", get_value(&ob, i, j));
        }
		fprintf(file, "]\n");
    }
}

















