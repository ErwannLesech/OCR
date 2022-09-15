#include <math.h>

float sigmoid(float x)
{
	return 1 / (1 + expf(-x));
}

float sigmoid_derivative(float x)
{
	return sigmoid(x) *  (1 - sigmoid(x));
}

void multiply_matrix(double m1[][], double m2[][], size_t r1, size_t c1, size_t c2, double return_matrix[][])
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

