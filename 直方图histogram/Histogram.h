#include<iostream>
#include<stdlib.h>
#include<time.h>

#define GRAY_LEVEL 8
#define WIDTH 10
#define HEIGHT 10


//直方图均衡化
void HistogramEqualization(double *src, int *dst_map, int width, int height) ;

//初始化直方图
void initHistogram(int *hist) ;

//获取直方图
void GetHistogram(double *src, int *hist, int width, int height) ;


