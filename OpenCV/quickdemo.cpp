#include<quickopencv.h>
#include<opencv2/dnn.hpp>
using namespace std;
using namespace cv;
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
	double minV, maxV;
	Point minLoc, maxLoc;
	std::vector<Mat> mv;
	split(image, mv);
	for (int i = 0;i < mv.size();i++) {
		minMaxLoc(mv[i], &minV, &maxV, &minLoc, &maxLoc, Mat());//单通道取最值
		std::cout<<"NO. Channels"<<i << "min value:" << minV << " , max value:" << maxV << std::endl;
	}
	
	Mat mean, stddev;
	meanStdDev(image, mean, stddev);
	for (int i = 0;i < mean.rows;i++) {
		for (int j = 0;j < mean.cols;j++) {
			std::cout << mean.at<double>(i, j) << std::endl;
		}
	}
	std::cout << "mean:\n" << mean << std::endl;
	std::cout << "stddev:\n" << stddev << std::endl;
}

void QuickDemo::drawing_Demo(Mat& image) {
	Rect rect;
	rect.x = 200;
	rect.y = 80;
	rect.width = 110;
	rect.height = 120;
	Mat bg = Mat::zeros(image.size(), image.type());
	rectangle(bg, rect, Scalar(0, 0, 255), -1, 8, 0);
	circle(bg, Point(310, 200), 20, Scalar(255, 0, 0), -1, 8, 0);
	line(bg, Point(0, 0), Point(400, 400), Scalar(0, 255, 0), 2, 8, 0);
	RotatedRect rrt;
	rrt.center = Point(430, 200);
	rrt.size = Size(130, 200);
	rrt.angle = 0.0;
	ellipse(image, rrt, Scalar(255, 0, 255), 2, 8);

	Mat hsv;
	cvtColor(bg, hsv, COLOR_BGR2HSV);
	Mat bgmask;
	inRange(hsv, Scalar(0, 0, 0), Scalar(180, 255, 46), bgmask);
	bitwise_not(bgmask, bgmask);
	Mat imageClone = image.clone();
	bg.copyTo(imageClone, bgmask);
	imshow("imageClone", imageClone);
	addWeighted(image, 0.7, imageClone, 0.4, 0, image);
	imshow("绘制演示", image);
}

void QuickDemo::drawingRadom_Demo(Mat& image) {
	Mat canvas = image;
	int w = canvas.cols;
	int h = canvas.rows;
	RNG rng(12345);
	Point p1 = Point(0, 0);
	Point p2 = Point(0, 0);
	while (true) {
		int c = waitKey(1);
		if (c == 27) {
			break;
		}
		int x = rng.uniform(0, w);
		int y = rng.uniform(0, h);
		p1 = p2;
		p2 = Point(x, y);
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);
		canvas = Scalar(255,255,255);
		line(canvas, p1, p2, Scalar(b, g, r), 1, 8, 0);
		imshow("canvas", canvas);
	}
}

void QuickDemo::drawingPolyline_Demo(Mat& image) {
	Mat canvas = image.clone();
	Point p1 = Point(60, 40);
	Point p2 = Point(350, 70);
	Point p3 = Point(400, 280);
	Point p4 = Point(320, 350);
	Point p5 = Point(140, 350);
	std::vector<Point> pts;
	pts.push_back(p1);
	pts.push_back(p2);
	pts.push_back(p3);
	pts.push_back(p4);
	pts.push_back(p5);
	/*polylines(canvas, pts, true, Scalar(0, 255, 0), 2, 8, 0);
	imshow("多边形绘制", canvas);
	fillPoly(canvas, pts, Scalar(255, 0, 255), 8, 0);
	imshow("多边形填充", canvas);*/
	std::vector<std::vector<Point>> contours;
	contours.push_back(pts);
	drawContours(canvas, contours, -1, Scalar(128, 64, 220), -1);//前面的-1代表绘制所有pts，否则按照索引单独绘制
	imshow("drawContours", canvas);
}

