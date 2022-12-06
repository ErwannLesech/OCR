#include <stddef.h>
#pragma once

int main_xor(int argc, char *argv[]);
void train_network(long epochs, double lr, size_t nbInputs);
void load_weights(char *filename);
void predict();