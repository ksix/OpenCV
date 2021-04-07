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
	void drawing_Demo(Mat& image);//ͼ�񼸺���״�Ļ���
	void drawingRadom_Demo(Mat& image);//������������ɫ
	void drawingPolyline_Demo(Mat& image);//�����������
	void mouseDrawing_Demo(Mat& image);//����������Ӧ
	void norm_Demo(Mat& image);//��������ת�����һ��
	void resize_Demo(Mat& image);//ͼ���������ֵ
	void resize_DemoX(Mat& image);//������ӿ���ͼ������
	void flip_Demo(Mat& image);//ͼ��ת
	void rotate_Demo(Mat& image);//ͼ����ת
	void video_Demo(Mat& image);//��Ƶ�ļ�����ͷʹ��
	void videoHandle_Demo(Mat& image);//��Ƶ�����뱣��
	void videoHandle_DemoX(Mat& image);//����ͷ��Ƶ¼��
	void histogram_Demo(Mat& image);//ֱ��ͼ
	void histogram2D_Demo(Mat& image);//��άֱ��ͼ
	void histogramEQ_Demo(Mat& image);//ֱ��ͼ���⻯
	void blur_Demo(Mat& image);//ͼ���ֵģ��
	void gaussianBlur_Demo(Mat& image);//��˹ģ��
	void bifilter_Demo(Mat& image);//��˹˫��ģ��
	void bifilter_DemoX(Mat& image);//��˹˫��ģ��-ʵʱ����
	void bifilter_DemoY(Mat& image);//��˹˫��ģ��-Y
	void faceDetection_Demo(Mat& image);//ʵʱ�������
};