Point sp(-1, -1);
Point ep(-1, -1);
Mat tmpImage;
static void on_Draw(int event, int x, int y, int flags, void* userdata) {
	Mat image = *((Mat*)userdata);
	if (event == EVENT_LBUTTONDOWN) {
		sp.x = x;
		sp.y = y;
		//std::cout << "start point:" << sp << std::endl;
	}
	else if (event == EVENT_LBUTTONUP) {
		ep.x = x;
		ep.y = y;
		/*int dx = ep.x - sp.x;
		int dy = ep.y - sp.y;*/
		int dx = (ep.x > image.cols ? image.cols : ep.x) - sp.x;
		int dy = (ep.y > image.rows ? image.rows : ep.y) - sp.y;
		if (dx > 0 && dy > 0) {
			Rect box(sp.x, sp.y, dx, dy);
			std::cout << "BOX:" << box << std::endl;
			tmpImage.copyTo(image);
			imshow("ROI区域", image(box));
			rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
			imshow("鼠标绘制", image);
			//为下次画框做准备
			sp.x = -1;
			sp.y = -1;
		}
		//std::cout << "end point:" << ep << std::endl;
	}
	else if (event == EVENT_MOUSEMOVE) {
		if (sp.x > 0 && sp.y > 0) {
			ep.x = x;
			ep.y = y;
			/*int dx = ep.x - sp.x;
			int dy = ep.y - sp.y;*/
			int dx = (ep.x > image.cols ? image.cols : ep.x) - sp.x;
			int dy = (ep.y > image.rows ? image.rows : ep.y) - sp.y;
			if (dx > 0 && dy > 0) {
				Rect box(sp.x, sp.y, dx, dy);
				tmpImage.copyTo(image);
				rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
				imshow("鼠标绘制", image);
			}
			//std::cout << "end point:" << ep << std::endl;
		}
	}
}
void QuickDemo::mouseDrawing_Demo(Mat& image) {
	namedWindow("鼠标绘制", WINDOW_AUTOSIZE);
	setMouseCallback("鼠标绘制", on_Draw, (void*)(&image));
	imshow("鼠标绘制", image);
	tmpImage = image.clone();
}

void QuickDemo::norm_Demo(Mat& image) {
	Mat dst;
	std::cout << image.type() << std::endl;
	image.convertTo(image, CV_32F);//32位浮点数，CV_8UC3代表3通道8位无符号
	std::cout << image.type() << std::endl;
	normalize(image, dst, 1.0, 0, NORM_MINMAX);
	std::cout << dst.type() << std::endl;
	imshow("图像数据归一化", dst);
}

void QuickDemo::resize_Demo(Mat& image) {
	Mat zoomin, zoomout;
	int w = image.cols;
	int h = image.rows;
	resize(image, zoomin, Size(w / 2, h / 2), 0.0, 0.0, INTER_LINEAR);
	imshow("zoomin", zoomin);
	resize(image, zoomout, Size(w * 1.5, h * 1.5), 0.0, 0.0, INTER_LINEAR);
	imshow("zoomout", zoomout);
}

double sizeMult = 1;
double sizeRate = 0.1;//缩放变化率
//Mat resizeTmpImage;
static void on_MouseWheelRollDraw(int event, int x, int y, int flags, void* userdata) {
	Mat image = *((Mat*)userdata);
	int w = image.cols;
	int h = image.rows;
	if (event == EVENT_MOUSEWHEEL) {
		int value = getMouseWheelDelta(flags);//向上+120 向下-120
		if (value > 0) {
			sizeMult += sizeRate;
		}
		else {
			sizeMult -= sizeRate;
		}
		//std::cout << "sizeMult:" << sizeMult << std::endl;
		//resizeTmpImage.copyTo(image);
		if (sizeMult < sizeRate) {
			return;
		}
		resize(image, image, Size(w * sizeMult, h * sizeMult), 0, 0, INTER_LINEAR);
		imshow("滚轮缩放", image);
	}

}
void QuickDemo::resize_DemoX(Mat& image) {
	namedWindow("滚轮缩放", WINDOW_AUTOSIZE);
	Mat dst;
	int w = image.cols;
	int h = image.rows;
	setMouseCallback("滚轮缩放", on_MouseWheelRollDraw, (void*)(&image));
	imshow("滚轮缩放", image);
	//resizeTmpImage = image.clone();
}

void QuickDemo::flip_Demo(Mat& image) {
	Mat dst;
	flip(image, dst, -1);//0上下翻转 1左右翻转 -1水平翻转+左右翻转即180°旋转
	imshow("图像翻转", dst);
}

void QuickDemo::rotate_Demo(Mat& image) {
	Mat dst, M;
	int w = image.cols;
	int h = image.rows;
	M = getRotationMatrix2D(Point2f(w / 2, h / 2), 90, 1.0);
	double cos = abs(M.at<double>(0, 0));
	double sin = abs(M.at<double>(0, 1));
	int nw = w * cos + h * sin;
	int nh = h * cos + w * sin;
	M.at<double>(0, 2) += nw / 2 - w / 2;
	M.at<double>(1, 2) += nh / 2 - h / 2;
	warpAffine(image, dst, M, Size(nw, nh), 1, 0, Scalar(255, 0, 0));
	imshow("图像旋转", dst);
}

