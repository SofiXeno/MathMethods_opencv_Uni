//
// Created by Софія Ксенофонтова  on 2019-11-10.
//
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include "Lab7.cpp"
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

int* createHist(const Mat& in){
    int* hist = new int[256]{};
    for (int i = 0; i < in.rows * in.cols; ++i)
        ++hist[in.data[i]];
    return hist;
}

int iterAlg(const Mat& in) {
    int* hist = createHist(in);
    int t1 = 0;
    int t2 = 0;
    int s1 = 0;
    int s2 = 0;
    int n1 = 0;
    int n2 = 0;

    for (int i = 1; i < 256; ++i)
        t1 += hist[i] * i;
    t1 /= in.rows * in.cols;
    do {
        n1 = 0;
        n2 = 0;
        s1 = 0;
        s2 = 0;
        t2 = t1;
        for (int i = 1; i < t1; ++i) {
            s1 += hist[i] * i;
            n1 += hist[i];
        }
        for (int i = t1; i < 256; ++i) {
            s2 += hist[i] * i;
            n2 += hist[i];
        }
        s1 /= n1;
        s2 /= n2;
        t1 = (s1 + s2) / 2;
    } while (t1 != t2);

    return t1;
}

void testIterAlg(const Mat& in) {
    int optimalTr = iterAlg(in);
    regGrowth(in, optimalTr);
    Mat out(in.rows, in.cols, CV_8UC1, Scalar(0));

    threshold(in, out, optimalTr, 255, THRESH_BINARY_INV);
    imshow("System binary", out);


}
//int main() {
//    Mat image = imread("../Geneva.tif", IMREAD_GRAYSCALE);
//    testIterAlg(image);
//    waitKey(0);
//    return 0;
//}
