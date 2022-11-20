#include "find_square.h"
#include "math.h"
#include <stdio.h>
struct Point find_intersection(struct Line line1, struct Line line2){
    double coef1 = -1;
    double coef2 = -1;
    if (line1.x_end - line1.x_start != 0)
    {
        coef1 = (line1.y_end - line1.y_start) / line1.x_end - line1.x_start;
    }
    if (line2.x_end - line2.x_start != 0)
    {
        coef2 = (line2.y_end - line2.y_start) / line2.x_end - line2.x_start;
    }
    if (coef1 != coef2)
    {
       struct Point point;
       double origord1 = line1.y_start - coef1 * line1.x_start;
       double origord2 = line2.y_start - coef2 * line2.x_start;
       if (coef1 == -1)
       {
            point.x = line1.x_start;
            point.y = coef2 * point.x + origord2;
       }
       else if (coef2 == -1)
       {
          point.x = line2.x_start;
          point.y = coef1 * point.x + origord1;
       }
       else
       {
          point.x = (origord2 - origord1) / (coef1 - coef2);
          point.y = coef1 * point.x + origord1;
       }
       return point;
       
    }
    struct Point P = {.x = -1};
    return P;
    
}
int dist(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int isSquare(struct Square square){
    int l1 = dist(square.pA.x, square.pA.y, square.pB.x, square.pB.y);
    int l2 = dist(square.pB.x, square.pB.y, square.pC.x, square.pC.y);
    int l3 = dist(square.pC.x, square.pC.y, square.pD.x, square.pD.y);
    int l4 = dist(square.pA.x, square.pA.y, square.pD.x, square.pD.y);  
    int max = l1;
    int min = l2;
    if (l2 > max)
    {
        max = l2;
    }
    if(l3 > max){
        max = l3;
    }
    if(l4 > max){
        max = l4;
    }
    if (l1 < min)
    {
        min = l1;
    }
    if (l3 < min)
    {
        min = l3;
    }
    if (l4 < min)
    {
        min = l4;
    }
    if (abs(max - min) > 5)
    {
        return 0;
    }
    return 1;
    
}

struct Squares simplify_squares(struct Squares squares){
    int a = 0;
    int maxl = 0;
    struct Square * squaress = malloc(sizeof(struct Square) * squares.size);
    for (size_t i = 0; i < squares.size; i++)
    {
        if (maxl < squares.squares[i].len)
        {
            maxl = squares.squares[i].len;
        }
    }
    for (size_t i = 0; i < squares.size; i++)
    {
        if (maxl == squares.squares[i].len)
        {
            squaress[a] = squares.squares[i];
            a++;
        }
    }
    struct Squares s = {.squares = squaress, .size = a};
    return s;
}


struct Squares find_square(struct Lines lines, int min_size, int max_size){
    int a = 0;
     struct Square * squares = malloc(sizeof(struct Square)*30000);
    for (size_t i = 0; i < lines.size; i++)
    {
        if (lines.lines[i].theta >= 80 && lines.lines[i].theta <=100 
        ||(lines.lines[i].theta >= -10 && lines.lines[i].theta <=10 ) )
        {
            for (size_t j = 0; j < lines.size; j++)
            {
                if(i == j)
                {
                    continue;
                }
                if (lines.lines[j].theta >= 80 && lines.lines[j].theta <=100 
        ||(lines.lines[j].theta >= -10 && lines.lines[j].theta <=10 ) )
            {
                struct Point pB = find_intersection(lines.lines[i], lines.lines[j]);
                if (pB.x != -1)
                {
                    for (size_t k = 0; k < lines.size; k++)
                    {
                    if(k == j || k == i)
                    {
                        continue;
                    }
                        if (lines.lines[k].theta >= 80 && lines.lines[k].theta <=100 
        ||(lines.lines[k].theta >= -10 && lines.lines[k].theta <=10))
                        {
                            struct Point pC = find_intersection(lines.lines[k], lines.lines[j]);
                            if(pC.x != -1)
                            {
                                for (size_t l = 0; l < lines.size; l++)
                                {
                                    if(l == j || k == l || l == i)
                                    {
                                        continue;
                                    }
                                     if (lines.lines[l].theta >= 80 && lines.lines[l].theta <=100 
        || (lines.lines[l].theta >= -10 && lines.lines[l].theta <=10))
                                    {
                                        struct Point pD = find_intersection(lines.lines[k], lines.lines[l]);
                                        struct Point pA = find_intersection(lines.lines[l], lines.lines[i]);
                                        struct Square square = {.pA = pA, .pB = pB, .pC = pC, .pD = pD, .len = dist(square.pA.x, square.pA.y, square.pB.x, square.pB.y)};
                                        if (pD.x != -1 && pA.x != -1 && isSquare(square) == 1)
                                        {
                                       /* printf("x:a: %d, b: %d, c: %d, d: %d\n" ,pA.x, pB.x, pC.x, pD.x);
                                        printf("y:a: %d, b: %d, c: %d, d: %d\n", pA.y, pB.y, pC.y, pD.y);  */                          
                           
                                            squares[a] = square;
                                            a++;
                                        }
                                        
                                    }
                                }
                                
                            }
                        }
                    }   
                }   
            }
        }
    }
    }
    
    struct Squares s = {.squares = squares, .size = a};
    struct Squares simp = simplify_squares(s);
    free(squares);
    printf("%i\n",simp.size);
    return simp;
}