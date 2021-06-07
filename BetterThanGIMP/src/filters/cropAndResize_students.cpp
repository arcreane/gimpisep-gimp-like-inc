#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//int main(void)
//{
//Mat source, scaleD, scaleU;
//
//// Read source image
//source = imread("HappyFish.jpg");
//
//// Scaling factors
//double scaleX = 0.6;
//double scaleY = 0.6;
//
//Mat scaledImage;
//
//resize(source, scaledImage, Size(), scaleX, scaleY, INTER_LINEAR);
//
//// Scaling down the image 0.6 times
//
//Mat downsizedImage;
//
//resize(source, downsizedImage, Size(source.cols * 0.6, source.rows * 0.6), 0, 0, INTER_LINEAR);
//
//
//// Scaling up the image 1.8 times
//
//Mat upsizedImage;
//
//resize(source, upsizedImage, Size(source.cols * 1.8, source.rows * 1.8), 0, 0, INTER_LINEAR);
//
//
////Cropped image
//Range rows(1, source.rows-100);
//Range cols(1, source.cols-100);
//Mat crop = source(rows, cols);
//
//
//
////Display windows and show for all four images
//
//namedWindow("Scaled Image", WINDOW_AUTOSIZE);
//imshow("Scaled Image", scaledImage);
//
//namedWindow("Downsized Image", WINDOW_AUTOSIZE);
//imshow("Downsized Image", downsizedImage);
//
//namedWindow("Upsized Image", WINDOW_AUTOSIZE);
//imshow("Upsized Image", upsizedImage);
//
//namedWindow("Cropped Image", WINDOW_AUTOSIZE);
//imshow("Cropped Image", crop);
//
//waitKey(0);
//
//}
