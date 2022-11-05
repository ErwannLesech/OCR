#pragma once

int main_xor(int argc, char *argv[]);
void train_network(long epochs, double lr);
void load_weights(char *filename);
void predict(char *a, char *b);