#include <opencv2/opencv.hpp>

using namespace cv;

cv::Mat image_to_gray(cv::Mat image)
{
    /*
	if (image.data)
	{
		printf(" No image data \n ");
		exit(-1);
	}
     */

	cv::Mat gray_image;
	cv::cvtColor(image, gray_image, COLOR_BGR2GRAY);
	imwrite("output_gray_image.jpg", gray_image);

	return gray_image;
};
