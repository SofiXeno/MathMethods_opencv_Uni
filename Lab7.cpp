//
// Created by Софія Ксенофонтова  on 2019-11-10.
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

bool isNeighbour(const Mat &in, Mat &out, const int index, const int cm) {
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int temppix = index + i * in.cols + j;
            if (i == 0 && j == 0)
                continue;
            if (temppix < 0 || temppix >= in.rows * in.cols)
                return false;
            if (out.data[index + i * in.cols + j] == c1m)
                return true;
        }
    }
    return false;
}

void regions(const Mat &in, Mat &out, const int cm, const int tr) {

    int temppix;
    bool haveToContinue = true;

    while (haveToContinue) {

        haveToContinue = false;

        for (int i = 0; i < in.rows; ++i) {
            for (int j = 0; j < in.cols; ++j) {

                temppix = i * in.cols + j;

                if (out.data[temppix] == 0 && isNeighbour(in, out, temppix, cm) && abs(in.data[temppix] - cm) < tr) {
                    out.data[temppix] = cm;
                    haveToContinue = true;
                }

            }
        }
    }
    //cout << "uspih" << endl;


}

void regGrowth(const Mat &in, const int tr) {
    Mat out(in.rows, in.cols, CV_8UC1, Scalar(0));

    int cm = 255;
    while (cm > 0) {


        for (int i = 0; i < in.rows; ++i) {
            for (int j = 0; j < in.cols; ++j) {
                int index = i * in.cols + j;
                if (in.data[index] == cm && out.data[index] == 0)
                    out.data[index] = cm;
            }
        }
        regions(in, out, cm, tr);
        --cm;
    }
    imshow("In", in);
    imshow("Out", out);

}

int main() {
    Mat image = imread("../Geneva.tif", IMREAD_GRAYSCALE);
    regGrowth(image, 150);
    waitKey(0);
    return 0;
}
