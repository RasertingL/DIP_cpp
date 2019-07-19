#include"Histogram.h"

//直方图初始化操作
void initHistogram(int *hist){
	for(int i = 0 ; i < GRAY_LEVEL ; i++){
		hist[i] = 0 ;
	}
}

//获得图片对应直方图
void GetHistogram(double *src, int *hist, int width, int height){
	initHistogram(hist) ;
	for(int i = 0 ; i < height ; i++ ) {
		for(int j = 0 ; j < width ; j++ ){
			int temp = src[i*width + j] ;
			hist[temp] ++ ;
		}
	}
}

//直方图均衡化
void HistogramEqualization(double *src, int *dst_map, int width, int height){
	int total = 0 ;
	int *hist = new int[GRAY_LEVEL] ;
	GetHistogram(src, hist, width, height) ;

	int *Temp_hist = new int[GRAY_LEVEL] ;
	initHistogram(Temp_hist) ;

	Temp_hist[0] = hist[0] ; 
	total = hist[0] ;

	for(int i = 1 ; i < GRAY_LEVEL ; i ++){
		Temp_hist[i] = Temp_hist[i - 1] + hist[i] ;
		total += hist[i] ;
	}

	for(int i = 0 ; i < GRAY_LEVEL ; i++ ){
		dst_map[i] = (int)((GRAY_LEVEL - 1) * ((double)Temp_hist[i] / (double)total)) ;
	}
}



int main(){
	srand( (unsigned)time( NULL ) ) ;
	double *src = new double[WIDTH * HEIGHT] ;
	for(int i = 0 ; i < WIDTH * HEIGHT ; i++ ){
		src[i] = (int)rand() % GRAY_LEVEL ;
		std::cout << src[i] << " " ;
	}
	std::cout << std::endl << std::endl ;

	//获得直方图
	int *hist = new int [GRAY_LEVEL] ;
	GetHistogram(src, hist, WIDTH, HEIGHT) ;
	
	for(int i = 0 ; i < GRAY_LEVEL ; i++ )
		std::cout << hist[i] << std::endl ;

	std::cout << std::endl << std::endl ;

	//直方图均衡化
	int *dst_map = new int[GRAY_LEVEL] ;
	HistogramEqualization(src, dst_map, WIDTH, HEIGHT) ;

	for(int i = 0 ; i < GRAY_LEVEL ; i++ ){
		std::cout << dst_map[i] << std::endl ;
	}

	//然后根据dst_map调节src中的值
	std::cout << std::endl ;
	for(int i = 0 ; i < WIDTH * HEIGHT ; i++ ){
		src[i] = dst_map[(int)src[i]] ;
		std::cout << src[i] << " " ;
	}
	return 0 ;
}
