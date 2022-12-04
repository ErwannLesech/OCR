#pragma once
#include "neuronal_network_functions.h"

void save_parameters(multiple_result *parameters, char path[]);

multiple_result load_parameters(char path[], int input_neurons,
	int hidden_neurons, int output_neurons);
