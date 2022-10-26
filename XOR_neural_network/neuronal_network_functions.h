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

multiple_result back_propagation(matrix *exp_outputs, multiple_result *parameters, multiple_result *forward_prop);

multiple_result *upgrade_parameters(matrix inputs, multiple_result *parameters, multiple_result *forward_prop, multiple_result *back_prop, double lr);

// simulate forward_prop for a test input
double predict_xor(multiple_result *parameters, matrix inputs);

double log_loss(double exp_output, double pred_output);

double xor_accuracy(multiple_result *parameters, int nb_tests);

void save_parameters(multiple_result *parameters, char path[]);

multiple_result load_parameters(char path[]);