#include <stdlib.h>
#include "matrix.h"
#include "neuronal_network_functions.h"

const unsigned int input_neurons = 2;
const unsigned int hidden_neurons = 2;
const unsigned int output_neurons = 1;

int main()
{
    matrix inputs;
    init_matrix(&inputs, 4, 2);
    insert_value(&inputs, 1, 1, 1);
    insert_value(&inputs, 2, 0, 1);
    insert_value(&inputs, 3, 0, 1);
    insert_value(&inputs, 3, 1, 1);

    print_matrix(&inputs);

    struct multiple_result init_network = initialization(input_neurons, 
    hidden_neurons, output_neurons);

    matrix hw = init_network.a;
    matrix hb = init_network.b;
    matrix ow = init_network.c;
    matrix ob = init_network.d;

    print_matrix(&hw);
    print_matrix(&hb);
    print_matrix(&ow);
    print_matrix(&ob);

    struct multiple_result forward_prop = forward_propagation(&hw, &hb, &ow, &ob,
    &inputs);

    print_matrix(&forward_prop.a);
    print_matrix(&forward_prop.b);

    return EXIT_SUCCESS;
}