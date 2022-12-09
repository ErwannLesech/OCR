#pragma once
#include "matrix.h"

typedef struct 
{
    matrix *a;
    matrix *b;
    matrix *c;
    matrix *d;
    matrix *e;
    matrix *f;
} multiple_matrices;

void free_multiple_matrices(multiple_matrices matrices);

double sigmoid(double x);

double sigmoid_derivative(double x);

double relu(double x);

double relu_derivative(double x);

double softmax(double x, double sum);

double softmax_derivative(x);

matrix *init_input_matrix_test(char *path);

multiple_matrices init_input_matrix(size_t nbInputs);


multiple_matrices initialization(int input_neurons,
	int hidden_neurons1, int hidden_neurons2, int output_neurons);

multiple_matrices forward_propagation(multiple_matrices *parameters, 
    matrix *inputs);

matrix *exp_output_init(matrix *exp_output);

multiple_matrices back_propagation(matrix *exp_outputs, matrix *inputs,
    multiple_matrices *parameters, multiple_matrices *forward_prop);

multiple_matrices *upgrade_parameters(matrix *inputs, multiple_matrices *parameters,
	multiple_matrices *forward_prop, multiple_matrices *back_prop, double lr);