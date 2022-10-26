#include "load_img.h"
#include "canny_filter.h"
#include "display_img.h"
#include <stdio.h>
#include "hough_translate.h"
#include "utils.h"
#include "utils_hough_translate.h"

 void main(char* argv[], int argc) {
    // Load image
    unsigned char* img = init_img(argv[1]);
    // Convert to grayscale
    if (argv[2] == "gray") {
      surface_to_grayscale_and_black_white(img);
      display_img(img);
    }
    else if (argv[2] == "filter")
    {
      surface_to_grayscale_and_black_white(img);
      sobel_filter(img);
      display_img(img);
    }
    else if (argv[2] == "hough")
    {
      surface_to_grayscale_and_black_white(img);
      sobel_filter(img);
      display_img(img);
      change_mat(img,Hough(img));
    }  
 }