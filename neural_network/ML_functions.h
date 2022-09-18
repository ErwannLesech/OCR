#ifndef ML_FUNCTIONS_H
#define ML_FUNCTIONS_H

float sigmoid(float x);
float sigmoid_derivative(float x);
void multiply_matrix(float m1[], float m2[], size_t r1, size_t c1, size_t c2, float return_matrix[]);
double dot_product(double m1[][2], double m2[][2], size_t len);
float mean(float m1[][2], size_t row, size_t col);
void print_matrix(float matrix[], size_t row, size_t col);

#endif
