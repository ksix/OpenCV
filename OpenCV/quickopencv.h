#pragma once
#include<opencv2/opencv.hpp>
using namespace cv;
class QuickDemo {
public:
	void colorSpace_Demo(Mat &image);
	void matCreation_Demo(Mat &image);
	void piexlVisit_Demo(Mat& image);
	void operators_Demo(Mat& image);//完成像素操作，加减乘除
	void trackingBar_Demo(Mat& image);//拖动条调整亮度
	void trackingBarX_Demo(Mat& image);//拖动条调整亮度和对比度
	void key_Demo(Mat& image);//键盘操作
	void colorStyle_Demo(Mat& image);//颜色表操作
	void bitWise_Demo(Mat& image);//画矩形&与或非
	void channels_Demo(Mat& image);//通道的分离与合并
	void inrange_Demo(Mat& image);//色彩空间转换，ROI区域提取
	void pixelStatistic_Demo(Mat& image);//像素的最值均值方差
};