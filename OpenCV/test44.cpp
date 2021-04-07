#include<opencv2/opencv.hpp>
#include<quickopencv.h>
#include<iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv) {
	Mat src = imread("C:/Users/ksig/Pictures/om.jpg");
	//src = imread("C:/Users/ksig/Pictures/Œ¢–≈Õº∆¨_20210319095003.jpg");
	if (src.empty()) {
		printf("couldn't load picture.");
		return -1;
	}
	/*namedWindow("input", WINDOW_AUTOSIZE);
	imshow("input", src);*/

	QuickDemo qd;
	qd.bifilter_DemoY(src);

	waitKey(0);
}