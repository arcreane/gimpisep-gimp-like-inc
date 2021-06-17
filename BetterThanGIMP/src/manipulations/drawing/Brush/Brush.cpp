//
// Created by Hugues Baratgin on 16/06/2021.
//


#include <opencv2/opencv.hpp>

#include "Brush.h"

using namespace cv;

Brush::Brush(Workspace &w) : Drawing(w) {
    this->name = "Brush";

    connect(&this->workspace, &Workspace::mouseMoved, this, [this](Point coordinates) {
        this->mouseCoordinates = coordinates;
        this->updateImageDisplay();
    });
}

Mat Brush::draw(Mat &image, Point coord, int size, Scalar color) {
    Mat result;
    image.copyTo(result);
    circle(result, coord, size, color, FILLED);
    if(result.empty()){
        std::cout << "EMPTY" << std::endl;
    }
    return result;
}

Mat Brush::applyManipulation() {
    return draw(this->imageModified, this->mouseCoordinates, this->brushSize,
                Scalar(this->blue, this->green, this->red));
};
