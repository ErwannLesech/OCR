#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "neuronal_network_functions.h"


matrix *init_matrix(matrix *m, int rows, int cols, double value)
{
    m->rows = rows;
    m->cols = cols;
    m->data = malloc(sizeof(double) * (rows * cols));

    for (int idx = 0; idx < (rows * cols); idx++)
    {
        m->data[idx] = value;
    }
    
    return m;
}


matrix *init_rand_matrix(matrix *m, int rows, int cols)
{
    srand(time(NULL));

    m->rows = rows;
    m->cols = cols;
    m->data = malloc(sizeof(double) * (rows * cols));

    for (int idx = 0; idx < (rows * cols); idx++)
    {
        m->data[idx] = ((rand() % 10000) / 10000.0);
    }
    
    return m;
}


void free_matrix(matrix *m)
{
    free(m->data);
}


matrix *insert_value(matrix *m, int rows, int cols, double val)
{
    m->data[rows * m->cols + cols] = val;
    return m;
}


double get_value(matrix *m, int rows, int cols)
{
    double value = m->data[rows * m->cols + cols];
    return value;
}


matrix *add_matrix(matrix *m_one, matrix *m_two)
{
    int rows = m_one->rows;
    int cols = m_one->cols;

    double sum = 0;

    for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                sum = get_value(m_one, i, j) + get_value(m_two, i, j);
                insert_value(m_one, i, j, sum);
            }
        }
        return m_one;
}

matrix add_col_matrix(matrix *m)
{
    int rows = m->rows;
    int cols = m->cols;

    matrix sum;
    init_matrix(&sum, rows, 1, 0);
    for (int i = 0; i < rows; i++)
    {
        double total = 0.0;
        for (int j = 0; j < cols; j++)
        {
            total += get_value(m, i, j);
        }
        insert_value(&sum, i, 0, total);
    }
    return sum;
}


matrix substract_matrix(matrix *m_one, matrix *m_two)
{
    int rows = m_one->rows;
    int cols = m_one->cols;
    double diff;
    matrix substract_matrix;
    init_matrix(&substract_matrix, rows, cols, 0);

    for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                diff = get_value(m_one, i, j) - get_value(m_two, i, j);
                insert_value(&substract_matrix, i, j, diff);
            }
        }
        return substract_matrix;
}


matrix multiply_matrix(matrix *m_one, matrix *m_two)
{
    int m_one_rows = m_one->rows;
    int m_one_cols = m_one->cols;
    int m_two_rows = m_two->rows;
    int m_two_cols = m_two->cols;

    if (m_one_cols != m_two_rows)
    {
        printf("multiply_matrix: Incorrect dimensions.\n");
        print_matrix(m_one);
        print_matrix(m_two);
        exit(1);
    }

    int p_rows = m_one_rows;
    int p_cols = m_two_cols;

    matrix product_m;
    init_matrix(&product_m, p_rows, p_cols, 0);

    double sum;

    for (int i = 0; i < m_one_rows; i++)
    {
        for (int j = 0; j < m_two_cols; j++)
        {
            sum = 0;
            for (int k = 0; k < m_one_cols; k++)
            {
                sum += get_value(m_one, i, k) * get_value(m_two, k, j);
            }
            insert_value(&product_m, i, j, sum);
        }
    }

    return product_m;
}

matrix undot_matrix(matrix *m, double val)
{
    int m_rows = m->rows;
    int m_cols = m->cols;

    matrix undot_m;
    init_matrix(&undot_m, m_rows, m_cols, 0);

    for (int i = 0; i < m_rows; i++)
    {
        double data;
        for (int j = 0; j < m_cols; j++)
        {
            data = get_value(m, i, j) * val;
            insert_value(&undot_m, i, j, data);
        }
        
    }

    return undot_m;
}

matrix transpose_matrix(matrix *m)
{
    int m_rows = m->rows;
    int m_cols = m->cols;

    matrix transposed_m;
    init_matrix(&transposed_m, m_cols, m_rows, 0);
    
    double value = 0;

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            value = get_value(m, i, j);
            insert_value(&transposed_m, j, i, value);
        }
    }

    return transposed_m;
}

matrix *sigmoid_matrix(matrix *m)
{
    int m_rows = m->rows;
    int m_cols = m->cols;

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            double x = get_value(m, i, j);
            insert_value(m, i, j, sigmoid(x));
        }
    }
    return m;
}

void print_matrix(matrix *m)
{
    int m_rows = m->rows;
    int m_cols = m->cols;

    printf("m_dimensions: %i rows - %i cols\n", m_rows, m_cols);
    for (int i = 0; i < m_rows; i++)
    {
        printf("[");

        for (int j = 0; j < m_cols; j++)
        {
            printf(" %f ", get_value(m, i, j));
        }
        
        printf("]\n");   
    }
}