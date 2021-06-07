#include <opencv2/opencv.hpp>

using namespace cv;

Mat cannyEdge(Mat image, int threshold1, int threshold2, int kernelSize) {
    cvtColor(image, image, COLOR_BGR2GRAY);
    GaussianBlur(image, image, Size(kernelSize, kernelSize), 0);
    Canny(image, image, threshold1, threshold2, kernelSize, false);
    return image;
}