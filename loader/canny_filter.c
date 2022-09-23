#include "canny_filter.h"
#include <stddef.h>
#include "array_utils.h"
float gaussian_kernel[5][5] = {{1.0, 4.0,  6.0,  4.0 , 1.0 },
                   {4.0 , 16.0 , 24.0 , 16.0 , 4.0 },
                   {6.0 , 24.0 , 36.0 , 24.0 , 6.0 },
                   {4 , 16 , 24 , 16 , 4 },
                   {1 , 4  ,  6 ,  4 , 1 }};

void filter(float** mat, int w, int h){
    for (size_t x = 2; x < w-2; x++)
    {
        for (size_t y = 2; y < h-2; y++)
        {
            for (size_t i = 0; i < 5; i++)
            {
                for (size_t j = 0; j < 5; j++)
                {            
                    mat[y+i-2][x+j-2] = (mat[y+i-2][x+j-2])* (gaussian_kernel[i][j])*3;
                }
            }
        }
    }
    print_array(mat, w, h);
}