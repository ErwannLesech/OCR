#pragma once

int main_xor(int argc, char *argv[]);
void train_network(long epochs, double lr, char *path);
void load_weights(char *filename);
void predict(char *a, char *b);