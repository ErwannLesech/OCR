#ifndef LOAD_IMG_H
#define LOAD_IMG_H
float** init_img(char* path);
float** init_array(int height, int weight);
float calculate_pixel_with_suppression(int red, int green, int blue);
#endif