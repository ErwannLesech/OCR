#pragma once
#include "matrix.h"

typedef struct 
{
    matrix a;
    matrix b;
    matrix c;
    matrix d;
} multiple_result;

double sigmoid(double x);

double sigmoid_derivative(double x);

double relu(double x);

double relu_derivative(double x);

double softmax(double x, size_t index, matrix *m);

void init_input_matrix(matrix *input, matrix *exp_output, size_t nbInputs);

multiple_result initialization(int input_neurons, 
int hidden_neurons, int output_neurons);

// hw -> hidden_weights, hb -> hidden_bias, 
// ow -> output_weights, ob -> output_bias

multiple_result forward_propagation(multiple_result *parameters, 
    matrix *inputs);

matrix one_hot(matrix exp_output);

multiple_result back_propagation(matrix *exp_outputs, matrix *inputs,
    multiple_result *parameters, multiple_result *forward_prop);

multiple_result *upgrade_parameters(matrix inputs, multiple_result *parameters,
    multiple_result *forward_prop, multiple_result *back_prop, double lr);

void save_parameters(multiple_result *parameters, char path[]);

multiple_result load_parameters(char path[]);