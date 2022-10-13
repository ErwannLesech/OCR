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

multiple_result initialization(int input_neurons, 
int hidden_neurons, int output_neurons);

// hw -> hidden_weights, hb -> hidden_bias, 
// ow -> output_weights, ob -> output_bias

multiple_result forward_propagation(multiple_result *parameters, matrix *inputs);

multiple_result back_propagation(matrix *inputs, matrix *exp_outputs, multiple_result *parameters, multiple_result *forward_prop);

multiple_result *upgrade_parameters(multiple_result *parameters, multiple_result *back_prop, double lr);

int predict(matrix *inputs, multiple_result *parameters);

void save_parameters(multiple_result *parameters, char path[]);