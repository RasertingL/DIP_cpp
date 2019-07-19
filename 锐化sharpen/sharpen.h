#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<math.h>

#define GRAY_LEVEL 8
#define WIDTH 10
#define HEIGHT 10
#define M_WIDTH 3
#define M_HEIGHT 3
#define C 1


double Sobel(double *src, double *dst, int width, int height, int sobel_size) ;
