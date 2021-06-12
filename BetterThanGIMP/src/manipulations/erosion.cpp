//
// Created by yakiimo on 6/7/21.
//
#include <opencv2/opencv.hpp>

cv::Mat erosion(cv::Mat imageInput, cv::Mat kernel, int iteration){
    cv :: Mat imageDestination;
    cv::erode(imageInput,imageDestination,kernel,cv::Point(-1,-1) ,iteration);

    return imageDestination;
}
