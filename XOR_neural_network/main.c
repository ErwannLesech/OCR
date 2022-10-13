#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "neuronal_network_functions.h"

const unsigned int input_neurons = 2;
const unsigned int hidden_neurons = 2;
const unsigned int output_neurons = 1;

const double learning_rate = 0.1;
const long epochs = 1000;

int main()
{
    matrix inputs;
    init_matrix(&inputs, 4, 2, 0);
    insert_value(&inputs, 1, 1, 1);
    insert_value(&inputs, 2, 0, 1);
    insert_value(&inputs, 3, 0, 1);
    insert_value(&inputs, 3, 1, 1);

    matrix exp_outputs;
    init_matrix(&exp_outputs, 4, 1, 0);
    insert_value(&inputs, 1, 0, 1);
    insert_value(&inputs, 2, 0, 1);

    multiple_result parameters = initialization(input_neurons, 
    hidden_neurons, output_neurons);

    multiple_result forward_prop;
    multiple_result back_prop;

    for (long i = 0; i < epochs; i++)
    {
        if (i % 100 == 0)
        {
            printf("iter: %li\n", i);

            matrix hw = parameters.a;
            matrix hb = parameters.b;
            matrix ow = parameters.c;
            matrix ob = parameters.d;

            print_matrix(&hw);
            print_matrix(&hb);
            print_matrix(&ow);
            print_matrix(&ob);
        }
        
        forward_prop = forward_propagation(&parameters, &inputs);

        back_prop = back_propagation(&inputs, &exp_outputs, 
        &parameters, &forward_prop);

        upgrade_parameters(&parameters, &back_prop, learning_rate);
    }

    // save_parameters(&parameters, "test.txt");

    /*matrix test;
    init_matrix(&test, 1, 2, 0);

    printf(predict(&init_matrix, &parameters));*/

    // Parameters
    matrix hw = parameters.a;
    matrix hb = parameters.b;
    matrix ow = parameters.c;
    matrix ob = parameters.d;

    // Forward prop
    matrix hidden_prop = forward_prop.a;
    matrix output_prop = forward_prop.b;

    // Back prop
    matrix dW1 = back_prop.a;
	matrix dB1 = back_prop.b;
	matrix dW2 = back_prop.c;
	matrix dB2 = back_prop.d;

    // Free all matrices

    free_matrix(&hw);
    free_matrix(&hb);
    free_matrix(&ow);
    free_matrix(&ob);

    free_matrix(&hidden_prop);
    free_matrix(&output_prop);

    free_matrix(&dW1);
    free_matrix(&dB1);
    free_matrix(&dW2);
    free_matrix(&dB2);

    return EXIT_SUCCESS;
}