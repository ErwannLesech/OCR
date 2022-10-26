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
	init_matrix(&hb, 1, hidden_neurons, 0);
	init_rand_matrix(&ow, hidden_neurons, output_neurons);
	init_matrix(&ob, 1, output_neurons, 0);

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

multiple_result back_propagation(matrix *exp_outputs,
	multiple_result *parameters, multiple_result *forward_prop)
{

	matrix hidden_prop = forward_prop->a;
	matrix output_prop = forward_prop->b;
	matrix ow = parameters->c;

	matrix error;
	error = substract_matrix(exp_outputs, &output_prop);
	
	d_sigmoid_matrix(&error, &output_prop);

	matrix ow_t;
	ow_t = transpose_matrix(&ow);

	matrix error_hidden_layer;
	error_hidden_layer = dot_matrix(&error, &ow_t);
	
	d_sigmoid_matrix(&error_hidden_layer, &hidden_prop);

	multiple_result back_prop;
	back_prop.a = error;
	back_prop.b = error_hidden_layer;

	return back_prop;
}

multiple_result *upgrade_parameters(matrix inputs, multiple_result *parameters,
	multiple_result *forward_prop, multiple_result *back_prop, double lr)
{
	matrix hw = parameters->a;
	matrix hb = parameters->b;
	matrix ow = parameters->c;
	matrix ob = parameters->d;

	matrix hidden_prop = forward_prop->a;
	// matrix output_prop = forward_prop->b;

	matrix d_predicted_output = back_prop->a;
	matrix d_hidden_layer = back_prop->b;

	matrix hidden_prop_t;
	hidden_prop_t = transpose_matrix(&hidden_prop);

	matrix undot_w2;
	undot_w2 = dot_matrix(&hidden_prop_t, &d_predicted_output);
	undot_w2 = multiply_matrix(&undot_w2, lr);
	add_matrix(&ow, &undot_w2);
	matrix undot_b2;
	undot_b2 = add_row_matrix(&d_predicted_output);
	undot_b2 = multiply_matrix(&undot_b2, lr);
	add_matrix(&ob, &undot_b2);

	matrix inputs_t;
	inputs_t = transpose_matrix(&inputs);

	matrix undot_w1;
	undot_w1 = dot_matrix(&inputs_t, &d_hidden_layer);
	undot_w1 = multiply_matrix(&undot_w1, lr);
	add_matrix(&hw, &undot_w1);

	matrix undot_b1;
	undot_b1 = add_row_matrix(&d_hidden_layer);
	undot_b1 = multiply_matrix(&undot_b1, lr);
	add_matrix(&hb, &undot_b1);
	

	parameters->a = hw;
	parameters->b = hb;
	parameters->c = ow;
	parameters->d = ob;

	return parameters;
}

double predict_xor(multiple_result *parameters, matrix inputs)
{
	matrix hw = parameters->a;
	matrix hb = parameters->b;
	matrix ow = parameters->c;
	matrix ob = parameters->d;

	matrix hidden_propagation;
	hidden_propagation = dot_matrix(&inputs, &hw);
*
	add_matrix(&hidden_propagation, &hb);
	sigmoid_matrix(&hidden_propagation);
	
	// OUTPUT LAYER
	matrix output_propagation;
	output_propagation = dot_matrix(&hidden_propagation, &ow);
	add_matrix(&output_propagation, &ob);

	sigmoid_matrix(&output_propagation);

	print_matrix(&output_propagation);

	// Return values
	double result = get_value(&output_propagation, 0, 0);

	free_matrix(&inputs);
	free_matrix(&hidden_propagation);
	free_matrix(&output_propagation);

	return result;
}

/*double log_loss(double exp_output, double pred_output)
{
	return 0.5 * pow((exp_output - pred_output), 2);
}*/

double xor_accuracy(multiple_result *parameters, int nb_tests)
{
	int valid_pred;
	matrix inputs;
	init_matrix(&inputs, 1, 2, 0);
	for(int i = 0; i < nb_tests; i++)
	{
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

		insert_value(&inputs, 0, 0, input_one);
		insert_value(&inputs, 0, 1, input_two);

		print_matrix(&inputs);
		double pred_output = predict_xor(parameters, inputs);

		int exp_output;

		if ((input_one < 0.5 && input_two < 0.5) || (input_one > 0.5 && input_two > 0.5))
		{
			exp_output = 0;
		}
		else
		{
			exp_output = 1;
		}
		printf("%i\n", exp_output);
		if(exp_output == (int) pred_output)
		{
			valid_pred++;
		}
	}

	printf("XOR correct pred = %i sur %i tests.\n", valid_pred, nb_tests);

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

	/*fprintf(file, "hw dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols; j++)
		{
			fprintf(file, "%f ", get_value(&hw, i, j));
		}
		fprintf(file, "\n");
	}

	fprintf(file, "\n");

	rows = hb.rows;
	cols = hb.cols;

	/*fprintf(file, "hb dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols; j++)
		{
			fprintf(file, "%f ", get_value(&hb, i, j));
		}
		fprintf(file, "\n");
	}

	fprintf(file, "\n");

	rows = ow.rows;
	cols = ow.cols;

	/*fprintf(file, "ow dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols; j++)
		{
			fprintf(file, "%f ", get_value(&ow, i, j));
		}
		fprintf(file, "\n");
	}

	fprintf(file, "\n");

	rows = ob.rows;
	cols = ob.cols;

	/*fprintf(file, "ob dim: ");
	fprintf(file, "%d rows - ", rows);
	fprintf(file, "%d\n", cols);*/

	for (int i = 0; i < rows; i++)
	{
		//fprintf(file, "[");
		for (int j = 0; j < cols; j++)
		{
			fprintf(file, "%f ", get_value(&ob, i, j));
		}
		fprintf(file, "\n");
	}
}

multiple_result load_parameters(char path[])
{
	/*FILE *file = fopen(path, "r");

	matrix hw;
	matrix hb;
	matrix ow;
	matrix ob;	*/

	multiple_result parameters;/*


	if (NULL == file) {
        printf("file can't be opened \n");
    }
 
	int idx = 0;
	char c;
	char param[50];

    while (!feof(file))
	{
		c = fgetc(file);
		printf("%c", c);

		if (c != " " && c != "\n")
		{
			int j = 0;
				switch (idx)
				{
				case 0:
					while (c != " " && c != "\n")
					{
						c = fgetc(file);
						param[j] = c;
						j++;
					}
					break;

				case 1:
				
					while (c != " " && c != "\n")
					{
						c = fgetc(file);
						param[j] = c;
						j++;
					}
					break;
				
				default:
					break;
				}		
		}
		idx++;
	}
	
 
    fclose(file);*/
	return parameters;
}