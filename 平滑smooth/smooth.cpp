#include"smooth.h"

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

//均值滤波器模板生成
void MeanMask(double *mask,int width,int height){
    double meanvalue = 1.0/(width * height) ;
    for(int i = 0 ; i < width * height ; i++ ){
        mask[i] = meanvalue ;
    }
}

void MeanFilter(double *src, double *dst, int width,int height,int m_width,int m_height){
    double *mask = new double[width * height] ;
    MeanMask(mask, m_width, m_height) ;
    RealCOV(src, dst, mask,  width, height, m_width, m_height) ; 
}


//高斯滤波器模板生成
void GaussianMask(double *mask,int width,int height,double deta){
    double deta_2 = deta * deta ;
    double mask_center_h = (double)height / 2 - 0.5 ; 
    double mask_center_w = (double)width / 2 - 0.5 ;
    double param = 1.0 / (2 * M_PI * deta_2) ;

    double sum = 0.0 ;

    for(int i = 0 ; i < height ; i++){
        for(int j = 0 ; j < width ; j++){
            double distance = sqrt((j-mask_center_w)*(j-mask_center_w)+(i-mask_center_h)*(i-mask_center_h)) ;
            mask[i * width + j] = param * exp(-(distance*distance)/(2*deta_2)) ;
            sum += mask[i * width + j] ;
        }
    }

    for(int i = 0 ; i < height * width ; i++){
        mask[i] /= sum ;
    }


}

void GaussianFilter(double *src, double *dst, int width, int height,int m_width,int m_height, double deta){
    double *mask = new double[width * height] ;
    GaussianMask(mask, m_width, m_height, deta) ;
    RealCOV(src, dst, mask,  width, height, m_width, m_height) ; 

}


//中值滤波器
void MedianFilter(double *src, double *dst, int width, int height, int m_width, int m_height){
    int mask_center_h = m_height / 2 ;
    int mask_center_w = m_width / 2 ;

    for(int i = 0 ; i < height ; i++ ){
        for(int j = 0 ; j < width ; j++ ){
            double value = 0.0 ;
            //确保不会越界
            if((i-mask_center_h)>=0 && (j-mask_center_w)>=0 &&(i+mask_center_h)<height && (j+mask_center_w)<width ){
                //对从src[(i-mask_center_h)*width+(j-mask_center_w)]开始的m_height*m_width个元素进行排序取中值
                int index = 0 ;
                double *sort = new double[m_width * m_height] ;
            	for(int n = 0 ; n < m_height ; n++ ){
	                for(int m = 0 ; m < m_width ; m++ ){
						sort[index] = src[(i+n-mask_center_h)*width + (j+m-mask_center_w)] ;
                        index ++ ;
	                }
            	}
                for(int n = 0 ; n < index-1 ; n++){
                    for(int m = 0 ; m < index-1-n ; m++){
                        if(sort[m] > sort[m+1]){
                            double temp_sort = sort[m] ;
                            sort[m] = sort[m+1] ;
                            sort[m+1] = temp_sort ;
                        }
                    }
                }
                value = sort[index/2] ;
			}
            
            dst[i*width+j] = value ;
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

    //均值滤波
    MeanFilter(src, dst, WIDTH, HEIGHT, M_WIDTH, M_HEIGHT) ;
    for(int i = 0 ; i < HEIGHT ; i++){
        for(int j = 0 ; j < WIDTH ; j++ ){
            std::cout << dst[i * WIDTH + j] << " " ;
        }
        std::cout << std::endl ;
    }

    //高斯滤波
    GaussianFilter(src, dst, WIDTH, HEIGHT, M_WIDTH, M_HEIGHT, 1) ;
    for(int i = 0 ; i < HEIGHT ; i++){
        for(int j = 0 ; j < WIDTH ; j++ ){
            std::cout << dst[i * WIDTH + j] << " " ;
        }
        std::cout << std::endl ;
    }

    //中值滤波(排序那里有点暴力。。。可能不够快)
    MedianFilter(src, dst, WIDTH, HEIGHT, M_WIDTH, M_HEIGHT) ;
    for(int i = 0 ; i < HEIGHT ; i++){
        for(int j = 0 ; j < WIDTH ; j++ ){
            std::cout << dst[i * WIDTH + j] << " " ;
        }
        std::cout << std::endl ;
    }
}
