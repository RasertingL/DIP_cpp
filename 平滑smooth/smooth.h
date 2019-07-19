#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<math.h>

#define GRAY_LEVEL 8
#define WIDTH 10
#define HEIGHT 10
#define M_WIDTH 3
#define M_HEIGHT 3
#define M_PI 3.14159265358979323846

void MeanFilter(double *src, double *dst, int width,int height,int m_width,int m_height) ;
void MeanMask(double *mask,int width,int height);


void MedianFilter(double *src, double *dst, int width, int height, int m_width, int m_height) ;

void GaussianMask(double *mask,int width,int height,double deta);
void GaussianFilter(double *src, double *dst, int width, int height,int m_width,int m_height, double deta) ;

//卷积操作
void RealCOV(double *src, double *dst, double *mask,  int width, int height, int m_width, int m_height) ;