#include<quickopencv.h>
void QuickDemo::colorSpace_Demo(Mat &image)
{
	Mat gray, hsv;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	cvtColor(image, hsv, COLOR_BGR2HSV);
	imshow("灰度", gray);
	imshow("HSV", hsv);
	imwrite("d:/gray.png", gray);
	imwrite("d:/hsv.png", hsv);
}

void QuickDemo::matCreation_Demo(Mat& image)
{
	Mat m1, m2;
	m1 = image.clone();
	image.copyTo(m2);

	//创建空白
	Mat m3 = Mat::zeros(Size(80, 80), CV_8UC3);
	m3 = Scalar(127, 127, 127);
	std::cout << m3 << std::endl;
	std::cout << "width: " << m3.cols << ", height: " << m3.rows << ", channels: " << m3.channels() << std::endl;
	imshow("m3",m3);
}

void QuickDemo::piexlVisit_Demo(Mat& image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	for (int row = 0;row < h;row++) {
		for (int col = 0;col < w;col++) {
			if (dims == 1) {//灰度图像
				int pv = image.at<uchar>(row, col);
				image.at<uchar>(row, col) = 255 - pv;
			}
			if (dims == 3) {//彩色图像
				Vec3b bgr = image.at<Vec3b>(row, col);
				image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
				image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
			}
		}
	}
	//for (int row = 0;row < h;row++) {
	//	uchar* current_row = image.ptr<uchar>(row);
	//	for (int col = 0;col < w;col++) {
	//		if (dims == 1) {//灰度图像
	//			int pv = *current_row;
	//			*current_row++ = 255 - pv;
	//		}
	//		if (dims == 3) {//彩色图像
	//			*current_row++ = 255 - *current_row;
	//			*current_row++ = 255 - *current_row;
	//			*current_row++ = 255 - *current_row;
	//		}
	//	}
	//}
	imshow("像素修改", image);
	imwrite("d:/opencvPixel.jpg", image);
}

void QuickDemo::operators_Demo(Mat& image) {
	Mat dst;
	Mat m = Mat::zeros(image.size(), image.type());

	m = Scalar(50, 50, 50);
	add(image, m, dst);
	imshow("加法操作", dst);

	m = Scalar(50, 50, 50);
	subtract(image, m, dst);
	imshow("减法操作", dst);

	m = Scalar(2, 2, 2);
	multiply(image, m, dst);
	imshow("乘法操作", dst);

	m = Scalar(4, 4, 4);
	multiply(image, m, dst);
	imshow("除法操作", dst);
}

static void onTrak(int b, void* userdata) {
	Mat image = *((Mat*)userdata);//指针变数据时前面得加星号
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(b, b, b);
	add(image, m, dst);
	imshow("亮度与对比度调整", dst);
}
void QuickDemo::trackingBar_Demo(Mat& image) {
	namedWindow("亮度与对比度调整", WINDOW_AUTOSIZE);
	int lightness = 1;
	int max_value = 255;
	int contrast_value = 2.0;
	createTrackbar("Light Value:", "亮度与对比度调整", &lightness, max_value, onTrak, (void*)(&image));
	onTrak(lightness, &image);
}

int light_times = 0, contrast_times = 0;
static void onLightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);//指针变数据时前面得加星号
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	addWeighted(image, 1.0, m, 0, b, dst);
	imshow("亮度与对比度调整", dst);
	light_times++;
	std::cout << "onLightness" << light_times << "\n" << std::endl;
}
static void onContrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);//指针变数据时前面得加星号
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(b, b, b);
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst);
	imshow("亮度与对比度调整", dst);
	contrast_times++;
	std::cout << "onContrast" << contrast_times << "\n" << std::endl;
}
void QuickDemo::trackingBarX_Demo(Mat& image) {
	namedWindow("亮度与对比度调整", WINDOW_AUTOSIZE);
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;
	createTrackbar("亮度", "亮度与对比度调整", &lightness, max_value, onLightness, (void*)(&image));
	createTrackbar("对比度", "亮度与对比度调整", &contrast_value, 200, onContrast, (void*)(&image));
	//onLightness(lightness, &image);
}

