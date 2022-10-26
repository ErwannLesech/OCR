#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H
#include "utils_hough_translate.h"
float** init_array(int m, int n);
void destroy_array(unsigned int** arr);
void print_array(float** arr,  int height, int weight);
int RGBToint(float gray);
float calculate_pixel_with_suppression(int red, int green, int blue);
float calculate_pixel_f(float red, float green, float blue);
int** init_array_i(int m, int n);
void print_array_i(int** arr, int height, int weight);
void print_array_1D(int* arr, int weight);
double degrees_ToRadians(double degrees);
double radian_To_Degree(double radian);
void sort_Lines(struct Line* lines, int size);
#endif