#include<opencv2/opencv.hpp>
#include<quickopencv.h>
#include<iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv) {
	Mat src = imread("C:/Users/ksig/Pictures/flowers.jpg");
	//src = imread("C:/Users/ksig/Pictures/΢��ͼƬ_20210319095003.jpg");
	if (src.empty()) {
		printf("couldn't load picture.");
		return -1;
	}
	namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);

	QuickDemo qd;
	qd.pixelStatistic_Demo(src);

	waitKey(0);
}