#pragma once

// we use row-major matrix structure

typedef struct 
{
    int rows;
    int cols;
    double *data;
} matrix;

// initialize a matrix
matrix *init_matrix(matrix *m, int rows, int cols, double value);

// initialize a matrix with random values
matrix *init_rand_matrix(matrix *m, int rows, int cols);

// free the allocation of memory of the matrix
void free_matrix(matrix *m);

// insert a value 'val' in matrix m at location rows/cols
matrix *insert_value(matrix *m, int rows, int cols, double val);

// get the value in matrix m at location rows/cols
double get_value(matrix *m, int rows, int cols);

// add matrix m_two in matrix m_one
matrix *add_matrix(matrix *m_one, matrix *m_two);

// add matrix resized to fit in m_on dimention, m_two in matrix m_one 
matrix *add_matrix_bias(matrix *m_one, matrix *m_two);

// sum colomns of matrix m
matrix add_col_matrix(matrix *m);

// sum rows of matrix m
matrix add_row_matrix(matrix *m);

// substract matrix m_two and matrix m_one
matrix substract_matrix(matrix *m_one, matrix *m_two);

// multiply the matrix m_one and matrix m_two
matrix dot_matrix(matrix *m_one, matrix *m_two);

// multiply every values in the matrix by val
matrix multiply_matrix(matrix *m, double val);

// transpose matrix m_one
matrix transpose_matrix(matrix *m);

// apply the sigmoid function to the matrix m
matrix *sigmoid_matrix(matrix *m);

// apply the derivative sigmoid function to the matrix m
matrix *d_sigmoid_matrix(matrix *m, matrix *m_two);

// apply the relu function to the matrix m
matrix *relu_matrix(matrix *m);

// apply the derivative relu function to the matrix m
matrix *d_relu_matrix(matrix *m, matrix *m_two);

// return max value of the matrix m
double max_value(matrix *m);

// apply the softmax function to the matrix m
matrix *softmax_matrix(matrix *m);

// create a copy of the matrix m
matrix copy_matrix(matrix *m);

// print a matrix
void print_matrix(matrix *m);
