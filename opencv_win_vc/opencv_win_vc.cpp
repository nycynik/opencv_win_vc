// opencv_win_vc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	cout << "load image" << endl;
	Mat img = imread("images/bicycle.png");
	if (img.empty()) {
		//failed to load
		cout << "bicycle image not found." << endl;
		return -1;
	}

	// x, y, width, height
	cv::Rect wheelROI(10, 130, 140, 180);
	Mat img2 = img(wheelROI);

	String windowName = "Biycle";
	namedWindow(windowName);
	imshow(windowName, img2);

	// generate a window
	Mat image = Mat::zeros(300, 600, CV_8UC3);
	circle(image, Point(250, 150), 100, Scalar(0, 255, 128), -100);
	circle(image, Point(350, 150), 100, Scalar(255, 255, 255), -100);
	imshow("Display Window", image);

	waitKey(0);
	destroyWindow(windowName);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
