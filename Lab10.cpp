//
// Created by Софія Ксенофонтова  on 2019-11-18.
//
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include "header.h";
#include <opencv2/imgproc.hpp>
#include <cassert>
#include<stack>
#pragma once
using namespace cv;
using namespace std;
stack<int> contourX;
stack<int> contourY;
vector<Point2d> V;
int K = 2;
bool isContour(const Mat& in, const int i, const int j) {
    if (i < 0 || i >= in.rows || j < 0 || j >= in.cols || in.data[i * in.cols + j] != 255)
        return false;
    for (int y = -1; y <= 1; ++y) {
        for (int x = -1; x <= 1; ++x) {
            if (x == 0 && y == 0)
                continue;
            int temppix = (y + i) * in.cols + (x + j);
            if (i + y < 0 || j + x < 0 || i + y >= in.rows || j + x >= in.cols || in.data[temppix] == 0)
                return true;
        }
    }
    return false;
}

int determine(const Mat& in, int& i, int& j, const int dir) {
    switch (dir) {
        case 0: {
            ++j;
            break;
        }
        case 1: {
            --i;
            ++j;
            break;
        }
        case 2: {
            --i;
            break;
        }
        case 3: {
            --i;
            --j;
            break;
        }
        case 4: {
            --j;
            break;
        }
        case 5: {
            ++i;
            --j;
            break;
        }
        case 6: {
            ++i;
            break;
        }
        case 7: {
            ++i;
            ++j;
            break;
        }
    }
    return i * in.cols + j;

}
void createContour(const Mat& in, Mat& out, int i, int j) {
    const int index = i * in.cols + j;
    int temppix;
    int dir = 7;
    int tempDir;
    int ii = i;
    int jj = j;
    do {
        tempDir = dir % 2 == 0 ? (dir + 7) % 8 : (dir + 6) % 8;
        for (int k = 0; k < 8; ++k) {
            temppix = determine(in, ii, jj, tempDir);
            if (isContour(in, ii, jj)) {
                out.data[temppix] = 255;
                contourX.push(ii);
                contourY.push(jj);
                dir = tempDir;
                i = ii;
                j = jj;
                V.push_back(Point2d(i, j));
                break;
            }
            else {
                ++tempDir;
                tempDir %= 8;
                ii = i;
                jj = j;
                temppix = ii * in.cols + jj;
            }
        }
        ii = i;
        jj = j;
    } while (index != temppix);
}


void findContourHistogram(int k)
{
    const int length = V.size();
    vector<double> res;

    for (int i = k; i < length - k; i++) {
        Point2d cur = V[i];
        Point2d next = V[i + k];
        Point2d prev = V[i - k];
        Point2d forward_vec = Point2d(cur.x - next.x, cur.y - next.y);
        Point2d backward_vec = Point2d(cur.x - prev.x, cur.y - prev.y);
        double f_dist = sqrt(forward_vec.x * forward_vec.x + forward_vec.y * forward_vec.y);
        double b_dist = sqrt(backward_vec.x * backward_vec.x + backward_vec.y * backward_vec.y);
        //cout << f_dist << " " << b_dist << endl;
        double arg_f = atan2(abs(next.x - cur.x), abs(next.y - cur.y));
        double arg_b = atan2(abs(prev.x - cur.x), abs(prev.y - cur.y));

        double arg_cur = (arg_f + arg_b) / 2;
        double diff_f = arg_f - arg_cur;

        res.push_back(diff_f * (b_dist + f_dist) / (2 * b_dist * f_dist));
    }

    //for (int i = 0; i < res.size(); i++)
    //  cout << res[i] << " ";
    int arrLength = res.size();
    int height =300;
    int width = arrLength;
    Mat gist(height, width, CV_8UC1, Scalar(0));
    //int thick = 1;
    line(gist, Point(0, 150), Point(width - 10, 150), 255);

    for (int i = 0, x = 1; i < arrLength; i++, x++)
        line(gist, Point(x, height / 2), Point(x, height / 2 + res[i] * 80), 255);
    imshow("Curve Graph", gist);

}
void traceContours(const Mat& in) {
    Mat binaryIn(in.rows, in.cols, CV_8UC1, Scalar(0));
    threshold(in, binaryIn, 127, 255, THRESH_BINARY);
    Mat out(in.rows, in.cols, CV_8UC1, Scalar(0));

    for (int i = 0; i < in.rows; ++i) {
        for (int j = 0; j < in.cols; ++j) {
            int index = i * in.cols + j;
            if (binaryIn.data[index] == 255 && (j == 0 || binaryIn.data[index - 1] == 0) && out.data[index] != 255)
                createContour(binaryIn, out, i, j);
        }
    }
    int length = contourX.size();
    int* xAx = new int[length];
    int* yAx = new int[length];
    //double* kurwa = new double[length];
    for (int i = 0; i < length; ++i) {
        xAx[i] = contourX.top();
        contourX.pop();
        yAx[i] = contourY.top();
        contourY.pop();
    }
    imshow("In", in);
    imshow("Binary In", binaryIn);
    imshow("Out", out);
    findContourHistogram(1);

}

int main() {
    Mat image = imread("../Circle.png", IMREAD_GRAYSCALE);
    traceContours(image);
    waitKey(0);
    return 0;
}



