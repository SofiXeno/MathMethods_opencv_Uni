/**
 * @author Sofia Xenofontova
 */

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>


using namespace cv;

void display(const Mat &img, const char *const msg) {
    imshow(msg, img);


}

//cv::Mat bigger(cv::Mat Image) {
//    cv::Mat jumbo(Image.rows * 2, Image.cols * 2, CV_8UC1, cv::Scalar(0));
//    for (int i = 0; i < Image.rows; ++i) {
//        for (int j = 0; j < Image.cols; ++j) {
//            jumbo.data[i * Image.cols * 4 + j * 2] = Image.data[i * Image.cols + j];
//            jumbo.data[i * Image.cols * 4 + j * 2 + 1] = Image.data[i * Image.cols + j];
//            jumbo.data[i * Image.cols * 4 + j * 2 + 1 + jumbo.cols] = Image.data[i * Image.cols + j];
//            jumbo.data[i * Image.cols * 4 + j * 2 + jumbo.cols] = Image.data[i * Image.cols + j];
//        }
//    }
//    return jumbo;
//}
cv::Mat bigger(cv::Mat image) {
    cv::Mat image2(image.rows * 4, image.cols * 4, CV_8UC1, cv::Scalar(0));
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            image2.data[i * image.cols * 16 + j * 4] = image.data[i * image.cols + j];
            image2.data[i * image.cols * 16 + j * 4 + 1] = image.data[i * image.cols + j];
            image2.data[i * image.cols * 16 + j * 4 + 1 + image2.cols] = image.data[i * image.cols + j];
            image2.data[i * image.cols * 16 + j * 4 + image2.cols] = image.data[i * image.cols + j];
            image2.data[i * image.cols * 16 + j * 4 + 2] = image.data[i * image.cols + j];
            image2.data[i * image.cols * 16 + j * 4 + 3] = image.data[i * image.cols + j];
            image2.data[i * image.cols * 16 + j * 4 + 2 + image2.cols] = image.data[i * image.cols + j];
            image2.data[i * image.cols * 16 + j * 4 + 3 + image2.cols] = image.data[i * image.cols + j];

            image2.data[i * image.cols * 16 + j * 4 + image2.cols * 2] = image.data[i * image.cols + j];
            image2.data[i * image.cols * 16 + j * 4 + 1 + image2.cols * 2] = image.data[i * image.cols + j];
            image2.data[i * image.cols * 16 + j * 4 + 1 + image2.cols * 3] = image.data[i * image.cols + j];
            image2.data[i * image.cols * 16 + j * 4 + image2.cols * 3] = image.data[i * image.cols + j];
            image2.data[i * image.cols * 16 + j * 4 + 2 + image2.cols * 2] = image.data[i * image.cols + j];
            image2.data[i * image.cols * 16 + j * 4 + 3 + image2.cols * 2] = image.data[i * image.cols + j];
            image2.data[i * image.cols * 16 + j * 4 + 2 + image2.cols * 3] = image.data[i * image.cols + j];
            image2.data[i * image.cols * 16 + j * 4 + 3 + image2.cols * 3] = image.data[i * image.cols + j];
        }
    }
    return image2;
}


void logar(Mat image) {
    for (int i = 0; i < image.rows * image.cols; ++i) {
       image.data[i] = log(pow(0.4, image.data[i] + 1));
//     image.data[i] = 0.4*log(image.data[i] + 1);
    }
}

void negative(Mat negativeImage) {
    for (int i = 0; i < negativeImage.rows * negativeImage.cols; ++i) {
        negativeImage.data[i] = 255 - negativeImage.data[i];
    }
}

void smaller(Mat image, Mat image1) {
    for (int i = 0; i < image1.cols; i++) {
        for (int j = 0; j < image1.rows; j++) {
            image1.data[i * image1.cols + j] = image.data[(i * image1.cols * 4 + j * 2)];
        }
    }
}

int main() {
    Mat image = imread("../IM15.tif", IMREAD_GRAYSCALE);
    Mat image1(image.rows / 2, image.cols / 2, CV_8UC1, Scalar(0));
    Mat image2(image.rows * 4, image.cols * 4, CV_8UC1, Scalar(0));
    String imageName("../IM15.tif");

    Mat negativeImage = imread(imageName.c_str(), IMREAD_GRAYSCALE);
    Mat logarImage = imread(imageName.c_str(), IMREAD_GRAYSCALE);


//    for (int i = 0; i < image.cols; i++) {
//        for (int j = 0; j < image.rows; j++) {
//            image2.data[i * image2.cols * 2 + j * 2] = image.data[i * image.cols + j];
//            image2.data[i * image2.cols * 2 + j * 2 + 1] = image.data[i * image.cols + j];
//            image2.data[i * image2.cols * 2 + j * 2 + image2.cols] = image.data[i * image.cols + j];
//            image2.data[i * image2.cols * 2 + j * 2 + image2.cols + 1] = image.data[i * image.cols + j];
//
//
//
////            image.data[i] = image.data[i * image.cols + j + 1];
//        }
//    }

    display(image, "Original");


    logar(logarImage);
    display(logarImage, "Logar");
    negative(negativeImage);
    display(negativeImage, "Negative");


    image2=bigger(image);
    display(image2, "Bigger");
    smaller(image, image1);
    display(image1, "Smaller");

    waitKey(0);
    return 0;
}