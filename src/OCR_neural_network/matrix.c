#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "neuronal_network_functions.h"


matrix *init_matrix(int rows, int cols, double value)
{
    matrix *m = malloc(sizeof(matrix));
    if(m == NULL)
    {
        printf("init_matrix: malloc failed.\n");
        exit(EXIT_FAILURE);
    }

    m->rows = rows;
    m->cols = cols;
    m->data = calloc((rows * cols), sizeof(double));

    if (m->data == NULL)
    {
        printf("init_matrix: malloc failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int idx = 0; idx < (rows * cols); idx++)
    {
        m->data[idx] = value;
    }
    
    return m;
}

matrix *init_rand_matrix(int rows, int cols)
{
    srand(time(NULL));

    matrix *m = malloc(sizeof(matrix));
    if(m == NULL)
    {
        printf("init_matrix: malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    
    m->rows = rows;
    m->cols = cols;
    m->data = malloc(sizeof(double) * (rows * cols));

    if (m->data == NULL)
    {
        printf("init_rand_matrix: malloc failed.\n");
        exit(EXIT_FAILURE);

    }

    for (int idx = 0; idx < (rows * cols); idx++)
    {
        double random = 0;
        
        random = (((double)rand()/(double) RAND_MAX) - 0.5);
        m->data[idx] = (random);
    }
    
    return m;
}

void free_matrix(matrix *m)
{
    free(m->data);
    free(m);
}

void shuffle_matrix(matrix *a[], int n)
{
	srand(time(NULL));
	for (int i = n - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		matrix *temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}


int insert_value(matrix *m, int rows, int cols, double val)
{
    if (rows > m->rows || cols > m->cols)
    {
        printf("insert_value: index out of range.\n");
        return 0;
    }
    
    m->data[rows * m->cols + cols] = val;
    return 1;
}


double get_value(matrix *m, int rows, int cols)
{
    int m_rows = m->rows;
    int m_cols = m->cols;

    if (rows > m_rows || cols > m_cols)
    {
        printf("get_value: index out of range.\n");
        return 0;
    }

    double value = m->data[rows * m->cols + cols];
    if (value != value)
    {
        return 0;
    }
    
    return value;
}


matrix *add_matrix(matrix *m_one, matrix *m_two)
{
    int rows = m_one->rows;
    int cols = m_one->cols;
    int rows_two = m_two->rows;
    int cols_two = m_two->cols;

    if (rows != rows_two || cols != cols_two)
    {
        printf("add_matrix: matrix dimensions do not match.\n");
        return NULL;
    }
    
    matrix *m = init_matrix(rows, cols, 0);
    double sum = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sum = get_value(m_one, i, j) + get_value(m_two, i, j);
            insert_value(m, i, j, sum);
        }
    }
    return m;
}


matrix *add_matrix_bias(matrix *m_one, matrix *m_two)
{
    int rows = m_one->rows;
    int cols = m_one->cols;

    int rows_two = m_two->rows;
    int cols_two = m_two->cols;

    if (cols_two != 1 || rows != rows_two)
    {
        printf("add_matrix_bias: matrix dimensions do not match.\n");
        return NULL;
    }

    matrix *m = init_matrix(rows, cols, 0);
    double sum = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sum = get_value(m_one, i, j) + get_value(m_two, i, 0);
            insert_value(m, i, j, sum);
        }
    }
    return m;
}

matrix *add_col_matrix(matrix *m)
{
    int rows = m->rows;
    int cols = m->cols;

    matrix *sum = init_matrix(rows, 1, 0);

    if (sum == NULL)
    {
        printf("add_col_matrix: malloc failed.\n");
        return NULL;
    }
    
    for (int i = 0; i < rows; i++)
    {
        double total = 0.0;
        for (int j = 0; j < cols; j++)
        {
            total += get_value(m, i, j);
        }
        insert_value(sum, i, 0, total);
    }
    return sum;
}

matrix *add_row_matrix(matrix *m)
{
    int rows = m->rows;
    int cols = m->cols;

    matrix *sum = init_matrix(1, cols, 0);

    if (sum == NULL)
    {
        printf("add_row_matrix: malloc failed.\n");
        return NULL;
    }  
    
    for (int i = 0; i < cols; i++)
    {
        double total = 0.0;
        for (int j = 0; j < rows; j++)
        {
            total += get_value(m, j, i);
        }
        insert_value(sum, 0, i, total);
    }
    return sum;
}

double sum_matrix(matrix *m)
{
    int rows = m->rows;
    int cols = m->cols;

    double sum = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sum += get_value(m, i, j);
        }
    }
    return sum;
}

