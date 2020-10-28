//
// Created by Софія Ксенофонтова  on 2019-09-24.
//

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include<opencv2/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/photo.hpp>


int cdf(int a, int hist[]);

int findMinimumNonZero(int hist[]);

using namespace std;

void drawHist(int hist[], std::string msg);

using namespace cv;

Mat equalizeHist(const Mat eq, int hist[]);


Mat equalizeHist(const Mat eq, int hist[]) {
    Mat out = eq.clone();
    float alpha = (float) 255 / (eq.rows * eq.cols - 1);
    int cdfmin = findMinimumNonZero(hist);
    for (int i = 0; i < (eq.rows * eq.cols); ++i) {
        out.data[i] = round((float) (cdf(out.data[i], hist) - cdfmin)) * alpha;
    }
    return out;
}

void drawHist(int hist[], String msg) {
    int max = 0;
    for (int i = 0; i < 256; ++i) {
        if (hist[i] > max)
            max = hist[i];
    }

    Mat h(max, 256, CV_8UC1, Scalar(0));
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < max - hist[i]; ++j) {
            h.data[i + j * h.cols] = 34;
        }
    }

    resize(h, h, Size(512, 512), 1, 1);
    imshow(msg, h);

}

int cdf(int a, int hist[]) {
    int res = 0;
    for (int i = 0; i <= a; ++i) {
        res += hist[i];
    }
    return res;
}

int findMinimumNonZero(int hist[]) {
    int i = 0;
    while (hist[i] == 0) {
        ++i;
    }
    return i;
}

int main() {
    Mat image = imread("Geneva.tif", IMREAD_GRAYSCALE);

    if (!image.data) { return -1; }

    imshow("Original", image);

    int f[256] = {0};
    for (int i = 0; i < image.rows * image.cols; ++i) {
        ++f[image.data[i]];
    }

    drawHist(f, "Histogram");

    Mat out = equalizeHist(image, f);

    //int *g = getHist(out);

    int g[256] = {0};
    for (int i = 0; i < out.rows * out.cols; ++i) {
        ++g[out.data[i]];
    }

    drawHist(g, "Equalized histogram");
    imshow("Equalized image", out);
    // display(histogram, "Histogram");
    // equalizeHist(histogram);
    // display(histogram, "Equalized histogram");


    waitKey(0);
    return 0;
}