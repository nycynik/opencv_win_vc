#include "pch.h"

#include "../opencv_win_vc/MyOCV_ImageIO.hpp"

TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(TestCaseName, TestName2) {
    printf("running");

    int z = 1; // MyOCV_ImageIO::test();
    EXPECT_EQ(z, 0);

}

/*

struct SomethingWeWantToTest {
    SomethingWeWantToTest() : m_value(1) {}
    int m_value;
};

TEST(TestCaseName, TestName3) {

    SomethingWeWantToTest testObject;

    printf("running");

    EXPECT_EQ(testObject.m_value, 0);

    EXPECT_EQ(testObject.m_value, 1);

}

*/
