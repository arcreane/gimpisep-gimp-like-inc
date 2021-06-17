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

Mat Brush::applyManipulation() {
    Mat result;
    this->imageModified.copyTo(result);
    circle(result, this->mouseCoordinates, this->brushSize, Scalar(this->blue, this->green, this->red), FILLED);
    return result;
};
