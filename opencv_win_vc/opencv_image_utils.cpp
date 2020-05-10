// opencv_win_vc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "MyOCV_ImageIO.hpp"
#include "opencv_image_utils.h"

using namespace cv;
using namespace std;


int main()
{
	cout << "load image" << endl;
	Mat img;
	String windowName;
	
	if (MyOCV_ImageIO::loadImage(img, "images/bicycle.png") == 0) {

		Mat img2;
		MyOCV_ImageIO::cropImage(img2, img, 10, 130, 140, 180);

		windowName = "Biycle";
		namedWindow(windowName);
		imshow(windowName, img2);
	}

	Mat img3 = imread("images/fruit.png");
	windowName = "Original Fruit";
	namedWindow(windowName);
	imshow(windowName, img3);

	// start timer
	double t = (double)getTickCount();	
	Mat img_grey = MyOCV_ImageIO::reduce(img3, 84);
	windowName = "Reduced Fruit";
	namedWindow(windowName);
	imshow(windowName, img3);

	// show how long it took
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "c method in seconds               : " << t << endl;

	// blend two images
	Mat dolph_img;
	if (MyOCV_ImageIO::loadImage(dolph_img, "images/dolphin.png") == 0) {
		Mat img4 = MyOCV_ImageIO::blend(img, dolph_img, .3);
		imshow("Blend", img4);
	}

	// generate a window
	Mat image = Mat::zeros(300, 600, CV_8UC3);
	circle(image, Point(250, 150), 100, Scalar(0, 255, 128), -100);
	circle(image, Point(350, 150), 100, Scalar(255, 255, 255), -100);
	imshow("Display Window", image);

	// save a file
	if (MyOCV_ImageIO::saveImage(img3, "./MyImage.jpg") != 0) { // save as JPEG, we can use other filenames to save as alt formats, like .png
	
		cout << "Failed to save the image" << endl;
		cin.get(); //wait for a key press

	} else {
		cout << "Image was saved to a file" << endl;
	}
	

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
