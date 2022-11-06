#include "utils.h"
#include "hough_translate.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//
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
int** init_array_i(int m, int n)
{
   int* values = calloc(m*n, sizeof(int));
    int** rows = malloc(m*sizeof(int*));
    for (int i=0; i<m; ++i)
    {
        rows[i] = values + i*n;
    }
    return rows;
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

void print_array_i(int** arr, int height, int weight)
{
    printf("[");
    for(int i=0; i<height; i++) {
         printf("["); 
    for(int j=0; j<weight; j++) {
      printf("%i; ", arr[i][j]);
    }
    printf("],\n"); // new line
  }
  printf("]\n");
}

void print_array_1D(int* arr, int weight)
{
    printf("[");
    for(int j=0; j<weight; j++) {
      printf("%i; ", arr[j]);
    }
    printf("],\n"); // new line
}

int RGBToint(float gray){
    return ((int)gray);
}


double degrees_ToRadians(double degrees)
{
    return degrees * M_PI/ 180.0;
}

double radian_To_Degree(double radian)
{
    return radian * 180.0 / M_PI;
}

void sort_Lines(struct Line* lines, int size){

  int index = 0;
  struct Line tmp;
  for (int i=0; i < (size-1); i++)
  {
    index = i;
   
    for (int j=i + 1; j < size; j++)
    {
      if (lines[index].val < lines[j].val)
        index = j;
    }
    if (index != i)
    {
      tmp = lines[i];
      lines[i] = lines[index];
      lines[index] = tmp;
    }
  }
}