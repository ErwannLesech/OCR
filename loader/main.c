#include "load_img.h"
#include "canny_filter.h"
#include "display_img.h"
#include <stdio.h>
#include "hough_translate.h"
#include "utils.h"
#include "utils_hough_translate.h"

 int main(){
   //printf("TEST");
      SDL_Surface* image = init_img("image_01.jpeg");
      //SDL_Surface* image = init_img("rectangle2.png");

   
    surface_to_grayscale_and_black_white(image);
   //print_array(image.array, image.height, image.width);
    //filter(image);
   
    sobel_filter(image);
    //Hough(image);
    change_mat(image,Hough(image));
    display_img(image);
    
    return 0;
 }