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
	return x * (1 - x);
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
	init_rand_matrix(&ow, 1, hidden_neurons);
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
	hidden_propagation = dot_matrix(&hw, inputs);

	add_matrix(&hidden_propagation, &hb);
	sigmoid_matrix(&hidden_propagation);

	// OUTPUT LAYER
	matrix output_propagation;
	output_propagation = dot_matrix(&ow, &hidden_propagation);

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
	dW2 = dot_matrix(&dZ2, &hidden_prop_t);

	matrix dB2;
	dB2 = add_col_matrix(&dZ2);

	matrix dZ1;

	matrix ow_transposed;
	ow_transposed = transpose_matrix(&ow);

	dZ1 = dot_matrix(&ow_transposed, &dZ2);
	d_sigmoid_matrix(&dZ1);

	matrix inputs_t;
	inputs_t = transpose_matrix(inputs);

	matrix dW1;
	dW1 = dot_matrix(&dZ1, &inputs_t);

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
	undot_w1 = multiply_matrix(&dW1, lr);
	matrix undot_w2;
	undot_w2 = multiply_matrix(&dW2, lr);
	matrix undot_b1;
	undot_b1 = multiply_matrix(&dB1, lr);
	matrix undot_b2;
	undot_b2 = multiply_matrix(&dB2, lr);

	/*print_matrix(&hw);
	print_matrix(&undot_b1);*/

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

double predict_xor(multiple_result *parameters, double input_one, 
	double input_two)
{
	matrix inputs;
	init_matrix(&inputs, 2, 4, 0);
	insert_value(&inputs, 0, 0, input_one);
	insert_value(&inputs, 0, 1, input_two);

	matrix hw = parameters->a;
	matrix hb = parameters->b;
	matrix ow = parameters->c;
	matrix ob = parameters->d;

	matrix hidden_propagation;
	hidden_propagation = dot_matrix(&hw, &inputs);

	add_matrix(&hidden_propagation, &hb);
	sigmoid_matrix(&hidden_propagation);

	// OUTPUT LAYER
	matrix output_propagation;
	output_propagation = dot_matrix(&ow, &hidden_propagation);

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

	int rows = hw.rows;
	int cols = hw.cols;

	fprintf(file, "hw dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);

	for (int i = 0; i < rows; i++)
	{
		fprintf(file, "[");
		for (int j = 0; j < cols; j++)
		{
			fprintf(file, " %f ", get_value(&hw, i, j));
		}
		fprintf(file, "]\n");
	}

	fprintf(file, "\n");

	rows = hb.rows;
	cols = hb.cols;

	fprintf(file, "hb dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);

	for (int i = 0; i < rows; i++)
	{
		fprintf(file, "[");
		for (int j = 0; j < cols; j++)
		{
			fprintf(file, " %f ", get_value(&hb, i, j));
		}
		fprintf(file, "]\n");
	}

	fprintf(file, "\n");

	rows = ow.rows;
	cols = ow.cols;

	fprintf(file, "ow dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);

	for (int i = 0; i < rows; i++)
	{
		fprintf(file, "[");
		for (int j = 0; j < cols; j++)
		{
			fprintf(file, " %f ", get_value(&ow, i, j));
		}
		fprintf(file, "]\n");
	}

	fprintf(file, "\n");

	rows = ob.rows;
	cols = ob.cols;

	fprintf(file, "ob dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);

	for (int i = 0; i < rows; i++)
	{
		fprintf(file, "[");
		for (int j = 0; j < cols; j++)
		{
			fprintf(file, " %f ", get_value(&ob, i, j));
		}
		fprintf(file, "]\n");
	}
}
