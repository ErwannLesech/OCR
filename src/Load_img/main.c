#include "load_img.h"
#include "canny_filter.h"
#include "display_img.h"
#include <stdio.h>
#include "hough_translate.h"
#include "utils.h"
#include "utils_hough_translate.h"
#include "find_square.h"
#include "focus_grid.h"
#include "auto_rot.h"
#include "string.h"
#include "otsu.h"
#include <SDL2/SDL_image.h>
#include "contrast.h"


#include "load_img.h"
#include "canny_filter.h"
#include "display_img.h"
#include <stdio.h>
#include "hough_translate.h"
#include "utils.h"
#include "utils_hough_translate.h"
#include "find_square.h"
#include "focus_grid.h"
#include "auto_rot.h"
#include "string.h"
#include <SDL2/SDL_image.h>
#include "otsu.h"
#include <stdio.h>
void main_load(char* img_path)
{
    printf("+1");
   // IMG_Load(img_path);
    SDL_Surface * img = init_img(img_path);
    surface_to_grayscale_and_black_white(img);
    IMG_SavePNG(img, "grayscale.png");
    image_binarize(img);
    IMG_SavePNG(img, "binarization.png");
    sobel_filter(img);
    IMG_SavePNG(img, "sobel_filter.png");
    struct Lines l = Hough(img);
    change_mat(img, l);
    IMG_SavePNG(img, "hough.png");
    SDL_Surface * sdl = auto_rotate_img(init_img(img_path), (double)(auto_rot(l)));
    SDL_FreeSurface(img);
    IMG_SavePNG(sdl, "auto_rot.png");
    surface_to_grayscale_and_black_white(sdl);
    sobel_filter(sdl);
    struct Lines li = Hough(sdl);
    struct Squares sa = find_square(li, sdl->w, sdl->h);
    registerSurface(IMG_Load("auto_rot.png"), sa);
}

 /*void main(char* argv[], int argc) {
    // Load image
    //SDL_Surface* img = init_img("image_02.jpeg");
      SDL_Surface * sdl = rotate_img(init_img("image_04.jpeg"), (double)0); //(auto_rot(l)) 1 deg for img 6
    // Convert to grayscale
     //display_img(sdl);
     //add_128_contrast(sdl);
      //     display_img(sdl);

      surface_to_grayscale_and_black_white(sdl);
      //median_filter(sdl);
      image_binarize(sdl);
      sobel_filter(sdl);
      struct Lines l = Hough(sdl);
      printf("%i\n", auto_rot(l));
  //  for (size_t i = 0; i < l.size; i++)
   //   {
   //     printf("x,y coord: %i,%i, x,y coord_f: %i,%i\n", l.lines[i].x_start, l.lines[i].y_start, l.lines[i].x_end, l.lines[i].y_end);
   //   }
      change_mat(sdl, l);
      display_img(sdl);

      struct Squares sa = find_square(l, sdl->w, sdl->h);
        printf("x:a: %d, y:a: %d, x:c: %d, y:c: %d\n" ,sa.squares[0].pA.x, sa.squares[0].pA.y, sa.squares[0].pC.x, sa.squares[0].pC.y);
        printf("size of img: %d,%d\n", sdl->w, sdl->h);
      struct Point ps[4] = {sa.squares[0].pA,sa.squares[0].pB,sa.squares[0].pC,sa.squares[0].pD};
      struct Points p = {.size = 4, .points = ps};
     // draw_points(sdl,p);
      registerSurface(sdl, sa);
      display_img(sdl);
      /*SDL_Surface * sdl = rotate_img(init_img("image_04.jpeg"), (double)(auto_rot(l)));
      //display_img(sdl);
     // display_img(img);
      SDL_FreeSurface(img);
      surface_to_grayscale_and_black_white(sdl);
      //SDL_Surface * sdl_grayscale = 
      sobel_filter(sdl);
      struct Lines li = Hough(sdl);
      //struct Squares sa = find_square(li, 3*sdl->w/4, sdl->w);
      //registerSurface(sdl, sa);
      //display_img(sdl);
     // change_mat(sdl, li);
      //display_img(sdl);
     struct Squares sa = find_square(li, sdl->w);
    // for (size_t i = 0; i < li.size; i++)
     // {
      //  printf("x,y coord: %i,%i, x,y coord_f: %i,%i\n", l.lines[i].x_start, l.lines[i].y_start, l.lines[i].x_end, l.lines[i].y_end);
      //}
      printf("x:a: %d, y:a: %d, x:c: %d, y:c: %d\n" ,sa.squares[0].pA.x, sa.squares[0].pA.y, sa.squares[0].pC.x, sa.squares[0].pC.y);
      //struct Point ps[4] = {sa.squares[0].pA,sa.squares[0].pB,sa.squares[0].pC,sa.squares[0].pD};
     // struct Points p = {.size = 4, .points = ps};
    //  draw_points(sdl,p);
    
      printf("size of img: %d,%d\n", sdl->w, sdl->h);
     registerSurface(init_img("image_04.jpeg"), sa);
     // draw_squares(sdl, sa);
      //display_img(sdl);
      //registerSurface(init_img("image_03.jpeg"), s);
     // draw_points(img, find_intersections(Hough(img)));
      //change_mat(img, Hough(img));
      //display_img(img);
 }*/