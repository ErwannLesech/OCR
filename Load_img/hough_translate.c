#include "hough_translate.h"
#include "utils_hough_translate.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "display_img.h"

double radian_To_Degrees(double degre){
    return degre/ (180/3.14);
}

struct Equation{
    float theta;
    float rho;
    int val;
};

struct Accum_in_mat{
    struct Equation* accums;
    int size;
};

struct Line make_line(double theta, double rho, int w, int h, int val){
      int houghHeight = (int) (sqrt(2) * fmax(h, w)) / 2; 

    // Find edge points and vote in array 
    float centerX = w / 2; 
    float centerY = h / 2; 

    // Draw edges in output array 
    double tsin = sin(theta); 
    double tcos = cos(theta); 

    if (theta < M_PI * 0.25 || theta > M_PI * 0.75) { 
      int x1=0, y1=0;
      int x2=0, y2=h-1;

      x1=(int) ((((rho - houghHeight) - ((y1 - centerY) * tsin)) / tcos) + 
            centerX);
      x2=(int) ((((rho - houghHeight) - ((y2 - centerY) * tsin)) / tcos) + 
            centerX);

struct Line line = { .x_start = x1, .y_start = y1, .x_end = x2, .y_end = y2, 
        .val = val};
    return line;
    }
    else {
        int x1=0, y1=0;
        int x2=w-1, y2=0;

        y1=(int) ((((rho - houghHeight) - ((x1 - centerX) * tcos)) / tsin) + 
            centerY); 
        y2=(int) ((((rho - houghHeight) - ((x2 - centerX) * tcos)) / tsin) + 
            centerY); 
        struct Line line = { .x_start = x1, .y_start = y1, .x_end = x2, 
            .y_end = y2, .val = val};
    return line;
}
}
    


struct Accum_in_mat** Matrix(int h, int w){
    struct Accum_in_mat **t = (struct Accum_in_mat **)malloc(h * 
        sizeof(struct Accum_in_mat *));
for (size_t i = 0; i < h; ++i)
    t[i] = (struct Accum_in_mat *)malloc(w * sizeof(struct Accum_in_mat));

return t;
}


struct Lines Hough(SDL_Surface *sdl_surface){

      const double diagonal = (int) (sqrt(2) * 
        fmax(sdl_surface->h, sdl_surface->w)) / 2; 
    int ** accum_mat = init_array_i(2*diagonal+1,180); 
    SDL_LockSurface(sdl_surface);
    double *saveCos = calloc(181, sizeof(double));
    double *saveSin = calloc(181, sizeof(double));

      int max = 0;
     for (int theta = 0; theta < 180 ; theta++)
    {
        double real_theta = (M_PI/180)*(double)theta;
        saveCos[theta] = cos(real_theta);
        saveSin[theta] = sin(real_theta);
    }
    int centerX =sdl_surface->w / 2; 
    int centerY = sdl_surface->h/ 2; 
    //printf("%f\n",saveCos[1000]);
    Uint32 * pixels = (sdl_surface->pixels);
    int num_points = 0;
  
   
        for (int y = 0; y < sdl_surface->h; y++)
        {
        for (int x = 0; x < sdl_surface->w; x++)
        {
            int i = 0;
           Uint8 r,g,b;
           SDL_GetRGB(pixels[y*(sdl_surface->w) + x], 
                sdl_surface->format, &r, &g,&b);
            if (r ==255)
            {
                //printf("+1\n");
                for (int theta = 0; theta < 180; theta++)
                {
                    double rho = (x-centerX)*saveCos[theta]+ 
                        (y-centerY)*saveSin[theta];
                    int rrho = (int)rho + diagonal;
                    //printf("%i\n", rho);
                    if (r < 0 || r >= 2*diagonal)
                    {
                        continue;
                    }
                    accum_mat[rrho][theta]++;
                    if (accum_mat[rrho][theta] > max )
                    {
                     //   printf("%i,%i,%i,%f, %f, %f\n", x, y, theta, rho, saveCos[theta], saveSin[theta]);
                        max = accum_mat[rrho][theta];
                    }
                    
                }
                num_points++;
            }
        }
    }
    free(saveCos);
    free(saveSin);
    
    //print_array_i(accum_mat, 2*diagonal+1, 2*diagonal+1);
    int pic =  (int)((double)max*0.42);
    printf("max:%i\n",max);
    struct Line *lines = malloc(2*diagonal*2*diagonal*sizeof(struct Line));
    int e = 0;
    if (num_points == 0)
    {
        struct Lines linnes = {.lines = lines, .size = e};
        return linnes;
    }
    
    for (size_t t = 0; t < 180; t++)
    {
        
        for (int r = 4; r < 2*diagonal -4 ; r++)
        {
            int ismax = 0;
            if(accum_mat[r][t] >= pic){
                int val = accum_mat[r][t];
            for (int dx = -4; dx <= 4 && ismax ==0; dx++) {
                for (int dy = -4; dy <= 4 && ismax ==0;dy++) { 
                    int dt = t + dx; 
                    int dr = r + dy; 
                    if (dt < 0) dt = dt + 180; 
                    else if (dt >= 180) dt = dt - 180; 
                    if (accum_mat[dr][dt] > val || ismax == 1) { 
                        ismax = 1;
              }
            }
          } 
          if (ismax == 0)
          {
              double theta = t * (M_PI/180);
        //printf("%i, %f\n", r,theta); 
        //struct Line ligne = make_line(theta, r, sdl_surface->w, sdl_surface->h, val);
             lines[e] = make_line(theta, r, sdl_surface->w, sdl_surface->h, 
                val);
            e++;
            }
            }
        }
    }
sort_Lines(lines, e);
    for (size_t j = 0; j < e; j++)
    {
        struct Line line = lines[j];
      
      printf("x:%i,%i and y:%i,%i, val = %i \n", line.x_start, line.x_end, 
            line.y_start, line.y_end,line.val);
    }
    
    struct Lines linnes = {.lines = lines, .size = e};
     SDL_UnlockSurface(sdl_surface);
    return linnes;

}
