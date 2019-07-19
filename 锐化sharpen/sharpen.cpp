#include"sharpen.h"


/*
 实数矩阵的180度旋转，对于Sobel算子卷积核分解为两个1*n矩阵时使用
 */
void RotateRealMatrix(double *matrix,double *dst,int width,int height){
    double *temp = new double[width*height] ;

    for(int i=0;i<width*height;i++){
        dst[width*height-1-i]=matrix[i];
    }
}

//卷积操作
void RealCOV(double *src, double *dst, double *mask,  int width, int height, int m_width, int m_height){
    //double *Temp = new double[width * height] ;

    int mask_center_h = m_height / 2 ;
    int mask_center_w = m_width / 2 ;

    for(int i = 0 ; i < height ; i++ ){
        for(int j = 0 ; j < width ; j++ ){
            double value = 0.0 ;
            //确保不会越界
            if((i-mask_center_h)>=0 && (j-mask_center_w)>=0 &&(i+mask_center_h)<height && (j+mask_center_w)<width ){
            	for(int n = 0 ; n < m_height ; n++ ){
	                for(int m = 0 ; m < m_width ; m++ ){
						value += src[(i+n-mask_center_h)*width + (j+m-mask_center_w)] * mask[n*m_width+m] ;  
	                }
            	}
			}
            
            dst[i*width+j] = value ;
        }
    }
}

void RealConvolution(double *src,double *dst,double *mask, int width,int height,int m_width,int m_height){
    double *temp = new double[width * height] ;
    RotateRealMatrix(mask,temp,m_width,m_height);
    RealCOV(src, dst, temp, width, height, m_width, m_height);
}

//最简单的Sobel算子操作
double Sobel(double *src, double *dst, int width, int height, int sobel_size){
    //最后一个参数可以指定卷积核大小，这里我们实现一个为3的并且为别的留下接口便于后面扩展
    //这里可以直接定义简单的3*3的卷积核，也可以将其分成两个1*3的。
    //另外注意对于不同的大小的卷积核，其分解得到的1*n矩阵也不同

    double *dst_x = new double[width * height] ;
    double *dst_y = new double[width * height] ;

    if(sobel_size == 3){
        //double SobelMask_x[3]={-1,-2,-1,0,0,0,1,2,1};
        double SobelMask1[3] = {0.25, 0.5, 0.25} ;
        double SobelMask2[3] = {1, 0, -1} ;
        RealConvolution(src, dst_y, SobelMask2, width, height, 1, 3) ;
        RealConvolution(dst_y, dst_y, SobelMask1, width, height, 3, 1) ;

        RealConvolution(src, dst_x, SobelMask1, width, height, 1, 3);
        RealConvolution(dst_x, dst_x, SobelMask2, width, height, 3, 1);
    }
    // else if(sobel_size==5){
    //     double SobelMask1[5]={1/16.,4/16.,6/16.,4/16.,1/16.};
    //     double SobelMask2[5]={1/3.,2/3.,0,-2/3.,-1/3.};
    //     RealConvolution(src, dst_x, SobelMask1, width, height, 1, 5);
    //     RealConvolution(dst_x, dst_x, SobelMask2, width, height, 5, 1);
        
    //     RealConvolution(src, dst_y, SobelMask2, width, height, 1, 5);
    //     RealConvolution(dst_y, dst_y, SobelMask1, width, height, 5, 1);
    
    // }else if(sobel_size==7){
    //     double SobelMask1[7]={1/64.,6/64.,15/64.,20/64.,15/64.,6/64.,1/64.};
    //     double SobelMask2[7]={0.1,0.4,0.5,0,-0.5,-0.4,-0.1};
    //     RealConvolution(src, dst_x, SobelMask1, width, height, 1, 7);
    //     RealConvolution(dst_x, dst_x, SobelMask2, width, height, 7, 1);
        
    //     RealConvolution(src, dst_y, SobelMask2, width, height, 1, 7);
    //     RealConvolution(dst_y, dst_y, SobelMask1, width, height, 7, 1);
        
    // }
    for(int i = 0 ; i < height ; i++ ){
        for(int j = 0 ; j < width ; j++ ){
            dst[i*width+j] = abs(dst_x[i*width+j]) + abs(-dst_y[i*width+j]) ; 
        }
    }
}


int main(){
    srand( (unsigned)time( NULL ) ) ;
	double *src = new double[WIDTH * HEIGHT] ;
    double *dst = new double[WIDTH * HEIGHT] ;
	for(int i = 0 ; i < WIDTH * HEIGHT ; i++ ){
		src[i] = (int)rand() % GRAY_LEVEL ;
		std::cout << src[i] << " " ;
	}
	std::cout << std::endl << std::endl ;

    for(int i = 0 ; i < HEIGHT ; i++){
        for(int j = 0 ; j < WIDTH ; j++ ){
            std::cout << src[i * WIDTH + j] << " " ;
        }
        std::cout << std::endl ;
    }
    std::cout << std::endl ;

    Sobel(src, dst, WIDTH, HEIGHT, 3) ;
    for(int i = 0 ; i < HEIGHT ; i++ ){
        for(int j = 0 ; j < WIDTH ; j++ ){
            dst[i*WIDTH+j] = src[i*WIDTH+j] + C*dst[i*WIDTH+j] ;
        }
    }


    std::cout << std::endl << std::endl ;

    for(int i = 0 ; i < HEIGHT ; i++){
        for(int j = 0 ; j < WIDTH ; j++ ){
            std::cout << dst[i * WIDTH + j] << " " ;
        }
        std::cout << std::endl ;
    }
}
