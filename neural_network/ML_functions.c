#include <math.h>
#include <stdio.h>

float sigmoid(float x)
{
	return 1 / (1 + expf(-x));
}

float sigmoid_derivative(float x)
{
	return sigmoid(x) *  (1 - sigmoid(x));
}

void multiply_matrix(double m1[][2], double m2[][2], size_t r1, size_t c1, size_t c2, double return_matrix[][2])
{
	for(size_t i = 0; i < r1; i++)
	{
		for(size_t j = 0; j < c2; j++)
		{
			for(size_t k = 0; k < c1; k++)
			{
				return_matrix[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}
}

double dot_product(double m1[][2], double m2[][2], size_t len)
{
	double product = 0;
 
 /*	for (size_t i = 0; i < len; i++)
 	{
		product += m1[i] * m2[i];
	}
*/
	return product;
}

float mean(float m1[][2], size_t len)
{
	float sum = 0;

	for(size_t i = 0; i < len; i++)
	{
		for(size_t j = 0; j < len; j++)
		{
			sum += m1[i][j];
		}
	}

	return sum / (len * len);

}

void print_matrix(float matrix[][2], size_t len)
{
	 for(size_t i = 0; i < len; i++)
        {
                for(size_t j = 0; j < len; j++)
                {
                        printf("%5f", matrix[i][j]);
                }
        }

}























