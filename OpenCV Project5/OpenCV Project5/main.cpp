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
	// ��ȭ������ �������� �ʾƼ� �ް��ϰ� ��ο��ȼ��� ��Ÿ����.
	// �Է� ������ �ȼ� �߿��� ��� 100�� ���Ͽ� 255���� �� ū ���� �Ǵ� �ȼ��� ������ 0�� ����� ��ο� �ȼ��� �ٲ�� �ȴ�.
	*/

	// ��ȭ���� �����
	// ���� v�� int������ �����߱� ������ 255���� �� ū���� ����� �� �ִ�.
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
	// �׷��̽����� �������� ��ȯ�� ���� ���� im1 ������ ����
	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);
	// ��� �ȼ� ���� 0���� �ʱ�ȭ�� 640*480 �׷��̽����� ���� ����. �� ������. ���α׷� ���� �� �׷��̽����� ���� ������ ��ü ���� �� ��� 
	Mat img2(480, 640, CV_8UC1, Scalar(0));
	//�̹� 3ä�� �÷� ������ ������ �ְ�, �̰� �׷��̽����� �������� ��ȯ�� �� cvtColor ���
	Mat img3 = imread("lenna.bmp", IMREAD_COLOR);
	Mat img4;
	cvtColor(img3, img4, COLOR_BGR2GRAY);
	*/







	return 0;
}