matrix *substract_matrix(matrix *m_one, matrix *m_two)
{
    int rows = m_one->rows;
    int cols = m_one->cols;
    int rows_two = m_two->rows;
    int cols_two = m_two->cols;
    double diff;
    matrix *substract_matrix = init_matrix(rows, cols, 0);

    if(rows != rows_two || cols != cols_two)
    {
        printf("substract_matrix: matrix dimensions do not match.\n");
        printf("rows: %d, rows_two: %d, cols: %d, cols_two: %d \n", rows, rows_two, cols, cols_two);
        return NULL;
    }

    if(substract_matrix == NULL)
    {
        printf("substract_matrix: malloc failed.\n");
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            diff = get_value(m_one, i, j) - get_value(m_two, i, j);
            insert_value(substract_matrix, i, j, diff);
        }
    }
    return substract_matrix;
}

matrix *substract_matrix_scal(matrix *m_one, double scal)
{
    int rows = m_one->rows;
    int cols = m_one->cols;
    double diff;
    matrix *substract_matrix = init_matrix(rows, cols, 0);
    if (substract_matrix == NULL)
    {
        printf("substract_matrix_scal: malloc failed.\n");
        return NULL;
    }
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            diff = get_value(m_one, i, j) - scal;
            insert_value(substract_matrix, i, j, diff);
        }
    }
    return substract_matrix;
}


matrix *dot_matrix(matrix *m_one, matrix *m_two)
{
    int m_one_rows = m_one->rows;
    int m_one_cols = m_one->cols;
    int m_two_rows = m_two->rows;
    int m_two_cols = m_two->cols;

    if (m_one_cols != m_two_rows)
    {
        printf("multiply_matrix: Incorrect dimensions.\n");
        printf("m_one_rows: %d, m_one_cols: %d, m_two_rows: %d, m_two_cols: %d\n", m_one_rows, m_one_cols, m_two_rows, m_two_cols);
        /*print_matrix(m_one);
        print_matrix(m_two);*/
        exit(EXIT_FAILURE);
    }

    int p_rows = m_one_rows;
    int p_cols = m_two_cols;

    matrix *product_m = init_matrix(p_rows, p_cols, 0);

    if(product_m == NULL)
    {
        printf("dot_matrix: malloc failed.\n");
        return NULL;
    }

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
            insert_value(product_m, i, j, sum);
        }
    }

    return product_m;
}

matrix *multiply_matrix(matrix *m, double val)
{
    int m_rows = m->rows;
    int m_cols = m->cols;

    matrix *undot_m = init_matrix(m_rows, m_cols, 0);

    if (undot_m == NULL)
    {
        printf("multiply_matrix: malloc failed.\n");
        return NULL;
    }

    for (int i = 0; i < m_rows; i++)
    {
        double data = 0;
        for (int j = 0; j < m_cols; j++)
        {
            data = get_value(m, i, j) * val;
            insert_value(undot_m, i, j, data);
        }   
    }
    return undot_m;
}

