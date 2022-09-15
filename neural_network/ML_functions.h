#ifndef ML_FUNCTIONS_H
#define ML_FUNCTIONS_H

float sigmoid(float x);
float sigmoid_derivative(float x);
void multiply_matrix(double m1[][2], double m2[][2], size_t r1, size_t c1, size_t c2, double return_matrix[][2]);
double dot_product(double m1[][2], double m2[][2], size_t len);
float mean(float m1[][2], size_t len);
void print_matrix(float matrix[][2], size_t len);

#endif
