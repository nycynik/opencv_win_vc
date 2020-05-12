#include "pch.h"
#include "../opencv_win_vc/MyOCV_ImageIO.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

TEST(TestCaseCropping, TestCroppingBounds) {

    Mat image = Mat::zeros(300, 600, CV_8UC3);
    circle(image, Point(250, 150), 100, Scalar(0, 255, 128), -100);
    circle(image, Point(350, 150), 100, Scalar(255, 255, 255), -100);

    Mat dst;
    EXPECT_ANY_THROW(MyOCV_ImageIO::cropImage(dst, image, 0, 0, 100, 700));
    EXPECT_ANY_THROW(MyOCV_ImageIO::cropImage(dst, image, 0, 0, 700, 100));
    EXPECT_ANY_THROW(MyOCV_ImageIO::cropImage(dst, image, -100, 0, 100, 100));
    EXPECT_ANY_THROW(MyOCV_ImageIO::cropImage(dst, image, 0,-1, 100, 100));

}

TEST(TestCaseCropping, TestCrop) {

    Mat image = Mat::zeros(300, 600, CV_8UC3);
    circle(image, Point(250, 150), 100, Scalar(0, 255, 128), -100);
    circle(image, Point(350, 150), 100, Scalar(255, 255, 255), -100);

    Mat dst;
    MyOCV_ImageIO::cropImage(dst, image, 0, 0, 5, 10);
    EXPECT_EQ(dst.cols, 5);
    EXPECT_EQ(dst.rows, 10);

}

