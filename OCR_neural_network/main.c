#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"
#include "neuronal_network_functions.h"
#include "main.h"

const unsigned int input_neurons = 784;
const unsigned int hidden_neurons = 128;
const unsigned int output_neurons = 9;

double learning_rate = 0.1;
long epochs = 10000;

void train_network(long epochs, double lr, size_t nbInputs);
void load_weights(char *filename);
void predict(char *a, char *b);

int main_neural_network(int argc, char *argv[])
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
            printf("main_xor: train xor network - 1M epochs - ");
            printf("0.9 learning rate.\n");
            
            train_network(epochs, learning_rate, 5);
        }
        else    
        {
            printf("main_xor: train xor network - 10000 epochs - ");
            printf("0.1 learning rate.\n");
            train_network(10000, 0.1, 5);    
        }
    }
    else if (strcmp(argv[2], "-weights") == 0)
    {
        printf("main_xor: load_weights.\n\n");
        load_weights("weights.txt");
    }
    else if (strcmp(argv[2], "-predict") == 0)
    {
        printf("main_xor: predict.\n\n");
        predict(argv[3], argv[4]);
    }
    else
    {
        printf("main_xor: incorrect argv. -help for help.\n");
    }

    return EXIT_SUCCESS;
}

void train_network(long epochs, double lr, size_t nbInputs)
{
    matrix input;
    init_matrix(&input, 784, nbInputs, 0);
    print_matrix(&input);

    matrix exp_output;
    init_matrix(&exp_output, 1, nbInputs, 0);
    print_matrix(&exp_output);

    init_input_matrix(&input, &exp_output, nbInputs);
    print_matrix(&input);
    print_matrix(&exp_output);

    /*matrix exp_outputs;

    multiple_result parameters = initialization(input_neurons, 
    hidden_neurons, output_neurons);

    multiple_result forward_prop;
    multiple_result back_prop;


    for (long i = 0; i < epochs + 1; i++)
    {        
        forward_prop = forward_propagation(&parameters, &input);

        back_prop = back_propagation(&exp_outputs, 
        &parameters, &forward_prop);

        upgrade_parameters(input, &parameters, &forward_prop, &back_prop,
        lr);

        if (i % (epochs / 10) == 0)
        {
            /*
            matrix hw = parameters.a;
            matrix hb = parameters.b;
            matrix ow = parameters.c;
            matrix ob = parameters.d;
            
            print_matrix(&hw);
            print_matrix(&hb);
            print_matrix(&ow);
            print_matrix(&ob);*/

            /*matrix output_prop = forward_prop.b;
            printf("iteration : %li\n", i);
            print_matrix(&output_prop);
        }
    }

    // Parameters
    matrix hw = parameters.a;
    matrix hb = parameters.b;
    matrix ow = parameters.c;
    matrix ob = parameters.d;

    save_parameters(&parameters, "weights.txt");

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
    free_matrix(&dB2);*/
}


void load_weights(char *filename)
{
    multiple_result parameters;

    parameters = load_parameters(filename);
    matrix hw = parameters.a;
	matrix hb = parameters.b;
	matrix ow = parameters.c;
	matrix ob = parameters.d;

    print_matrix(&hw);
	printf("\n");
    print_matrix(&hb);
	printf("\n");
    print_matrix(&ow);
    printf("\n");
	print_matrix(&ob);
    printf("\n");
}

void predict(char *a, char *b)
{
    multiple_result parameters;

    parameters = load_parameters("weights.txt");

    matrix inputs_test;
    init_matrix(&inputs_test, 4, 2, 0);
    insert_value(&inputs_test, 0, 1, 1);
    insert_value(&inputs_test, 1, 0, 1);
    insert_value(&inputs_test, 2, 1, 1);
    insert_value(&inputs_test, 2, 0, 1);

    predict_xor(&parameters, inputs_test, (int)*a - 48, (int)*b - 48);
}