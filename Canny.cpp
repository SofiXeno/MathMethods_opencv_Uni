#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include "header.h";


#include <opencv2/imgproc.hpp>
using namespace cv;

const unsigned char LOW = 50;
const unsigned char HIGH = 150;


unsigned char myCompare(const Mat& in, int degr, int index) {
    int i1, i2;
    if (degr == 0) {
        i2 = index + 1; i1 = index - 1;
    }
    else if (degr == 45) {
        i1 = index + 1 - in.cols; i2 = index - 1 + in.cols;
    }
    else if (degr == 90) {
        i1 = index - in.cols; i2 = index + in.cols;
    }
    else if (degr == 135) {
        i1 = index - 1 - in.cols; i2 = index + 1 + in.cols;
    }
//    else {
//        std::cout << degr << std::endl;
//    }
    if(i1<0 || i2>in.rows*in.cols)
        return 0;
    if (in.data[i1] >= in.data[index] || in.data[i2] >= in.data[index])
        return 0;
    return in.data[index];

}


unsigned char determineThreshold(const Mat& in, int degr, int index) {
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int temp = index + i * in.cols + j;
            if (temp < 0 || temp > in.rows * in.cols)
                return 0;
            else if (in.data[temp] > HIGH)
                return 255;
        }

    }
    return 0;

}

void cannyAlg(Mat in) {
    Mat prepared1(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat prepared2(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat temp(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat out(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat sys(in.rows, in.cols, CV_8UC1, Scalar(0));
    GaussianBlur(in, prepared1, 1.4);
    int* dirs = SobelOperator(prepared1, prepared2);
    Canny(prepared2, sys, LOW, HIGH);

    imshow("Sobel", prepared2);
    imshow("Sytem", sys);
    for (int i = 0; i < in.rows; ++i) {
        for (int j = 0; j < in.cols; ++j) {
            int index = i * out.cols + j;
            int degr = dirs[index];
            temp.data[index] = myCompare(prepared2, degr, index);
        }
    }
    imshow("Local max suppression", temp);
    for (int i = 0; i < in.rows; ++i) {
        for (int j = 0; j < in.cols; ++j) {
            int index = i * out.cols + j;
            unsigned char pixel = temp.data[index];
            int degr = dirs[index];
            if (pixel <= LOW) {
                pixel = 0;
            }
            else if (pixel >= HIGH) {

                pixel = 255;

            }
            else
                pixel = determineThreshold(temp, degr, index);

            out.data[index] = pixel;
        }

    }
    imshow("Hystheresis threshold", out);

}

int main() {
    Mat image = imread("../Geneva.tif", IMREAD_GRAYSCALE);
    Mat image_out(image.rows, image.cols, CV_8UC1, Scalar(0));
    cannyAlg(image);
    waitKey(0);
    return 0;
}
