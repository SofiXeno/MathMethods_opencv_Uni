//
// Created by Софія Ксенофонтова  on 2019-11-05.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
const int MATRIX_SIDE = 3;
unsigned char erosion(const Mat& in, const int index) {

    for (int k = -MATRIX_SIDE/2; k <= MATRIX_SIDE/2; ++k) {
        for (int l = -MATRIX_SIDE/2; l <= MATRIX_SIDE/2; ++l) {
            int index2 = index + k * in.cols + l;
            if (index2 < 0 || index2 > in.rows * in.cols)
                return in.data[index2];
            if (in.data[index2] != 255)
                return 0;
        }
    }
    return 255;
}

unsigned char dylatation(const Mat& in, const int index) {
    for (int k = -MATRIX_SIDE / 2; k <= MATRIX_SIDE / 2; ++k) {
        for (int l = -MATRIX_SIDE / 2; l <= MATRIX_SIDE / 2; ++l) {
            int index2 = index + k * in.cols + l;
            if (index2 < 0 || index > in.rows * in.cols)
                continue;
            if (in.data[index2]== 255)
                return 255;
        }
    }
    return 0;

}

void applyAlg(const Mat& in, Mat& out, const bool erode) {
    for (int i = 0; i < in.rows; ++i) {
        for (int j = 0; j < in.cols; ++j) {
            int index = i * in.cols + j;
            if(erode)
                out.data[index] = erosion(in, index);
            else
                out.data[index] = dylatation(in, index);
        }
    }

}
void findContour(const Mat& in) {
    for (int i = 0; i < in.rows * in.cols; ++i) {
        if (in.data[i] > 0)
            in.data[i] = 255;
    }
    imshow("Original", in);
    Mat eroded(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat dylatated(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat dylatatedContour(in.rows, in.cols, CV_8UC1, Scalar(0));

    Mat erodedContour(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat out(in.rows, in.cols, CV_8UC1, Scalar(0));

    applyAlg(in, eroded, true);

    imshow("Erosion", eroded);
    for (int i = 0; i < in.rows*in.cols; ++i)
        erodedContour.data[i] = in.data[i] - eroded.data[i];
    imshow("Erosion Contour", erodedContour);

    applyAlg(in, dylatated, false);
    imshow("Dylatation", dylatated);
    for(int i = 0; i<in.rows*in.cols; ++i)
        dylatatedContour.data[i] =  dylatated.data[i] - in.data[i];
    imshow("Dylatation Contour", dylatatedContour);
    for (int i = 0; i < in.rows * in.cols; ++i)
        out.data[i] = erodedContour.data[i] + dylatatedContour.data[i];
    imshow("Res", out);
}

int main() {
    Mat image = imread("../contour.tif", IMREAD_GRAYSCALE);
    findContour(image);
    waitKey(0);
    return 0;
}



