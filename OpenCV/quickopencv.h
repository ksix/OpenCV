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
	void drawing_Demo(Mat& image);//图像几何形状的绘制
	void drawingRadom_Demo(Mat& image);//随机数与随机颜色
	void drawingPolyline_Demo(Mat& image);//多边形填充绘制
	void mouseDrawing_Demo(Mat& image);//鼠标操作与响应
	void norm_Demo(Mat& image);//像素类型转换与归一化
	void resize_Demo(Mat& image);//图像缩放与插值
	void resize_DemoX(Mat& image);//鼠标轮子控制图像缩放
	void flip_Demo(Mat& image);//图像翻转
	void rotate_Demo(Mat& image);//图像旋转
	void video_Demo(Mat& image);//视频文件摄像头使用
	void videoHandle_Demo(Mat& image);//视频处理与保存
	void videoHandle_DemoX(Mat& image);//摄像头视频录制
	void histogram_Demo(Mat& image);//直方图
	void histogram2D_Demo(Mat& image);//二维直方图
	void histogramEQ_Demo(Mat& image);//直方图均衡化
	void blur_Demo(Mat& image);//图像均值模糊
	void gaussianBlur_Demo(Mat& image);//高斯模糊
	void bifilter_Demo(Mat& image);//高斯双边模糊
	void bifilter_DemoX(Mat& image);//高斯双边模糊-实时美颜
	void bifilter_DemoY(Mat& image);//高斯双边模糊-Y
	void faceDetection_Demo(Mat& image);//实时人脸检测
};