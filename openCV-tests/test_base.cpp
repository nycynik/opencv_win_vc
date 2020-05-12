#include "pch.h"
#include "../opencv_win_vc/MyOCV_ImageIO.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

TEST(TestBaseName, TestName) {

    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
    EXPECT_TRUE(MyOCV_ImageIO::test());
}

TEST(TestBaseName, TestCroppingBounds) {

    Mat image = Mat::zeros(300, 600, CV_8UC3);
    circle(image, Point(250, 150), 100, Scalar(0, 255, 128), -100);
    circle(image, Point(350, 150), 100, Scalar(255, 255, 255), -100);

    Mat dst;
    EXPECT_ANY_THROW(MyOCV_ImageIO::cropImage(dst, image, 0, 0, 100, 700));
    EXPECT_ANY_THROW(MyOCV_ImageIO::cropImage(dst, image, 0, 0, 700, 100));
    EXPECT_ANY_THROW(MyOCV_ImageIO::cropImage(dst, image, -100, 0, 100, 100));
    EXPECT_ANY_THROW(MyOCV_ImageIO::cropImage(dst, image, 0, -1, 100, 100));

}