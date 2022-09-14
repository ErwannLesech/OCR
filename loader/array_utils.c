#include "array_utils.h"
#include <stdio.h>
#include <stdlib.h>
//hauteur, largeur
float** init_array(int m, int n)
{
    float* values = calloc(m*n, sizeof(float));
    float** rows = malloc(m*sizeof(float*));
    for (int i=0; i<m; ++i)
    {
        rows[i] = values + i*n;
    }
    return rows;
}

void destroy_array(unsigned int** arr)
{
   /* free(*arr);
    free(arr);*/
}
void print_array(float** arr, int height, int weight)
{
    printf("[");
    for(int i=0; i<height; i++) {
         printf("["); 
    for(int j=0; j<weight; j++) {
      printf("%f; ", arr[i][j]);
    }
    printf("],\n"); // new line
  }
  printf("]\n");
}