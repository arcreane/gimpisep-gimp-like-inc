//
// Created by yakiimo on 6/7/21.
//
cv::Mat dilate(cv::Mat imageInput, cv::Mat kernel, int iteration){
    cv :: Mat imageDestination;
    cv::dilate(imageInput, imageDestination,kernel,cv::Point(-1,-1) ,iteration);

    return imageDestination;
}