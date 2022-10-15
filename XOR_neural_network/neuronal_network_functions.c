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
	hidden_propagation = dot_matrix(inputs, &hw);
	add_matrix(&hidden_propagation, &hb);
	sigmoid_matrix(&hidden_propagation);

	// OUTPUT LAYER

	matrix output_propagation;
	output_propagation = dot_matrix(&hidden_propagation, &ow);
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

	// OUTPUT TO HIDDEN

	matrix error;
	error = substract_matrix(&output_prop, exp_outputs);
	
	matrix douto_dino;
	douto_dino = deriv_sigmoid_matrix(&output_prop);

	matrix douto_dino_t;
	douto_dino_t = transpose_matrix(&douto_dino);

	matrix derr_dino;
	derr_dino = multiply_matrix(&error, &douto_dino_t);
	
	matrix ow_t;
	ow_t = transpose_matrix(&ow);

	matrix error_hidden_layer;
	error_hidden_layer = dot_matrix(&derr_dino, &ow_t);

	
	// HIDDEN TO INPUT

	matrix douth_dinh;
	douth_dinh = deriv_sigmoid_matrix(&hidden_prop);
	print_matrix(&douth_dinh);
	
	matrix douth_dinh_t;
	douth_dinh_t = transpose_matrix(&douth_dinh);
	print_matrix(&douth_dinh_t);
	
	matrix derr_dinh;
	derr_dinh = multiply_matrix(&error_hidden_layer, &douth_dinh_t);
	printf("output passed\n");
	matrix input_t;
	input_t = transpose_matrix(inputs);
	
	
	matrix d_hidden_layer;
	d_hidden_layer = multiply_matrix(&input_t, &derr_dinh);

	matrix out_hidden_t;
	out_hidden_t = transpose_matrix(&hidden_prop);

	matrix d_output_layer;
	d_output_layer = multiply_matrix(&out_hidden_t, &derr_dino);
	

	// RETURN RESULT

	multiple_result back_prop;
	back_prop.a = d_output_layer;
	back_prop.b = derr_dino;
	back_prop.c = d_hidden_layer;
	back_prop.d = derr_dinh;

	return back_prop;
}

multiple_result *upgrade_parameters(multiple_result *parameters, 
multiple_result *back_prop, double lr)
{
	matrix hw = parameters->a;
	matrix hb = parameters->b;
	matrix ow = parameters->c;
	matrix ob = parameters->d;

	matrix d_output_layer = back_prop->a;
	matrix derr_dino = back_prop->b;
	matrix d_hidden_layer = back_prop->c;
	matrix derr_dinh = back_prop->d;

	matrix d_ol;
	d_ol =  multiply_matrix_val(&d_output_layer, lr);
	ow = substract_matrix(&ow, &d_ol);

	matrix d_output_bias;
	d_output_bias = add_row_matrix(&derr_dino);
	d_output_bias = multiply_matrix_val(&d_output_bias, lr);
	ob = substract_matrix(&ob, &d_output_bias);

	matrix d_hl;
	d_hl =  multiply_matrix_val(&d_hidden_layer, lr);
	hw = substract_matrix(&hw, &d_hl);

	matrix d_hidden_bias;
	d_hidden_bias = add_row_matrix(&derr_dinh);
	d_hidden_bias = multiply_matrix_val(&d_hidden_bias, lr);
	hb = substract_matrix(&hb, &d_hidden_bias);

	parameters->a = hw;
	parameters->b = hb;
	parameters->c = ow;
	parameters->d = ob;

	return parameters;
}

double predict_xor(multiple_result *parameters, double input_one, double input_two)
{
	matrix inputs;
	init_matrix(&inputs, 1, 2, 0);
	insert_value(&inputs, 0, 0, input_one);
	insert_value(&inputs, 0, 1, input_two);

	matrix hw = parameters->a;
	matrix hb = parameters->b;
	matrix ow = parameters->c;
	matrix ob = parameters->d;

	// HIDDEN LAYER

	matrix hidden_propagation;
	hidden_propagation = multiply_matrix(&inputs, &hw);
	add_matrix(&hidden_propagation, &hb);
	sigmoid_matrix(&hidden_propagation);

	// OUTPUT LAYER

	matrix output_propagation;
	output_propagation = multiply_matrix(&hidden_propagation, &ow);
	add_matrix(&hidden_propagation, &ob);
	sigmoid_matrix(&output_propagation);

	// Return values
	double result = get_value(&output_propagation, 0, 0);

	free_matrix(&inputs);
	free_matrix(&hidden_propagation);
	free_matrix(&output_propagation);

	return result;
}


double log_loss(double exp_output, double pred_output)
{
	return 0.5 * pow((exp_output - pred_output), 2);
}

double xor_accuracy(multiple_result *parameters, int nb_tests)
{
	int valid_pred;
	double dError;
	for(int i = 0; i < nb_tests; i++)
	{
		matrix inputs;
		init_rand_matrix(&inputs, 1, 2);

		double input_one;
		double input_two;

		if(inputs.data[0] < 0.5)
		{
			input_one = 0;
		}
		else
		{
			input_one = 1;
		}

		if(inputs.data[1] < 0.5)
		{
			input_two = 0;
		}
		else
		{
			input_two = 1;
		}

		double pred_output = predict_xor(parameters, input_one, input_two);

		int exp_output;

		if ((input_one < 0.5 && input_two < 0.5) || (input_one > 0.5 && input_two > 0.5))
		{
			exp_output = 0;
		}
		else
		{
			exp_output = 1;
		}

		dError += log_loss(exp_output, pred_output);

		if(exp_output == (int) pred_output)
		{
			valid_pred++;
		}
	}

	printf("XOR correct pred = %i sur %i tests.\n", valid_pred, nb_tests);
	printf("Average error per test: %f\n", dError / nb_tests);

	return (valid_pred / nb_tests);
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

	fprintf(file, "\n");
}

















