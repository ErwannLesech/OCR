#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}

double sigmoid_derivative(double x)
{
	return sigmoid(x) *  (1 - sigmoid(x));
}

// rm -> return_matrix
void add_matrix(double m1[], double m2[], size_t row, size_t col, double rm[])
{
	for(size_t idx = 0; idx < row; idx++)
	{
		for(size_t j = 0; j < col; j++)
			{
				rm[idx * col + j] = 
					m1[idx * col + j] + m2[idx * col + j];
			}
	}
}

void multiply_matrix(double m1[], double m2[], size_t r1, size_t c1, 
		size_t c2, double rm[])
{
	for(size_t i = 0; i < r1; i++)
	{
		for(size_t j = 0; j < c2; j++)
		{
			for(size_t k = 0; k < c1; k++)
			{
				rm[i * c2 + j] += 
					m1[i * c1 + k] * m2[k * c2 + j]; 
			}
		}
	}
}

double dot_product(double m1[][2], double m2[][2], size_t len)
{
	double product = 0;
 
	for (size_t i = 0; i < len; i++)
 	{
		for(size_t j = 0; j < len; j++)
		{
			product += m1[i][j] * m2[i][j];
		}
	}

	return product;
}

double mean(double m1[][2], size_t row, size_t col)
{
	double sum = 0;

	for(size_t i = 0; i < row; i++)
	{
		for(size_t j = 0; j < col; j++)
		{
			sum += m1[i][j];
		}
	}

	return sum / (row * col);

}

void transpose_matrix(double matrix[], size_t row, size_t col, double rm[])
{
	for(size_t i = 0; i < row; i++)
	{
		for(size_t j = 0; j < col; j++)
		{
			rm[j * col + i] = matrix[i * col + j];
		}
	}
}

void print_matrix(double matrix[], size_t row, size_t col)
{
	 for(size_t i = 0; i < row; i++)
        {
                for(size_t j = 0; j < col; j++)
                {
                        printf("%10f, ", matrix[i * col + j]);
                }
		printf("\n");
        }

}























