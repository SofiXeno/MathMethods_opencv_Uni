
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <math.h>
#include <cmath>

using namespace cv;


const int MASK = 3;
const double KOEF = 0.7;

int convolution(int x, int y, int *kernel, Mat &in) {
    int pixelSum = 0;
    for (int i = 0; i < MASK; ++i) {
        for (int j = 0; j < MASK; ++j) {
            pixelSum += kernel[i + j * (MASK)] * in.data[(x - MASK / 2) + (y - MASK / 2) * in.cols + i + j * in.cols];
        }
    }
    return pixelSum;
}

double toDegrees(double rad) {
    return 180 * rad / M_PI;
}

int determineDegr(double d) {
    for (int res = 0; res < 360; res += 45) {
        if (d < 22.5 + res)
            return res;
    }
    return -1;
}

int *SobelOperator(Mat &in, Mat &out) {
    Mat outP(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat outA(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat outS(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat gx(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat gy(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat grad_x(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat grad_y(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat grad_x_abs(in.rows, in.cols, CV_8UC1, Scalar(0));
    Mat grad_y_abs(in.rows, in.cols, CV_8UC1, Scalar(0));
    int maskX[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int maskY[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    int *array = new int[in.rows * in.cols];
    for (int i = 0; i < in.cols; ++i) {
        for (int j = 0; j < in.rows; ++j) {
            gx.data[i + j * gx.cols] = convolution(i, j, maskX, in) * KOEF;
        }
    }


    for (int i = 0; i < in.cols; ++i) {
        for (int j = 0; j < in.rows; ++j) {
            gy.data[i + j * gy.cols] = convolution(i, j, maskY, in) * KOEF;
        }
    }


    for (int i = 0; i < in.cols; ++i) {
        for (int j = 0; j < in.rows; ++j) {
            int pixelX = convolution(i, j, maskX, in) * KOEF;
            int pixelY = convolution(i, j, maskY, in) * KOEF;
            int degr = toDegrees(atan2(pixelY, pixelX));
            degr %= 180;
            if (degr < 0) {
                degr = 180 + degr;
            }
            degr %= 180;
            degr = determineDegr(degr);
            //cout << degr << endl;
            array[i + j * out.cols] = degr;
            out.data[i + j * out.cols] = round(sqrt(pixelX * pixelX + pixelY * pixelY));
            //out.data[i + j * out.cols] = abs(pixelX) + abs(pixelY);
        }
    }
    imshow("Original", in);
    imshow("Gx", gx);
    imshow("Gy", gy);

    return array;



//    imshow("Out Pythagorean", outP);
//    imshow("Out Abs", outA);


//    Sobel(in, grad_x, CV_16S, 1, 0);
//    Sobel(in, grad_y, CV_16S, 1, 0);
//    convertScaleAbs(grad_x, grad_x_abs);
//
//    convertScaleAbs(grad_y, grad_y_abs);
//    addWeighted(grad_x_abs, 0.5, grad_y_abs, 0.5, 0, outS);

    //  imshow("Out System", outS);
    return array;
}
//
//int main() {
//    Mat image = imread("../Geneva.tif", IMREAD_GRAYSCALE);
//    Mat image_out(image.rows, image.cols, CV_8UC1, Scalar(0));
//    SobelOperator(image, image_out);
//    waitKey(0);
//    return 0;
//}
