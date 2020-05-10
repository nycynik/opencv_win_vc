#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class MyOCV_ImageIO
{
public:
	static int test();

	// Save and load images
	static int loadImage(Mat& img, String pathname);
	static int saveImage(Mat img, String pathname);

	// Image sizing and scaling
	static int cropImage(Mat& dst, Mat src, long x, long y, long width, long height);

	// Image color manipulation
	static Mat reduce(Mat& img, int divWidth); 

private:
	static Mat& scanImageAndReduce(Mat& I, const uchar* const table);
};


