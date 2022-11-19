#pragma once
#include "matrix.h"

typedef struct 
{
    matrix a;
    matrix b;
    matrix c;
    matrix d;
} multiple_result;

/*typedef struct
{
    multiple_result
} layer;

typedef struct
{
    size_t layer_number;
    layer layers[layer_number];
} neural_network;*/

double sigmoid(double x);

double sigmoid_derivative(double x);

void create_input_matrix(matrix *input, char *path);

multiple_result initialization(int input_neurons, 
int hidden_neurons, int output_neurons);

// hw -> hidden_weights, hb -> hidden_bias, 
// ow -> output_weights, ob -> output_bias

multiple_result forward_propagation(multiple_result *parameters, 
    matrix *inputs);

multiple_result back_propagation(matrix *exp_outputs, 
    multiple_result *parameters, multiple_result *forward_prop);

multiple_result *upgrade_parameters(matrix inputs, multiple_result *parameters,
    multiple_result *forward_prop, multiple_result *back_prop, double lr);

// simulate forward_prop for a test input
double predict_xor(multiple_result *parameters, matrix inputs, int a, int b);

void save_parameters(multiple_result *parameters, char path[]);

multiple_result load_parameters(char path[]);