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

void main_load(char* img_path)
{
    SDL_Surface * img = init_img(img_path);
    surface_to_grayscale_and_black_white(img);
    IMG_SavePNG(img, "grayscale.png");
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
    struct Squares sa = find_square(li, sdl->w);
    registerSurface(IMG_Load("auto_rot.png"), sa);
}
