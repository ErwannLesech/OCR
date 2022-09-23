#include "load_img.h"
#include "img.h"
#include "canny_filter.h"
#include "display_img.h"
#include <stdio.h>
 int main(){
   //printf("TEST");
   struct img image = init_img("image_03.jpeg");
   
    filter(image.array, image.width, image.height);
    display_img(image.array,  image.height, image.width);
    return 0;
 }