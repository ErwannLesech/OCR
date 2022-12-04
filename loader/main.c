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

void all_treat(char* img_path)
{
    SDL_Surface * img = init_img(img_path);
    surface_to_grayscale_and_black_white(img);
    IMG_SavePNG(img, "grayscale.png");
    sobel_filter(img);
    IMG_SavePNG(img, "sobel_filter.bmp");
    struct Lines l = Hough(img);
    change_mat(img, l);
    IMG_SavePNG(img, "hough.bmp");
    SDL_Surface * sdl = rotate_img(init_img(img_path), (double)(auto_rot(l)));
    SDL_FreeSurface(img);
    IMG_SavePNG(sdl, "auto_rot.bmp");
    surface_to_grayscale_and_black_white(sdl);
    sobel_filter(sdl);
    struct Lines li = Hough(sdl);
    struct Squares sa = find_square(li, sdl->w);
    registerSurface(IMG_Load("auto_rot.bmp"), sa);
}


 void main(char* argv[], int argc) {
    // Load image
    SDL_Surface* img = init_img("image_04.jpeg");
    // Convert to grayscale

      surface_to_grayscale_and_black_white(img);
      sobel_filter(img);
      struct Lines l = Hough(img);
      printf("%i\n", auto_rot(l));
      SDL_Surface * sdl = rotate_img(init_img("image_04.jpeg"), (double)(auto_rot(l)));
      //display_img(sdl);
     // display_img(img);
      SDL_FreeSurface(img);
      surface_to_grayscale_and_black_white(sdl);
      //SDL_Surface * sdl_grayscale = 
      sobel_filter(sdl);
      struct Lines li = Hough(sdl);
    //  struct Squares sa = find_square(li, 3*sdl->w/4, sdl->w);
      //registerSurface(sdl, sa);
      //display_img(sdl);
     // change_mat(sdl, li);
      //display_img(sdl);
     struct Squares sa = find_square(li, sdl->w);
    /*  for (size_t i = 0; i < li.size; i++)
      {
        printf("x,y coord: %i,%i, x,y coord_f: %i,%i\n", l.lines[i].x_start, l.lines[i].y_start, l.lines[i].x_end, l.lines[i].y_end);
      }
      printf("x:a: %d, y:a: %d, x:c: %d, y:c: %d\n" ,sa.squares[0].pA.x, sa.squares[0].pA.y, sa.squares[0].pC.x, sa.squares[0].pC.y);*/
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
 }