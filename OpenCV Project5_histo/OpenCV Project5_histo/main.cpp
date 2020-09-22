#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

Mat calcGrayHist(const Mat& img) {
	CV_Assert(img.type() == CV_8UC1);
	Mat hist;
	int channels[] = { 0 };
	int dims = 1;
	const int histSize[] = { 256 };
	float graylevel[] = { 0,256 };
	const float* ranges[] = { graylevel };

	calcHist(&img, 1, channels, noArray(), hist, dims, histSize, ranges);

	return hist;
}
Mat getGrayHistImage(const Mat& hist) {
	CV_Assert(hist.type() == CV_32FC1);
	CV_Assert(hist.size() == Size(1, 256));

	double histMax;
	minMaxLoc(hist, 0, &histMax);

	Mat imgHist(100, 256, CV_8UC1, Scalar(255));
	for (int i = 0; i < 256; i++) {
		line(imgHist, Point(i, 100),
			Point(i, 100 - cvRound(hist.at<float>(i, 0) * 100 / histMax)), Scalar(0));
	}
	
	return imgHist;
}

void histogram_stretching() {
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	double gmin, gmax;
	minMaxLoc(src, &gmin, &gmax);
	Mat dst = (src - gmin) * 255 / (gmax - gmin);

	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}

void histogram_equalization() {
	Mat src = imread("hawkes.bmp", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	Mat dst;
	equalizeHist(src, dst);
	imshow("src", src);
	imshow("srcHist", getGrayHistImage(calcGrayHist(src)));

	imshow("dst", dst);
	imshow("dstHist", getGrayHistImage(calcGrayHist(dst)));

	waitKey();
	destroyAllWindows();
}

int main() {
	histogram_equalization();
	/*Mat src = imread("lenna.bmp", IMREAD_GRAYSCALE);
	Mat src1 = src + 100;
	Mat src2 = src - 100;
	
	Mat hist = calcGrayHist(src);
	Mat hist_img = getGrayHistImage(hist);

	Mat hist1 = calcGrayHist(src1);
	Mat hist_img1 = getGrayHistImage(hist1);

	Mat hist2 = calcGrayHist(src2);
	Mat hist_img2 = getGrayHistImage(hist2);

	// 히스토그램 함수를 사용하지 않고 히스토그램 구하는 코드
	int hist[256] = { 0, };
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			hist[src.at<uchar>(i, j)]++;
		}
	} 

	imshow("src", src);
	imshow("srcHist", hist_img);

	imshow("src1", src1);
	imshow("srcHist1", hist_img1);

	imshow("src2", src2);
	imshow("srcHist2", hist_img2);

	waitKey();
	destroyAllWindows();*/

	return 0;
}