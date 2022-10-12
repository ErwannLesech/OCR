#pragma once

// we use row-major matrix structure

typedef struct 
{
    int rows;
    int cols;
    double *data;
} matrix;

// initialize a matrix
matrix *init_matrix(matrix *m, int rows, int cols);

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

// substract matrix m_two to matrix m_one
matrix *substract_matrix(matrix *m_one, matrix *m_two);

// multiply the matrix m_one and matrix m_two
matrix multiply_matrix(matrix *m_one, matrix *m_two);

// transpose matrix m_one
matrix transpose_matrix(matrix *m);

// apply the sigmoid function to the matrix m
matrix *sigmoid_matrix(matrix *m);

// print a matrix
void print_matrix(matrix *m);