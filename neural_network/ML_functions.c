#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float sigmoid(float x)
{
	return 1 / (1 + expf(-x));
}

float sigmoid_derivative(float x)
{
	return sigmoid(x) *  (1 - sigmoid(x));
}

void multiply_matrix(float m1[], float m2[], size_t r1, size_t c1, size_t c2, float return_matrix[])
{
	for(size_t i = 0; i < r1; i++)
	{
		for(size_t j = 0; j < c2; j++)
		{
			for(size_t k = 0; k < c1; k++)
			{
				return_matrix[i * c2 + j] += m1[i * c1 + k] * m2[k * c2 + j]; 
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

float mean(float m1[][2], size_t row, size_t col)
{
	float sum = 0;

	for(size_t i = 0; i < row; i++)
	{
		for(size_t j = 0; j < col; j++)
		{
			sum += m1[i][j];
		}
	}

	return sum / (row * col);

}

void print_matrix(float matrix[], size_t row, size_t col)
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























