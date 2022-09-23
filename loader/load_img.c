#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "load_img.h"
#include "array_utils.h"
#include "display_img.h"

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

switch (bpp)
{
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
      }
}

float** init_img(char* path){
   SDL_Surface * sdl_surface = IMG_Load(path);
   SDL_LockSurface(sdl_surface);
   
   Uint8 *q = (Uint8 *) sdl_surface -> pixels;
   float** array = init_array(sdl_surface->h, sdl_surface->w);
   for (int x = 0; x < sdl_surface->w; x++)
   {
      for (size_t y = 0; y < sdl_surface->h; y++)
      {
         SDL_Color rgb;
      Uint32 data = getpixel(sdl_surface, x, y);
      SDL_GetRGB(data, sdl_surface->format, &rgb.r, &rgb.g, &rgb.b);
        array[y][x] = calculate_pixel_with_suppression(rgb.r, rgb.g, rgb.b);
      }
   }
    display_img(array, sdl_surface->h, sdl_surface->w);
    SDL_UnlockSurface(sdl_surface);
    return array;
   
}


float calculate_pixel_with_suppression(int red, int green, int blue){
   float pixel = ( ((float)red)/255.0f + ((float)green)/255.0f + ((float)blue)/255.0f)/3;
   if (pixel <0.3f)
   {
      return 0.0f;
   }
   if (pixel > 0.7f)
   {
      return 1.0f;
   }

   return pixel;
}
//height = hauteur width = largeur
