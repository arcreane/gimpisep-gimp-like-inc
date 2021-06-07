//
// Created by yakiimo on 6/7/21.
//
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

/* Option 0 for resizing with dimensions, option 1 for resizing with a factor */
cv::Mat resizing(Mat input, Mat output,double scaleX, double scaleY, int option){
	double input_height = input.size().height;
	double input_width = input.size().width;

	if (option == 0) {
		/* Resize down*/
		if (input_height * input_width < scaleX * scaleY) {
			resize(input, output, Size(scaleX, scaleY), INTER_AREA);
		}
		/* Resize up*/
		else if (input_height * input_width > scaleX * scaleY) {
			resize(input, output, Size(scaleX, scaleY), INTER_CUBIC);
		}
		/* Same size*/
		else {
			resize(input, output, Size(scaleX, scaleY), INTER_LINEAR);
		}
	}
	else if (option == 1) {
		/* Rescale down*/
		if (input_height * input_width < scaleX * scaleY) {
			resize(input, output, Size(0, 0), scaleX, scaleY, INTER_AREA);
		}
		/* Rescale up*/
		else if (input_height * input_width > scaleX * scaleY) {
			resize(input, output, Size(0, 0), scaleX, scaleY, INTER_CUBIC);
		}
		/* Same size*/
		else {
			resize(input, output, Size(0, 0), scaleX, scaleY, INTER_LINEAR);
		}
	}
	else {
		throw;
	}
	return output;
}

