// opencv_win_vc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// fastest way to scan an image and do some operation on it
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);
	int channels = I.channels();
	int nRows = I.rows;
	int nCols = I.cols * channels;
	if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	int i, j;
	uchar* p;
	for (i = 0; i < nRows; ++i)
	{
		p = I.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j)
		{
			p[j] = table[p[j]];
		}
	}
	return I;
}

// slightly safer way than the C way
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);
	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{
		MatIterator_<uchar> it, end;
		for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
			*it = table[*it];
		break;
	}
	case 3:
	{
		MatIterator_<Vec3b> it, end;
		for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
		{
			(*it)[0] = table[(*it)[0]];
			(*it)[1] = table[(*it)[1]];
			(*it)[2] = table[(*it)[2]];
		}
	}
	}
	return I;
}

// really slow way, but shows random access, in case we need that later.
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);
	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
				I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
		break;
	}
	case 3:
	{
		Mat_<Vec3b> _I = I;
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
			{
				_I(i, j)[0] = table[_I(i, j)[0]];
				_I(i, j)[1] = table[_I(i, j)[1]];
				_I(i, j)[2] = table[_I(i, j)[2]];
			}
		I = _I;
		break;
	}
	}
	return I;
}

Mat greyScale(Mat& img, int divWidth) {
	if (divWidth == 0) {
		cout << "Invalid number entered for dividing. " << endl;
		return img;
	}

	// Create a lookup table so that we don't have to * and / each pixel value
	uchar table[256];
	for (int i = 0; i < 256; ++i)
		table[i] = (uchar)(divWidth * (i / divWidth));

	// start timer
	double t = (double)getTickCount();
	
	Mat img_grey = ScanImageAndReduceC(img, table);

	// show how long it took
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "c method in seconds               : " << t << endl;


	t = (double)getTickCount();
	img_grey = ScanImageAndReduceIterator(img, table);
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "iterator method passed in seconds : " << t << endl;


	t = (double)getTickCount();
	img_grey = ScanImageAndReduceRandomAccess(img, table);
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "row col method passed in seconds  : " << t << endl;


	return img_grey;

}
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

	Mat img3 = imread("images/fruit.png");
	windowName = "Original Fruit";
	namedWindow(windowName);
	imshow(windowName, img3);

	Mat img_grey = greyScale(img3, 86);
	windowName = "Reduced Fruit";
	namedWindow(windowName);
	imshow(windowName, img3);

	// generate a window
	Mat image = Mat::zeros(300, 600, CV_8UC3);
	circle(image, Point(250, 150), 100, Scalar(0, 255, 128), -100);
	circle(image, Point(350, 150), 100, Scalar(255, 255, 255), -100);
	imshow("Display Window", image);

	// save a file
	bool isSaved = imwrite("./MyImage.jpg", img3); // save as JPEG, we can use other filenames to save as alt formats, like .png
	
	if (isSaved == false) {

		cout << "Failed to save the image" << endl;
		cin.get(); //wait for a key press
	}
	else {
		cout << "Image is succusfully saved to a file" << endl;
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
