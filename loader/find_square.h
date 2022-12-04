#pragma once
#include "hough_translate.h"
#include "utils_hough_translate.h"
#include "utils.h"
#include <SDL2/SDL.h>


struct Point{
    int x;
    int y;
};

struct Square {
    struct Point pA;
    struct Point pB;
    struct Point pC;
    struct Point pD;
    int len;
};

struct Points{
    struct Point* points;
    int size;
};

struct Squares{
    struct Square* squares;
    int size;
};

struct Squares find_square(struct Lines lines, int max_size);
//struct Points find_intersections(struct Lines lines);