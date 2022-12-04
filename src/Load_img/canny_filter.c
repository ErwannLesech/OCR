#include "canny_filter.h"
#include <stddef.h>
#include "utils.h"
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

float gaussian_kernel[5][5] = {{1.0, 4.0,  6.0,  4.0 , 1.0 },
                   {4.0 , 16.0 , 24.0 , 16.0 , 4.0 },
                   {6.0 , 24.0 , 36.0 , 24.0 , 6.0 },
                   {4.0 , 16.0 , 24.0 , 16.0 , 4.0 },
                   {1.0 , 4.0  ,  6.0 ,  4.0 , 1.0 }};

void filter(SDL_Surface* sdl_surface){
 SDL_LockSurface(sdl_surface);
  Uint32* pixels = sdl_surface->pixels;
    for (int x = 2; x < sdl_surface->w-2; x++)
    {
        for (int y = 2; y < sdl_surface->h-2; y++)
        {
            float red = 0;
            float green = 0;
            float blue = 0;
            for (size_t i = 0; i < 5; i++)
            {   
                for (size_t j = 0; j < 5; j++)
                {  
                    int xn = x + i - 2;
                    int yn = y + j - 2;  
                    Uint32 RGB = (Uint32)pixels[yn*(sdl_surface->w) + xn];
                    Uint8 r, g, b;
                    SDL_GetRGB(RGB, sdl_surface->format, &r, &g, &b);
                    red += ((float)r)*((gaussian_kernel[i][j])/256.0);
                    green += ((float)g)*((gaussian_kernel[i][j])/256.0);      
                    blue+= ((float)b)*((gaussian_kernel[i][j])/256.0);
                    
                }
            }
           
            Uint32 color = SDL_MapRGB(sdl_surface->format, 
                (Uint8)red,(Uint8) green,(Uint8) blue);
            pixels[y*(sdl_surface->w) + x] = color;
        }
    }
     SDL_UnlockSurface(sdl_surface);

   // print_array(mat, h, w);
}

int RGB_To_Int(Uint32 pixel, SDL_PixelFormat* format){
     Uint8 r, g, b;
    SDL_GetRGB(pixel, format, &r, &g, &b);
    return ((int)r+ (int)g + (int) b )/3;
}

/*void sobel_filter(SDL_Surface* sdl_surface){
     SDL_LockSurface(sdl_surface);
      Uint32* pixels = sdl_surface->pixels;
      SDL_PixelFormat* format = sdl_surface->format;
    double maxgradient = -1;
    int** edge_colors = init_array_i(sdl_surface->h,sdl_surface->w);
    for (size_t x = 1; x < sdl_surface->w-1; x++)
    {
        for (size_t y = 1; y < sdl_surface->h-1; y++)
        {
           
            int gx = -RGB_To_Int(pixels[(y-1)*(sdl_surface->w) + (x-1)], format) + RGB_To_Int(pixels[(y-1)*(sdl_surface->w) + (x+1)], format)
            + (-2) * RGB_To_Int((pixels[y*(sdl_surface->w)  + (x-1)]), format) + 2*(RGB_To_Int(pixels[y*(sdl_surface->w) +(x+1)],format))
            -RGB_To_Int(pixels[(y+1)*(sdl_surface->w)  + (x-1)],format) + RGB_To_Int(pixels[(y+1)*(sdl_surface->w)  + (x+1)], format);

            int gy = (-RGB_To_Int(pixels[(y-1)*(sdl_surface->w) + (x-1)], format) - RGB_To_Int(pixels[(y-1)*(sdl_surface->w) + (x+1)], format) 
            + ((-2) * RGB_To_Int(pixels[(y-1)*(sdl_surface->w)  + x], format)))
            + (RGB_To_Int(pixels[(y+1)*(sdl_surface->w) +(x-1)], format)+(2*(RGB_To_Int(pixels[(y+1)*(sdl_surface->w)  + x], format)))
             + RGB_To_Int(pixels[(y+1)*(sdl_surface->w) +(x+1)], format));
        
            double g = sqrt(gx*gx + gy*gy);//gx+gy;
            if (g > maxgradient)
            {
                maxgradient = g;
            }
            edge_colors[y][x] = (int)g;
        }
    }
    //print_array_i(edge_colors, h,w);
    //double scale = 255.0/maxgradient;
      for (size_t x = 1; x < sdl_surface->w-1; x++)
    {
        for (size_t y = 1; y < sdl_surface->h-1; y++)
        {
            
            Uint8 edge_color = (Uint8)(edge_colors[y][x]);
            ((int)scale);
            if (edge_colors[y][x] != 0)
            {
                 pixels[y*(sdl_surface->w) +x] = SDL_MapRGB(format, 255, 255, 255);
            }
            
            pixels[y*(sdl_surface->w) +x] = SDL_MapRGB(format, edge_color, edge_color, edge_color);
        }
    }
    SDL_UnlockSurface(sdl_surface);
}*/

 double kernel_x[3][3] = { { -1.0, 0.0, 1.0 },
                              { -2.0, 0.0, 2.0 },
                              { -1.0, 0.0, 1.0 } };

    double kernel_y[3][3] = { { -1.0, -2.0, -1.0 },
                              { 0.0, 0.0, 0.0 },
                              { 1.0, 2.0, 1.0 } };

double Convolution(SDL_Surface * image, double kernel[3][3], int row, int col)
{
    Uint32 *pixels = image->pixels;
    double sum = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int x = i + row;
            int y = j + col;
            if (x >= 0 && y >= 0 && x < (int)image->w
                && y < (int)image->h)
            {
                Uint8 r,g,b;
                SDL_GetRGB(pixels[y*(image->w) + x], image->format, &r,&g,&b);
                sum += r * kernel[i][j];
            }
        }
    }

    return sum;
}

void sobel_filter(SDL_Surface *image)
{
    SDL_LockSurface(image);
    double gx, gy;
    double g_px;
    Uint32 *pixels = image->pixels;

    double kernel_x[3][3] = { { -1.0, 0.0, 1.0 },
                              { -2.0, 0.0, 2.0 },
                              { -1.0, 0.0, 1.0 } };

    double kernel_y[3][3] = { { -1.0, -2.0, -1.0 },
                              { 0.0, 0.0, 0.0 },
                              { 1.0, 2.0, 1.0 } };

    const unsigned int height = image->h;
    const unsigned int width = image->w;
    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = 0; j < width; j++)
        {
            gx = Convolution(image, kernel_x, j, i);
            gy = Convolution(image, kernel_y, j, i);
            g_px = sqrt(gx * gx + gy * gy);

           if (g_px > 128)
           {
                pixels[i*(image->w) + j] = SDL_MapRGB(image->format, 
                    255,255,255);
           }
           else{
                pixels[i*(image->w) + j] = SDL_MapRGB(image->format, 0,0,0);
           }
           
        }
    }
    SDL_UnlockSurface(image);
}