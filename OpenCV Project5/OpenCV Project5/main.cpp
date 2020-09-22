#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void brightness1() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	Mat dstPlus = src + 100;
	Mat dstMinus = src - 100;

	imshow("src", src);
	imshow("dstPlus", dstPlus);
	imshow("dstMinus", dstMinus);
	waitKey();

	destroyAllWindows();
}
void brightness2() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	Mat dst(src.rows, src.cols, src.type());

	/*for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			dst.at<uchar>(i, j) = src.at<uchar>(i, j) + 100;
		}
	}
	// 포화연산을 수행하지 않아서 급격하게 어두운픽셀이 나타난다.
	// 입력 영상의 픽셀 중에서 밝기 100을 더하여 255보다 더 큰 값이 되는 픽셀은 오히려 0에 가까운 어두운 픽셀로 바뀌게 된다.
	*/

	// 포화연산 수행법
	// 변수 v는 int형으로 선언했기 때문에 255보다 더 큰값이 저장될 수 있다.
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			int v = src.at<uchar>(i, j) + 100;
			dst.at<uchar>(i, j) = v > 255 ? 255 : v < 0 ? 0 : v;
		}
	}

	imshow("src", src);
	imshow("dst", dst);
	waitKey();

	destroyAllWindows();
}

void brightness3() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	Mat dst(src.rows, src.cols, src.type());

	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			dst.at<uchar>(i, j) = saturate_cast<uchar>(src.at<uchar>(i, j) + 100);
		}
	}
	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void on_brightness(int pos, void* userdata) {
	Mat src = *(Mat*)userdata;
	Mat dst = src + pos;
	imshow("dst", dst);
}

void brightness4() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	namedWindow("dst");
	createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)&src);
	on_brightness(0, (void*)&src);

	waitKey();
	destroyAllWindows();
}

void contrast1() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	float s = 2.f;
	Mat dst = s * src;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void contrast2() {
	Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	float alpha = 1.f;
	Mat dst = src + (src - 128) * alpha;

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main() {
	contrast2();

	/*
	// 그레이스케일 형식으로 변환된 레나 영상 im1 변수에 저장
	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);
	// 모든 픽셀 값이 0으로 초기화된 640*480 그레이스케일 영상 생성. 빈 껍데기. 프로그램 동작 중 그레이스케일 영상 저장할 객체 만들 때 사용 
	Mat img2(480, 640, CV_8UC1, Scalar(0));
	//이미 3채널 컬러 영상을 가지고 있고, 이걸 그레이스케일 영상으로 변환할 때 cvtColor 사용
	Mat img3 = imread("lenna.bmp", IMREAD_COLOR);
	Mat img4;
	cvtColor(img3, img4, COLOR_BGR2GRAY);
	*/







	return 0;
}