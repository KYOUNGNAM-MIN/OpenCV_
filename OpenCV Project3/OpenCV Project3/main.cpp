#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void MatOp1() {
	Mat img1; // empty matrix
	Mat img2(480, 640, CV_8UC1); //unsigned char, 1-channel
	Mat img3(480, 640, CV_8UC3); //unsigned char, 3-channels
	Mat img4(Size(640, 480), CV_8UC3); //Size(width, height)
	Mat img5(480, 640, CV_8UC1, Scalar(128)); //initial values, 128
	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255)); //initial values, red

	Mat mat1 = Mat::zeros(3, 3, CV_32SC1); //0's matrix
	Mat mat2 = Mat::ones(3, 3, CV_32FC1); //1's matrix
	Mat mat3 = Mat::eye(3, 3, CV_32FC1); //identity matrix

	float data[] = { 1,2,3,4,5,6 };
	Mat mat4(2, 3, CV_32FC1, data);

	/*Mat_<float> mat5_(2, 3);
	mat5_ << 1, 2, 3, 4, 5, 6;
	Mat mat5 = mat5_;*/
	Mat mat5 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
	Mat mat6 = Mat_<float>({ 2,3 }, { 1,2,3,4,5,6 });

	mat4.create(256, 256, CV_8UC3); //uchar, 3-channels
	mat5.create(4, 4, CV_32FC1); //float, 1-channel

	mat4 = Scalar(255, 0, 0);
	mat5.setTo(1.f);
}

void MatOp2() {
	Mat img1 = imread("dog.bmp");
	if (img1.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	Mat img2 = img1; // 복사 생성자(얕은 복사)
	Mat img3;
	img3 = img1; // 대입 연산자(얕은 복사)

	Mat img4 = img1.clone(); // 깊은 복사
	Mat img5;
	img1.copyTo(img5); // 깊은 복사

	img1.setTo(Scalar(0, 255, 255)); // yellow

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);
	imshow("img5", img5);

	waitKey();
	destroyAllWindows();
}

void MatOp3() {
	Mat img1 = imread("cat.bmp");
	if (img1.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	Mat img2 = img1(Rect(220, 120, 340, 240));
	Mat img3 = img1(Rect(220, 120, 340, 240)).clone();

	img2 = ~img2;

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);

	waitKey();
	destroyAllWindows();
}

void MatOp4() {
	Mat mat1 = Mat::zeros(3, 4, CV_8UC1);

	for (int i = 0; i < mat1.rows; i++) {
		for (int j = 0; j < mat1.cols; j++) {
			mat1.at<uchar>(i, j)++;
		}
	}

	for (int i = 0; i < mat1.rows; i++) {
		uchar* p = mat1.ptr<uchar>(i);
		for (int j = 0; j < mat1.cols; j++) {
			p[j]++;
		}
	}

	for (MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); ++it) {
		(*it)++;
	}

	cout << "mat1:\n" << mat1 << endl;
}

void MatOp5() {
	Mat img1 = imread("lenna.bmp");
	if (img1.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	cout << "Width: " << img1.cols << endl;
	cout << "Height: " << img1.rows << endl;
	cout << "Channels: " << img1.channels() << endl;

	if (img1.type() == CV_8UC1)
		cout << "img1 is a grayscale image." << endl;
	else if (img1.type() == CV_8UC3)
		cout << "img1 is a truecolor image." << endl;

	float data[] = { 2.f, 1.414f, 3.f, 1.732f };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1: \n" << mat1 << endl;
}

void MatOp6() {
	float data[] = { 1,1,2,3 };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n" << mat1 << endl;

	Mat mat2 = mat1.inv();
	cout << "mat2:\n" << mat2 << endl;

	cout << "mat1.t():\n" << mat1.t() << endl;
	cout << "mat1 + 3:\n" << mat1 + 3 << endl;
	cout << "mat1 + mat2:\n" << mat1 + mat2 << endl;
	cout << "mat1 * mat2:\n" << mat1 * mat2 << endl;
}

void MatOp7() {
	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);
	if (img1.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}
	Mat img1f;
	img1.convertTo(img1f, CV_32FC1);

	uchar data1[] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	Mat mat1(3, 4, CV_8UC1, data1);
	Mat mat2 = mat1.reshape(0, 1);

	cout << "mat1:\n" << mat1 << endl;
	cout << "mat1_reshape:\n" << mat2 << endl;

	Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255;
	mat1.push_back(mat3);  //pop_back(제거할 행 개수)
	cout << "mat1_pushback:\n" << mat1 << endl;

	mat1.resize(6, 100);
	cout << "mat1_resize:\n" << mat1 << endl;
}

void VecOp() {
	Vec3b p1, p2(0, 0, 255);
	p1[0] = 100;
	cout << "p1: " << p1 << endl;
	cout << "p2: " << p2 << endl;
}

void ScalarOp() {
	Scalar gray = 128;
	cout << "gray: " << gray << endl;
	
	Scalar yellow(0, 255, 255);
	cout << "yellow: " << yellow << endl;
	Mat img1(256, 256, CV_8UC3, yellow);
	for (int i = 0; i < 4; i++) {
		cout << yellow[i] << endl;
	}
}

void printMat(InputArray _mat) {
	Mat mat = _mat.getMat();
	cout << mat << endl;
}

void InputArrayOp() {
	uchar data1[] = { 1,2,3,4,5,6 };
	Mat mat1(2, 3, CV_8U, data1);
	printMat(mat1);

	vector<float> vec1 = { 1.2f,3.4f,-2.1f };
	printMat(vec1);
}

int main() {
	InputArrayOp();

	return 0;
}