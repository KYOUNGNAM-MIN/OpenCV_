#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main() {
	/*Point_ 클래스*/
	Point pt1;
	pt1.x = 5; pt1.y = 10; // pt1 = [5, 10]
	Point pt2(10, 30); // pt2 = [10, 30]

	Point pt3 = pt1 + pt2; // pt3 = [15, 40]
	Point pt4 = pt1 * 2; // pt4 = [10, 20]
	int d1 = pt1.dot(pt2); // d1 = 350 
	// dot()함수는 두 점의 내적을 계산하는 멤버 함수
	// == pt1.x*pt2.x + pt1.y*pt2.y
	bool b1 = (pt1 == pt2); // b1 = false

	cout << "pt1: " << pt1 << endl;
	cout << "pt2: " << pt2 << endl;

	/*Size_ 클래스*/
	Size sz1, sz2(10, 20); // sz1 = [0 x 0], sz2 = [10 x 20]
	sz1.width = 5; sz1.height = 10; // sz1 = [5 x 10]

	Size sz3 = sz1 + sz2; // sz3 = [15 x 30]
	Size sz4 = sz1 * 2; // sz4 = [10 x 20]
	int area1 = sz4.area(); // area1 = 200 // area(): 사각형 크기
	
	cout << "sz3: " << sz3 << endl;
	cout << "sz4: " << sz4 << endl;

	/*Rect_ 클래스*/
	Rect rc1; // rc1 = [0 x 0 from (0,0)]
	Rect rc2(10, 10, 60, 40); // rc2 = [60 x 40 from (10,10)]

	Rect rc3 = rc1 + Size(50, 40); // rc3 = [50 x 40 from (0,0)]
	Rect rc4 = rc2 + Point(10, 10); // rc4 = [60 x 40 from (20,20)]

	// & 연산자 : 두 사각형의 겹치는 영역 반환 // | 연산자 : 두 사각형을 모두 포함하는 최소 크기의 사각형 반환
	Rect rc5 = rc3 & rc4; // rc5 = [30 x 20 from (10,10)]
	Rect rc6 = rc3 | rc4; // rc6 = [80 x 60 from(0,0)]

	cout << "rc5: " << rc5 << endl;
	cout << "rc6: " << rc6 << endl;

	/*RotatedRect 클래스*/
	RotatedRect rr1(Point2f(40, 30), Size2f(40, 20), 30.f); // 중심좌표(40,30), 크기(40,20), 시계방향으로 30도 회전
	Point2f pts[4];
	rr1.points(pts); //회전된 사각형의 좌측 하단 꼭지점부터 시게방향으로 네 꼭지점 좌표가 pts 배열에 저장됨.

	Rect br = rr1.boundingRect(); // 회전된 사각형을 감싸는 최소 크기의 사각형 = 바운딩 박스
	cout << "br: " << br << endl;

	/*Range 클래스*/
	//범위 또는 구간을 표현함. start와 end 멤버 변수를 가짐.
	Range r1(0, 10); // r1 = 0 ~ 9
	
	/*String 클래스*/
	String str1 = "Hello";
	String str2 = "world";
	String str3 = str1 + " " + str2;
	bool ret = (str2 == "WORLD"); // false
	
	Mat imgs[3];
	for (int i = 0; i < 3; i++) {
		String filename = format("test%02d.bmp", i + 1);
		imgs[i] = imread(filename);
		String windowname = format("wintest%02d", i + 1);
		imshow(windowname,imgs[i]);
	}

	waitKey();
	return 0;
}