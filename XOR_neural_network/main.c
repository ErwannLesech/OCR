#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"
#include "neuronal_network_functions.h"
#include "main.h"


const unsigned int input_neurons = 2;
const unsigned int hidden_neurons = 2;
const unsigned int output_neurons = 1;

double learning_rate = 0.9;
long epochs = 1000000;

void train_network(long epochs, double lr);
void predict();

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("main_xor: Argv missing");
        return EXIT_FAILURE;
    }
    if (strcmp(argv[2], "-train") == 0)
    {
        if (argc > 3)
        {
            printf("main_xor: train xor network - 1M epochs - 0.9 learning rate.\n");
            train_network(epochs, learning_rate);
        }
        else    
        {
            printf("main_xor: train xor network - 10000 epochs - 0.1 learning rate.\n");
            train_network(10000, 0.1);    
            
        }
    }
    else if (strcmp(argv[2], "-weights") == 0)
    {
        printf("main_xor: load_weights.\n\n");
        load_weights("weights.txt");
    }
    else
    {
        printf("main_xor: incorrect argv. -help for help.\n");
    }

    return EXIT_SUCCESS;
}

void train_network(long epochs, double lr)
{
    /*Inputs =
    [[1, 0, 1, 0], 
    [0, 1, 1, 0]]*/

    matrix inputs;
    init_matrix(&inputs, 4, 2, 0);
    insert_value(&inputs, 0, 1, 1);
    insert_value(&inputs, 1, 0, 1);
    insert_value(&inputs, 2, 1, 1);
    insert_value(&inputs, 2, 0, 1);

    /*Exp_outputs =
    [[1], [1], [0], [0]]*/

    matrix exp_outputs;
    init_matrix(&exp_outputs, 4, 1, 0);
    insert_value(&exp_outputs, 0, 0, 1);
    insert_value(&exp_outputs, 1, 0, 1);

    multiple_result parameters = initialization(input_neurons, 
    hidden_neurons, output_neurons);

    multiple_result forward_prop;
    multiple_result back_prop;


    for (long i = 0; i < epochs + 1; i++)
    {        
        forward_prop = forward_propagation(&parameters, &inputs);

        back_prop = back_propagation(&exp_outputs, 
        &parameters, &forward_prop);

        upgrade_parameters(inputs, &parameters, &forward_prop, &back_prop,
        learning_rate);

        if (i % 1 == 0)
        {
            /*matrix hw = parameters.a;
            matrix hb = parameters.b;
            matrix ow = parameters.c;
            matrix ob = parameters.d;*/

            /*matrix output_prop = forward_prop.b;
            print_matrix(&output_prop);*/

            /*print_matrix(&hw);
            print_matrix(&hb);
            print_matrix(&ow);
            print_matrix(&ob);*/
        }
    }

    // Parameters
    matrix hw = parameters.a;
    matrix hb = parameters.b;
    matrix ow = parameters.c;
    matrix ob = parameters.d;

    save_parameters(&parameters, "weights.txt");

    // load_parameters("test.txt");
    // Forward prop
    matrix hidden_prop = forward_prop.a;
    matrix output_prop = forward_prop.b;

    print_matrix(&output_prop);

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
}


void load_weights(char *filename)
{
    multiple_result parameters;

    parameters = load_parameters(filename);

    printf("\n");
}