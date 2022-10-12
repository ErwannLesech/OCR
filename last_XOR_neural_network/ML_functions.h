#ifndef ML_FUNCTIONS_H
#define ML_FUNCTIONS_H

double sigmoid(double x);
double sigmoid_derivative(double x);
void add_matrix(double m1[], double m2[], size_t row, size_t col, double rm[]);
void multiply_matrix(double m1[], double m2[], size_t r1, size_t c1, 
		size_t c2, double rm[]);
double dot_product(double m1[][2], double m2[][2], size_t len);
void transpose_matrix(double matrix[], size_t row, size_t col, double rm[]);
double mean(double m1[][2], size_t row, size_t col);
void print_matrix(double matrix[], size_t row, size_t col);

#endif
