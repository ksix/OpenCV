#pragma once
#include<opencv2/opencv.hpp>
using namespace cv;
class QuickDemo {
public:
	void colorSpace_Demo(Mat &image);
	void matCreation_Demo(Mat &image);
	void piexlVisit_Demo(Mat& image);
	void operators_Demo(Mat& image);//������ز������Ӽ��˳�
	void trackingBar_Demo(Mat& image);//�϶�����������
	void trackingBarX_Demo(Mat& image);//�϶����������ȺͶԱȶ�
	void key_Demo(Mat& image);//���̲���
	void colorStyle_Demo(Mat& image);//��ɫ�����
	void bitWise_Demo(Mat& image);//������&����
	void channels_Demo(Mat& image);//ͨ���ķ�����ϲ�
	void inrange_Demo(Mat& image);//ɫ�ʿռ�ת����ROI������ȡ
	void pixelStatistic_Demo(Mat& image);//���ص���ֵ��ֵ����
};