void QuickDemo::key_Demo(Mat& image) {
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true) {
		int c = waitKey(100);
		if (c == 27) {
			break;
		}
		switch (c) {
		case 49:
			std::cout << "you print key #1." << std::endl;
			cvtColor(image, dst, COLOR_BGR2GRAY);
			break;
		case 50:
			std::cout << "you print key #2." << std::endl;
			cvtColor(image, dst, COLOR_BGR2HSV);
			break;
		case 51:
			std::cout << "you print key #3." << std::endl;
			dst = Scalar(50, 50, 50);
			add(image, dst, dst);
			break;
		}
		imshow("键盘响应", dst);
	}
}

void QuickDemo::colorStyle_Demo(Mat& image) {
	int colorMap[] = {
		COLORMAP_AUTUMN,
		COLORMAP_BONE,
		COLORMAP_JET,
		COLORMAP_WINTER,
		COLORMAP_RAINBOW,
		COLORMAP_OCEAN,
		COLORMAP_SUMMER,
		COLORMAP_SPRING,
		COLORMAP_COOL,
		COLORMAP_PINK,
		COLORMAP_HOT,
		COLORMAP_PARULA,
		COLORMAP_MAGMA,
		COLORMAP_INFERNO,
		COLORMAP_PLASMA,
		COLORMAP_VIRIDIS,
		COLORMAP_CIVIDIS,
		COLORMAP_TWILIGHT,
		COLORMAP_TWILIGHT_SHIFTED
	};

	Mat dst = Mat::zeros(image.size(), image.type());
	int index = 0;
	while (true) {
		int c = waitKey(100);
		if (c == 27) {
			break;
		}
		applyColorMap(image, dst, colorMap[index%19]);
		imshow("颜色风格" + std::to_string(index%19), dst);
		imwrite("d:/颜色风格" + std::to_string(index % 19) + ".jpg", dst);
		index++;
	}
}

void QuickDemo::bitWise_Demo(Mat& image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	imshow("m1", m1);
	imshow("m2", m2);
	Mat dst = Mat::zeros(Size(256, 256), CV_8UC3);
	bitwise_and(m1, m2, dst);
	imshow("and", dst);
	//bitwise_not(image, dst);
	dst = ~image;
	imshow("not", dst);
	bitwise_xor(m1, m2, dst);//XOR先非再或
	imshow("xor", dst);
}

void QuickDemo::channels_Demo(Mat& image) {
	std::vector<Mat> mv;
	split(image, mv);
	imshow("蓝色", mv[0]);
	imshow("绿色", mv[1]);
	imshow("红色", mv[2]);

	Mat dst;
	mv[0] = 0;//通道分离
	mv[1] = 0;
	merge(mv, dst);
	imshow("merge", dst);

	int from_to[] = { 0,2,1,1,2,0 };
	mixChannels(&image, 1, &dst, 1, from_to, 3);
	imshow("通道混合", dst);
}

void QuickDemo::inrange_Demo(Mat& image) {
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	imshow("hsv", hsv);
	Mat mask;
	//inRange(hsv, Scalar(0, 0, 221), Scalar(180, 30, 255), mask);//处理白色
	inRange(hsv, Scalar(35,43,46), Scalar(77,255,255), mask);
	imshow("mask", mask);

	Mat redback = Mat::zeros(image.size(), image.type());
	redback = Scalar(40, 40, 200);
	bitwise_not(mask, mask);
	imshow("masknot", mask);
	image.copyTo(redback, mask);
	imshow("ROI区域提取", redback);
}

void QuickDemo::pixelStatistic_Demo(Mat& image) {

}
