//
// Created by Hugues Baratgin on 17/06/2021.
//

#include <opencv2/imgproc.hpp>

#include "Circle.h"

Circle::Circle(Workspace &w) : Drawing(w) {
    this->name = "Circle";

    connect(&this->workspace, &Workspace::mousePressed, this, [this](Point coordinates) {
        this->center = coordinates;
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

Mat Circle::applyManipulation() {
    Mat result;
    this->imageSavedInMemory.copyTo(result);

    // Calculate radius of the circle
    float radius = sqrt(pow(this->center.x - this->mouseCoordinates.x, 2) +
                        pow(this->center.y - this->mouseCoordinates.y, 2));

    // Draw the circle
    cv::circle(result, center, radius, Scalar(this->blue, this->green, this->red), this->brushSize);
    return result;
};
