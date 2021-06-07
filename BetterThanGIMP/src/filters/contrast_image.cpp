#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

cv::Mat image_to_bright(cv::Mat image)
{
   // Read the image file

    // Check for failure

    Mat bright_image = Mat::zeros(Size(image.cols, image.rows), image.type());

    //increase the brightness by 50

    image.convertTo(bright_image, -1, 1, 50);

    imwrite("output_bright_image.jpg", bright_image);

    return bright_image;
}
