#include "load_img.h"
#include "canny_filter.h"
#include "display_img.h"
#include <stdio.h>
#include "hough_translate.h"
#include "utils.h"
#include "utils_hough_translate.h"
#include "find_square.h"
#include "focus_grid.h"

 void main(char* argv[], int argc) {
    // Load image
    SDL_Surface* img = init_img("image_03.jpeg");
    // Convert to grayscale

      surface_to_grayscale_and_black_white(img);
      sobel_filter(img);
      struct Squares s = find_square(Hough(img), 3*img->w/4, img->w);
      //draw_squares(img, s);
      registerSurface(init_img("image_03.jpeg"), s);
     // draw_points(img, find_intersections(Hough(img)));
      //change_mat(img, Hough(img));
     // display_img(focus_grid(init_img("image_03.jpeg"), s));
 }