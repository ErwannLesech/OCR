#pragma once
#include "matrix.h"

struct multiple_result
{
    matrix a;
    matrix b;
    matrix c;
    matrix d;
};


double sigmoid(double x);

double sigmoid_derivative(double x);

struct multiple_result initialization(int input_neurons, 
int hidden_neurons, int output_neurons);

// hw -> hidden_weights, hb -> hidden_bias, 
// ow -> output_weights, ob -> output_bias

struct multiple_result forward_propagation(matrix *hw, matrix *hb, 
matrix *ow, matrix *ob, matrix *inputs);
