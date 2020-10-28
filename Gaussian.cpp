//
// Created by Софія Ксенофонтова  on 2019-10-15.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

#define _USE_MATH_DEFINES

#include <math.h>
#include <cmath>

using namespace cv;

void gauss(Mat img);

//void GaussianBlur(const Mat &in_image, Mat &out_image, double sigma);

void convolution(const Mat &in, Mat &out, double koef, double kernel[], String name);



using namespace std;

const int MASK = 5;
const double KOEF = 1.3;


void gauss(Mat img) {
    int size;
    double sigma;
    Mat out(img.rows, img.cols, CV_8UC1, Scalar(0));
    cout << endl << "Введіть сигму: ";
    cin >> sigma;
    cout << endl;
    void GaussianBlur(const Mat &in_image, Mat &out_image, double sigma);
    GaussianBlur(img, out, sigma);

}

void GaussianBlur(const Mat &in_image, Mat &out_image, double sigma) {
    assert(MASK % 2 != 0);
    double gauss_mask[MASK * MASK] = {0};
    double sum = 0;
    for (int i = -MASK / 2; i <= MASK / 2; ++i) {
        for (int j = -MASK / 2; j <= MASK / 2; ++j) {
            double member = exp(
                    -((double) (((double) i * i + (double) j * j)))/ (2 * sigma * sigma))
                            / (2 * sigma * sigma * M_PI);
            gauss_mask[i + MASK / 2 + (j + MASK / 2) * MASK] = member;
            sum += member;
        }
    }
    for (int i = 0; i < MASK * MASK; ++i)
        cout << gauss_mask[i] << " ; ";
 //   double k = 1 / sum;
 double tempMask[25]={0};
    tempMask[0] = 1, tempMask[1] = 2, tempMask[2] = 3, tempMask[3] = 2, tempMask[4] = 1;
    tempMask[5] = 2, tempMask[6] = 4, tempMask[7] = 6, tempMask[8] = 4, tempMask[9] = 2;
    tempMask[10] = 3, tempMask[11] = 6, tempMask[12] = 9, tempMask[13] = 6, tempMask[14] = 3;
    tempMask[15] = 2, tempMask[16] = 4, tempMask[17] = 6, tempMask[18] = 4, tempMask[19] = 2;
    tempMask[20] = 1, tempMask[21] = 2, tempMask[22] = 3, tempMask[23] = 2,tempMask[24] = 1;

   convolution(in_image, out_image, KOEF, gauss_mask, "gauss");
    //convolution(in_image, out_image, 0.012, tempMask, "random mask conv");

    imshow("original", in_image);


}

void convolution(const Mat &in, Mat &out, double koef, double kernel[], String name) {
    double sum;
    int count1 = 0, count2 = 0;
    for (int i = 0; i < in.cols; ++i) {
        for (int j = 0; j < in.rows; ++j) {
            if (i <= MASK / 2 || j <= MASK / 2 || i >= in.cols - MASK / 2 || j >= in.rows - MASK / 2) {
                ++count2;
                out.data[i + j * in.cols] = in.data[i + j * in.cols] / KOEF;
                continue;
            }
            sum = 0;
            for (int k = 0; k < MASK; ++k) {
                for (int l = 0; l < MASK; ++l) {
                    sum += kernel[k + l * (MASK)] * in.data[i - MASK / 2 + (j - MASK / 2) * in.cols + k + l * in.cols];
                    ++count1;
                }
            }
            sum *= koef;
            //sum /= MASK * MASK;
            //cout << sum << endl;
            out.data[i + j * in.cols] = (sum > 255) ? 255 : (char) sum;
        }
    }
    //cout << count1 << endl << count2 << endl;
    imshow(name, out);

}


//
//int main() {
//    Mat image = imread("../Geneva.tif", IMREAD_GRAYSCALE);
//    gauss(image);
//    waitKey(0);
//    return 0;
//}