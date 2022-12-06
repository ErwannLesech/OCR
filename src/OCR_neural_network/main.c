#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrix.h"
#include "neuronal_network_functions.h"
#include "main.h"
#include "debug_tool.h"
#include "../Solver/main.h"
#include "save_parameters.h"

const unsigned int input_neurons = 784;
const unsigned int hidden_neurons = 10;
const unsigned int output_neurons = 10;

double learning_rate = 0.1;
long epochs = 10000;

void train_network(long epochs, double lr, size_t nbInputs);
void load_weights(char *filename);
void predict();

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
            printf("main_nn: train xor network - 1M epochs - ");
            printf("0.9 learning rate.\n");
            
            train_network(epochs, learning_rate, 5);
        }
        else    
        {
            printf("main_nn: train xor network - 10000 epochs - ");
            printf("0.1 learning rate.\n");
            train_network(1000, 0.01, 60);    
        }
    }
    else if (strcmp(argv[2], "-weights") == 0)
    {
        printf("main_xor: load_weights.\n\n");
        load_weights("./OCR_neural_network/weights.txt");
    }
    else if (strcmp(argv[2], "-predict") == 0)
    {
        printf("predict\n");
        predict();
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


    matrix exp_output;
    init_matrix(&exp_output, 1, nbInputs, 0);

    
    init_input_matrix(&input, &exp_output, nbInputs);
    print_matrix(&input);
    print_matrix(&exp_output);

    matrix Y_t = exp_output_init(exp_output);
    //print_matrix(&Y_t);

    multiple_result parameters = initialization(input_neurons, 
    hidden_neurons, output_neurons);
    /*print_matrix(&parameters.a);
    print_matrix(&parameters.b);
    print_matrix(&parameters.c);
    print_matrix(&parameters.d);*/

    multiple_result forward_prop;
    multiple_result back_prop;
    
    /*for (long i = 0; i < epochs + 1; i++)
    {        
        printf("%i\n", i);
        
        forward_prop = forward_propagation(&parameters, &input);

        back_prop = back_propagation(&exp_output, &input,
        &parameters, &forward_prop);

        upgrade_parameters(input, &parameters, &forward_prop, &back_prop,
        lr);

        if (i % (epochs / 10) == 0)
        {
            
            matrix hw = parameters.a;
            matrix hb = parameters.b;
            matrix ow = parameters.c;
            matrix ob = parameters.d;
            
            print_matrix(&hw);
            print_matrix(&hb);
            print_matrix(&ow);
            print_matrix(&ob);

            matrix output_prop = forward_prop.b;
            print_matrix(&output_prop);
        }
    }*/

    // Parameters
    matrix hw = parameters.a;
    matrix hb = parameters.b;
    matrix ow = parameters.c;
    matrix ob = parameters.d;

    print_matrix(&hw);
    print_matrix(&hb);
    print_matrix(&ow);
    print_matrix(&ob);

    save_parameters(&parameters, "./OCR_neural_network/weights.txt");

    /*free_matrix(&hw);
    free_matrix(&hb);
    free_matrix(&ow);
    free_matrix(&ob);*/

    //load_weights("./OCR_neural_network/weights.txt");

    matrix Z1 = forward_prop.a;
    matrix A1 = forward_prop.b;
    matrix A2 = forward_prop.c;

    /*free_matrix(&Z1);
    free_matrix(&A1);
    free_matrix(&A2);*/

    print_matrix(&A2);

    // Back prop
    matrix dW1 = back_prop.a;
	matrix dB1 = back_prop.b;
	matrix dW2 = back_prop.c;
	matrix dB2 = back_prop.d;

    // Free all matrices


    /*free_matrix(&dW1);
    free_matrix(&dB1);
    free_matrix(&dW2);
    free_matrix(&dB2);

    free_matrix(&input);
    free_matrix(&exp_output);
    free_matrix(&Y_t);*/
}


void load_weights(char *filename)
{
    multiple_result parameters;

    parameters = load_parameters(filename, input_neurons, hidden_neurons, output_neurons);
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

    free_matrix(&hw);
    free_matrix(&hb);
    free_matrix(&ow);
    free_matrix(&ob);
}


void predict()
{
    char a[9][9] = {
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'},
	{'.','.','.','.','.','.','.','.','.'}
    };

    matrix input;
    init_matrix(&input, 784, 1, 0);
    
    multiple_result parameters;
    parameters = load_parameters("./OCR_neural_network/weights.txt", input_neurons, hidden_neurons, output_neurons);
    matrix hw = parameters.a;
	matrix hb = parameters.b;
	matrix ow = parameters.c;
	matrix ob = parameters.d;

    for (int i = 0; i < 81; i++)
    {    
        char path[12] = "cells/";
        path[6] = (i/10) + 48;
        path[7] = (i%10) + 48;
        path[8] = '.';
        path[9] = 'p';
        path[10] = 'n';
        path[11] = 'g';
        path[12] = '\0';
        init_input_matrix_test(&input, path);
        multiple_result forward_prop = forward_propagation(&parameters, &input);
        matrix output_prop = forward_prop.c;
        char max = '0';
        for (int k = 0; k < 9; k++)
        {
            if (get_value(&output_prop, k, 0) > max - 48 && get_value(&output_prop, k, 0) != 0)
            {
                max = k + 48;
            }
        }
        a[i/9][i%9] = max;
    }

	FILE* output_file = fopen("grid.txt", "w");

	for(unsigned int i = 0; i < 9; i++)
	{
		if(i%3 == 0 && i != 0)
        {
			fprintf(output_file, "\n");
        }

		for(unsigned int j = 0; j < 9; j++)
		{
			if(j%3 == 0 && j != 0)
			{
				fprintf(output_file, " ");
			}
			fprintf(output_file, "%c", a[i][j]);
		}

		fprintf(output_file, "\n");
	}
    fprintf(output_file, "\n");
	fclose(output_file);
    printf("Done\n");
}
