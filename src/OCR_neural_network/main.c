#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include "matrix.h"
#include "neuronal_network_functions.h"
#include "main.h"
#include "debug_tool.h"
#include "../Solver/main.h"
#include "save_parameters.h"

const unsigned int input_neurons = 784;
const unsigned int hidden_neurons1 = 128;
const unsigned int hidden_neurons2 = 32;
const unsigned int output_neurons = 10;

double learning_rate = 0.001;
long epochs = 500;

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
            train_network(epochs, learning_rate, 600);    
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
    else if (strcmp(argv[2], "-accuracy") == 0)
    {
        printf("predict_train\n");
        accuracy();
    }
    else if (strcmp(argv[2], "-test") == 0)
    {
        printf("test\n");
        matrix *input = init_input_matrix_predict("./OCR_neural_network/dataset/training/1/01.jpg");
        display_mat(*input);
    }
    else if (strcmp(argv[2], "-help") == 0)
    {
        printf("main_xor: -train to train the network.\n");
        printf("main_xor: -weights to load weights.\n");
        printf("main_xor: -predict to predict.\n");
        printf("main_xor: -test to test.\n");
    }
    else
    {
        printf("main_xor: incorrect argv. -help for help.\n");
    }

    return EXIT_SUCCESS;
}

void train_network(long epochs, double lr, size_t nbInputs)
{
    multiple_matrices entries = init_input_matrix(nbInputs);
    
    matrix *input = entries.a;
    matrix *exp_output = entries.b;
    
    /*print_matrix(input);
    print_matrix(exp_output);*/

    matrix *exp_output_hot = exp_output_init(exp_output);
    //print_matrix(exp_output_hot);

    multiple_matrices parameters = initialization(input_neurons, 
    hidden_neurons1, hidden_neurons2, output_neurons);
    /*print_matrix(parameters.a);
    print_matrix(parameters.b);
    print_matrix(parameters.c);
    print_matrix(parameters.d);
    print_matrix(parameters.e);
    print_matrix(parameters.f);
    */

    multiple_matrices forward_prop;
    multiple_matrices back_prop;
    
    for (long i = 0; i < epochs + 1; i++)
    {        
        printf("%i\n", i);

        shuffle(input, exp_output_hot);
        
        forward_prop = forward_propagation(&parameters, input);

        back_prop = back_propagation(exp_output_hot, input,
        &parameters, &forward_prop);

        upgrade_parameters(input, &parameters, &forward_prop, &back_prop,
        lr);

        /*if (i % (epochs / 10) == 0)
        {
            print_matrix(parameters.a);
            print_matrix(parameters.b);
            print_matrix(parameters.c);
            print_matrix(parameters.d);

            print_matrix(forward_prop.c);
        }*/
    }

    // Parameters
    /*matrix *hw = parameters.a;
    matrix *hb = parameters.b;
    matrix *ow = parameters.c;
    matrix *ob = parameters.d;*/

    /*print_matrix(&hw);
    print_matrix(&hb);
    print_matrix(&ow);
    print_matrix(&ob);*/

    save_parameters(parameters, "./OCR_neural_network/weights.txt");

    // Free all matrices*/
    free_multiple_matrices(parameters);
    free_multiple_matrices(forward_prop);
    free_multiple_matrices(back_prop);

    free_multiple_matrices(entries);
    free_matrix(exp_output_hot);
}

void load_weights(char *filename)
{
    multiple_matrices parameters;

    parameters = load_parameters(filename, input_neurons, hidden_neurons1, hidden_neurons2, output_neurons);
    matrix *hw = parameters.a;
	matrix *hb = parameters.b;
	matrix *ow = parameters.c;
	matrix *ob = parameters.d;

    print_matrix(hw);
	printf("\n");
    print_matrix(hb);
	printf("\n");
    print_matrix(ow);
    printf("\n");
	print_matrix(ob);
    printf("\n");

    free_multiple_matrices(parameters);
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

    matrix *input;
    multiple_matrices forward_prop;
    matrix *output_prop;
    
    multiple_matrices parameters;
    parameters = load_parameters("./OCR_neural_network/weights.txt", input_neurons, hidden_neurons1, hidden_neurons2, output_neurons);
    /*matrix *w1 = parameters.a;
	matrix *b1 = parameters.b;
	matrix *w2 = parameters.c;
	matrix *b2 = parameters.d;
    matrix *w3 = parameters.e;
    matrix *b3 = parameters.f;*/

    int nb = 0;

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
        input = init_input_matrix_predict(path);
        if (input != NULL)
        {
            forward_prop = forward_propagation(&parameters, input);
            output_prop = forward_prop.f;
            print_matrix(output_prop);
            double max = get_value(output_prop, 0, 0);
            char index = '0';
            for (int k = 1; k < 10; k++)
            {
                if (get_value(output_prop, k, 0) > max)
                {
                    index = k + 48;
                    max = get_value(output_prop, k, 0);
                }
            }
            printf("%c \n", index);
            if (index != '0')
            {
                printf("%d \n", i);
                a[i/9][i%9] = index;
            }
        }
        else
        {
            nb++;
        }
    }

    printf("%d \n", nb);

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

void accuracy()
{
    srand(time(NULL));
    int accuracy = 0;

    matrix *input;
    multiple_matrices forward_prop;
    matrix *output_prop;
    
    multiple_matrices parameters;
    parameters = load_parameters("./OCR_neural_network/weights.txt", input_neurons, hidden_neurons1, hidden_neurons2, output_neurons);
    /*print_matrix(parameters.a);
    print_matrix(parameters.b);
    print_matrix(parameters.c);
    print_matrix(parameters.d);
    print_matrix(parameters.e);
    print_matrix(parameters.f);*/

    for (int i = 0; i < 200; i++)
    {    
        int number = rand() % 9 + 1;
		int random = rand() % 10;
		int random2 = rand() % 10;
		char path[46] = "./OCR_neural_network/dataset/training/";
		path[38] = number + 48;
		path[39] = '/';
		path[40] = random + 48;
		path[41] = random2 + 48;
		path[42] = '.';
		path[43] = 'j';
		path[44] = 'p';
		path[45] = 'g';
		path[46] = '\0';
        printf("%s \n", path);
        input = init_input_matrix_accuracy(path);
        
        forward_prop = forward_propagation(&parameters, input);
        output_prop = forward_prop.f;
        double max = get_value(output_prop, 0, 0);
        char index = '0';
        for (int k = 1; k < 10; k++)
        {
            if (get_value(output_prop, k, 0) > max)
            {
                index = k + 48;
                max = get_value(output_prop, k, 0);
            }
        }
        printf("got %c - expected %c - ", index, number + 48);
        if (index == number + 48)
        {
            printf("Correct \n");
            accuracy++;
        }
        else
        {
            printf("Incorrect \n");
        }
    }
    printf("accuracy: %f \n", ((double)accuracy/(double)100));
    return accuracy;
}