void QuickDemo::video_Demo(Mat& image) {
	VideoCapture capture(0);
	//VideoCapture capture("C:/Users/ksig/Videos/Screenrecording_20210220_085646.mp4");
	Mat frame;
	while (true) {
		capture.read(frame);
		if (frame.empty())
			break;
		//TODO:do somthing
		rotate_Demo(frame);
		imshow("frame", frame);
		int c = waitKey(10);
		if (c == 27)
			break;
	}
	capture.release();
}

void QuickDemo::videoHandle_Demo(Mat& image) {
	//VideoCapture capture("C:/Users/ksig/Videos/Screenrecording_20210220_085646.mp4");
	VideoCapture capture(0);
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int frame_count = capture.get(CAP_PROP_FRAME_COUNT);
	double fps = capture.get(CAP_PROP_FPS);
	std::cout << "width:" << frame_width << std::endl;
	std::cout << " height:" << frame_height << std::endl;
	std::cout << " frames:" << frame_count << std::endl;
	std::cout << " fps:" << fps << std::endl;
	//VideoWriter writer("D:/JZ.AVI", capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);
	VideoWriter writer("D:/JZ.AVI", VideoWriter::fourcc('X','V','I','D'), 12, Size(frame_width, frame_height), true);
	Mat frame;
	while (true) {
		capture.read(frame);
		if (frame.empty())
			break;
		imshow("frame", frame);
		writer.write(frame);
		int c = waitKey(1);
		if (c == 27)
			break;
	}
	capture.release();
	writer.release();
}

void QuickDemo::videoHandle_DemoX(Mat& image) {
	VideoCapture cap;
	VideoWriter outputVideo;
	Mat frame;

	cap.open(0);
	outputVideo.open(String("D:/temp.AVI"), VideoWriter::fourcc('X', 'V', 'I', 'D'), 12, Size(640, 480));
	while (true) {
		cap >> frame;
		outputVideo.write(frame);
		imshow("Recording...", frame);
		if (waitKey(1) == ' ')  break;
	}

	destroyWindow("Recording...");
	cap.release();
	outputVideo.release();
}

void QuickDemo::histogram_Demo(Mat& image) {
	//三通道分离
	std::vector<Mat> bgr_plane;
	split(image, bgr_plane);

	const int channels[1] = { 0 };
	const int bins[1] = { 256 };
	float hranges[2] = { 0,255 };
	const float* ranges[1] = { hranges };
	Mat b_hist, g_hist, r_hist;

	//计算B/G/R通道的直方图
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);

	//显示直方图
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);

	//归一化直方图数据
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	//绘制直方图曲线
	for (int i = 1;i < bins[0];i++) {
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))), Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))), Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))), Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}

	//显示直方图
	namedWindow("Histogram Demo", WINDOW_AUTOSIZE);
	imshow("Histogram Demo", histImage);
}

void QuickDemo::histogram2D_Demo(Mat& image) {
	Mat hsv, hs_hist;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	int hbins = 30;
	int sbins = 32;
	int hist_bins[] = { hbins,sbins };
	float h_range[] = { 0,180 };
	float s_range[] = { 0,255 };
	const float* hs_ranges[] = { h_range,s_range };
	int hs_channels[] = { 0,1 };
	calcHist(&hsv, 1, hs_channels, Mat(), hs_hist, 2, hist_bins ,hs_ranges, true, false);
	double maxVal = 0;
	minMaxLoc(hs_hist, 0, &maxVal, 0, 0);
	int scale = 10;
	Mat hist2d_image = Mat::zeros(sbins * scale, hbins * scale, CV_8UC3);
	for (int h = 0;h < hbins;h++) {
		for (int s = 0;s < sbins;s++) {
			float binVal = hs_hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);
			rectangle(hist2d_image, Point(h * scale, s * scale), Point((h + 1) * scale - 1, (s + 1) * scale - 1), Scalar::all(intensity), -1);
		}
	}
	applyColorMap(hist2d_image, hist2d_image, COLORMAP_JET);
	imshow("H-S Histogram", hist2d_image);
}

void QuickDemo::histogramEQ_Demo(Mat& image) {
	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	Mat dst;
	equalizeHist(gray, dst);
	imshow("灰度图像", gray);
	imshow("直方图均衡化", dst);
	applyColorMap(dst, dst, COLORMAP_JET);
	imshow("直方图均衡化彩色", dst);
}

void QuickDemo::blur_Demo(Mat& image) {
	Mat dst;
	for (int i = 1;i <= 20;i++) {
		for (int j = 1;j <= 20;j++) {
			blur(image, dst, Size(i, j), Point(-1, -1));
			imshow("均值模糊", dst);
			waitKey(1000);
		}
	}
	
}

