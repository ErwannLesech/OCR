#pragma once
#include "neuronal_network_functions.h"

void save_parameters(multiple_matrices parameters, char path[]);

multiple_matrices load_parameters(char path[], int input_neurons,
	int hidden_neurons, int output_neurons);
