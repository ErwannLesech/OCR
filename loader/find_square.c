#include "find_square.h"
#include "math.h"

struct Points find_intersections(struct Lines lines){
    struct Point* points = malloc(sizeof(struct Point)*lines.size*lines.size);
    int i = 0;
    for(int j = 0; j < lines.size; j++){
        if((lines.lines[j].theta >=80 && lines.lines[j].theta <=100) || 
        (lines.lines[j].theta >=-10 && lines.lines[j].theta <=10) ){
        for(int k = 0; k < lines.size; k++){
            if(j != k && (lines.lines[k].theta >= 80 && lines.lines[k].theta <= 100) ||
            (lines.lines[k].theta >=-10 && lines.lines[k].theta <=10) ){
               double coef1 = (lines.lines[j].y_end - lines.lines[j].y_start) / (lines.lines[j].x_end - lines.lines[j].x_start);
               double coef2 = (lines.lines[k].y_end - lines.lines[k].y_start) / (lines.lines[k].x_end - lines.lines[k].x_start);
               double origord1 = lines.lines[j].y_start - coef1 * lines.lines[j].x_start;
               double origord2 = lines.lines[k].y_start - coef2 * lines.lines[k].x_start;
               if(coef1 != coef2){
                   points[i].x = (origord2 - origord1) / (coef1 - coef2);
                   points[i].y = coef1 * points[i].x + origord1;
                   i++;
               }
            }
        }
    }
    }
    struct Points points_struct = {points, i};
    return points_struct;
}

struct Squares find_square(struct Lines lines){
    struct Points points = find_intersections(lines);
    struct Square * square = malloc(sizeof(struct Square)*points.size);
    int a = 0;
    for (size_t i = 0; i < points.size; i++)
    {
        for (size_t j = 0; j < points.size; j++)
        {
            if(i == j){
                break;
            }
            int len = sqrt(pow(points.points[i].x - points.points[j].x, 2) + pow(points.points[i].y - points.points[j].y, 2));
            for (size_t k = 0; k < points.size; k++)
            {
                if(k == i || k == j){
                    break;
                }
                int len2 = sqrt(pow(points.points[i].x - points.points[k].x, 2) + pow(points.points[i].y - points.points[k].y, 2));
                if(abs(len-len2) < 10){
                    for (size_t l = 0; l < points.size; l++)
                    {
                        if(l == i || l == j || l == k){
                            break;
                        }
                        int len3 = sqrt(pow(points.points[i].x - points.points[l].x, 2) + pow(points.points[i].y - points.points[l].y, 2));
                        if(abs(len-len3) < 10){
                            square[a].pA = points.points[i];
                            square[a].pB = points.points[j];
                            square[a].pC = points.points[k];
                            square[a].pD = points.points[l];
                            square[a].len = len;
                            a++;
                        }
                    }
                }
            }
        }
        
    }
    struct Squares squares = {square, a};
    return squares;
}