void QuickDemo::gaussianBlur_Demo(Mat& image) {
	Mat dst;
	//GaussianBlur(image, dst, Size(5, 5), 15);
    //imshow("高斯模糊", dst);
	for (int i = 1;i <= 20;i++) {
		GaussianBlur(image, dst, Size(0, 0), i);
		imshow("高斯模糊", dst);
		waitKey(1000);
		if (i == 20) {
			for (int j = 20;j >= 1;j--) {
				GaussianBlur(image, dst, Size(0, 0), j);
				imshow("高斯模糊", dst);
				waitKey(1000);
			}
		}
	}
}

void QuickDemo::bifilter_Demo(Mat& image) {
	Mat dst;
	bilateralFilter(image, dst, 0, 100, 10);
	imshow("高斯双边模糊", dst);
}

void QuickDemo::bifilter_DemoX(Mat& image) {
	VideoCapture capture(0);
	Mat frame;
	Mat dst;
	while (true) {
		capture.read(frame);
		if (frame.empty())
			break;
		bilateralFilter(frame, dst, 0, 30, 10);
		imshow("常规", frame);
		imshow("美颜", dst);
		if (waitKey(1) == 27)
			break;
	}
}

void QuickDemo::faceDetection_Demo(Mat& image) {
	string root_dir = "D:/Dev/TOOLS/OpenCV4.5/opencv/sources/samples/dnn/face_detector/";
	dnn::Net net = dnn::readNetFromTensorflow(root_dir + "opencv_face_detector_uint8.pb", root_dir + "opencv_face_detector.pbtxt");
	VideoCapture capture(0);
	Mat frame;
	while (true) {
		capture.read(frame);
		if (frame.empty()) {
			break;
		}
		Mat blob = dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);
		net.setInput(blob);//NCHW
		Mat probs = net.forward();//
		//解析结果
		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());
		for (int i = 0;i < detectionMat.rows;i++) {
			float confidence = detectionMat.at<float>(i, 2);
			if (confidence > 0.5) {
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
				Rect box(x1, y1, x2 - x1, y2 - y1);
				rectangle(frame, box, Scalar(0, 0, 255), 2, 8, 0);
			}
		}
		imshow("人脸检测", frame);
		if (waitKey(1) == 27)
			break;
	}
}

//定义全局变量
const int g_ndMaxValue = 100;
const int g_nsigmaColorMaxValue = 200;
const int g_nsigmaSpaceMaxValue = 200;
int g_ndValue;
int g_nsigmaColorValue;
int g_nsigmaSpaceValue;

Mat g_srcImage;
Mat g_dstImage;

//定义回调函数
void on_bilateralFilterTrackbar(int, void*)
{
	bilateralFilter(g_srcImage, g_dstImage, g_ndValue, g_nsigmaColorValue, g_nsigmaSpaceValue);
	imshow("双边滤波图像", g_dstImage);
}

void QuickDemo::bifilter_DemoY(Mat &image){
		g_srcImage = image;

		//判断图像是否加载成功
		if (g_srcImage.empty())
		{
			cout << "图像加载失败!" << endl;
		}
		else
			cout << "图像加载成功!" << endl << endl;

		namedWindow("原图像", WINDOW_AUTOSIZE);
		imshow("原图像", g_srcImage);

		//定义输出图像窗口属性和轨迹条属性
		namedWindow("双边滤波图像", WINDOW_AUTOSIZE);
		g_ndValue = 10;
		g_nsigmaColorValue = 10;
		g_nsigmaSpaceValue = 10;

		char dName[20];
		sprintf_s(dName, "邻域直径 %d", g_ndMaxValue);

		char sigmaColorName[20];
		sprintf_s(sigmaColorName, "sigmaColor %d", g_nsigmaColorMaxValue);

		char sigmaSpaceName[20];
		sprintf_s(sigmaSpaceName, "sigmaSpace %d", g_nsigmaSpaceMaxValue);

		//创建轨迹条
		createTrackbar(dName, "双边滤波图像", &g_ndValue, g_ndMaxValue, on_bilateralFilterTrackbar);
		on_bilateralFilterTrackbar(g_ndValue, 0);

		createTrackbar(sigmaColorName, "双边滤波图像", &g_nsigmaColorValue, g_nsigmaColorMaxValue, on_bilateralFilterTrackbar);
		on_bilateralFilterTrackbar(g_nsigmaColorValue, 0);

		createTrackbar(sigmaSpaceName, "双边滤波图像", &g_nsigmaSpaceValue, g_nsigmaSpaceMaxValue, on_bilateralFilterTrackbar);
		on_bilateralFilterTrackbar(g_nsigmaSpaceValue, 0);
}
