//
// Created by yakiimo on 6/17/21.
//

#include <opencv2/imgproc.hpp>

#include "Box.h"

Box::Box(Workspace &w) : Drawing(w) {
    this->name = "Box";

    connect(&this->workspace, &Workspace::mousePressed, this, [this](Point coordinates) {
        this->startCorner = coordinates;
    });

    connect(&this->workspace, &Workspace::mouseMoved, this, [this](Point coordinates) {
        this->mouseCoordinates = coordinates;
        this->updateImageDisplay();
    });


    connect(&this->workspace, &Workspace::mouseReleased, this, [this]() {
        //TODO Implement memory saving in a more elegant way
        this->imageSavedInMemory = applyManipulation();
    });
}

Mat Box::applyManipulation() {
    Mat result;
    this->imageSavedInMemory.copyTo(result);

    // Draw the rectangle
    cv::rectangle(result, this->startCorner, this->mouseCoordinates, Scalar(this->blue, this->green, this->red),
                  this->brushSize);
    return result;
};