matrix *transpose_matrix(matrix *m)
{
    int m_rows = m->rows;
    int m_cols = m->cols;

    matrix *transposed_m = init_matrix( m_cols, m_rows, 0);

    if(transposed_m == NULL)
    {
        printf("transpose_matrix: malloc failed.\n");
        return NULL;
    }
    
    double value = 0;

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            value = get_value(m, i, j);
            insert_value(transposed_m, j, i, value);
        }
    }
    return transposed_m;
}

matrix *sigmoid_matrix(matrix *m)
{
    int m_rows = m->rows;
    int m_cols = m->cols;

    matrix *sigmoid_m = init_matrix(m_rows, m_cols, 0);

    if(sigmoid_m == NULL)
    {
        printf("sigmoid_matrix: malloc failed.\n");
        return NULL;
    }

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            double x = get_value(m, i, j);
            insert_value(sigmoid_m, i, j, sigmoid(x));
        }
    }
    return sigmoid_m;
}

matrix *d_sigmoid_matrix(matrix *m, matrix *m_two)
{
    int m_rows = m->rows;
    int m_cols = m->cols;

    matrix *d_sigmoid_m = init_matrix(m_rows, m_cols, 0);

    if(d_sigmoid_m == NULL)
    {
        printf("d_sigmoid_matrix: malloc failed.\n");
        return NULL;
    }

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            double x = get_value(m_two, i, j);
            double y = get_value(m, i, j);
            insert_value(d_sigmoid_m, i, j, (y * sigmoid_derivative(x)));
        }
    }
    return d_sigmoid_m;
}

// apply the relu function to the matrix m
matrix *relu_matrix(matrix *m)
{
    int m_rows = m->rows;
    int m_cols = m->cols;

    matrix *relu_m = init_matrix(m_rows, m_cols, 0);

    if(relu_m == NULL)
    {
        printf("relu_matrix: malloc failed.\n");
        return NULL;
    }

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            double x = get_value(m, i, j);
            insert_value(relu_m, i, j, relu(x));
        }
    }
    return relu_m;
}

// apply the derivative relu function to the matrix m
matrix *d_relu_matrix(matrix *m, matrix *m_two)
{
    int m_rows = m->rows;
    int m_cols = m->cols;

    matrix *d_relu_m = init_matrix(m_rows, m_cols, 0);

    if(d_relu_m == NULL)
    {
        printf("d_relu_matrix: malloc failed.\n");
        return NULL;
    }

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            double x = get_value(m_two, i, j);
            double y = get_value(m, i, j);
            insert_value(d_relu_m, i, j, (y * relu_derivative(x)));
        }
    }
    return d_relu_m;
}

double sum_exp(matrix *m, int col)
{
    int m_rows = m->rows;
    int m_cols = m->cols;

    double sum = 0;

    for (int j = 0; j < m_rows; j++)
    {
        sum += exp(get_value(m, j, col));
    }

    return sum;
}

// apply the softmax function to the matrix m
matrix *softmax_matrix(matrix *m)
{
    int m_rows = m->rows;
    int m_cols = m->cols;

    double sum = 0;
    matrix *softmax_m = init_matrix(m_rows, m_cols, 0);

    if(softmax_m == NULL)
    {
        printf("softmax_matrix: malloc failed.\n");
        return NULL;
    }

    for (int i = 0; i < m_cols; i++)
    {
        sum = sum_exp(m, i);
        if (sum == 0)
        {
            sum = 0.0001;
        }
        
        for (int j = 0; j < m_rows; j++)
        {
            double x = get_value(m, j, i);
            insert_value(softmax_m, j, i, exp(x)/sum);
        }
    }

    return softmax_m;
}

matrix *copy_matrix(matrix *m)
{
    int m_rows = m->rows;
    int m_cols = m->cols;

    matrix *copy_m = init_matrix(m_rows, m_cols, 0);

    if(copy_m == NULL)
    {
        printf("copy_matrix: malloc failed.\n");
        return NULL;
    }

    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            double x = get_value(m, i, j);
            insert_value(copy_m, i, j, x);
        }
    }
    return copy_m;
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