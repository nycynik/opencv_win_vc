#include "MyOCV_ImageIO.hpp"

using namespace cv;
using namespace std;

int MyOCV_ImageIO::test()
{
	return 1;
}

int MyOCV_ImageIO::loadImage(Mat& img, String pathname) {

	img = imread(pathname); // "images/bicycle.png");
	if (img.empty()) {
		//failed to load
		cerr << "Image not found." << endl;
		return -1;
	}

	return 0;
}

int MyOCV_ImageIO::saveImage(Mat img, String pathname) {

	if (imwrite("./MyImage.jpg", img)) {

		// saved
		return 0;

	} else {

		// not saved
		cerr << "Image was not saved" << endl;
		return -1;
	}

}

// Image manipulation
int MyOCV_ImageIO::cropImage(Mat& dst, Mat src, long x, long y, long width, long height) {
	
	// check that x,y,w,h are all in the mat bounds.
	if (x < 0 || y < 0 || width > src.cols || height > src.rows) {
		throw new Exception();
	}

	// now crop
	cv::Rect cropROI(x, y, width, height);
	dst = src(cropROI);
	
	return 0;

}

Mat MyOCV_ImageIO::blend(Mat a, Mat b, double alpha) {

	if (a.rows != b.rows || a.cols != b.cols) {
		throw new Exception();
	}

	Mat dst;
	addWeighted(a, alpha, b, (1.0 - alpha), 0.0, dst);
	return dst;
}

// fastest way to scan an image and do some operation on it
Mat& MyOCV_ImageIO::scanImageAndReduce(Mat& I, const uchar* const table)
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

Mat MyOCV_ImageIO::reduce(Mat& img, int divWidth) {

	if (divWidth == 0) {
		cerr << "Invalid number entered for dividing. " << endl;
		return img;
	}

	// Create a lookup table so that we don't have to * and / each pixel value
	uchar table[256];
	for (int i = 0; i < 256; ++i)
		table[i] = (uchar)(divWidth * (i / divWidth));

	Mat img_grey = MyOCV_ImageIO::scanImageAndReduce(img, table);

	return img_grey;

}

