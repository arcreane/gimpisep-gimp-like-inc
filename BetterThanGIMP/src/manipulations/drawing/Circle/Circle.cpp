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

Mat Circle::drawCircle(Mat &image, Point center, Point end, int size, Scalar color) {
    Mat result;
    image.copyTo(result);

    // Calculate radius of the circle
    float radius = sqrt(pow(center.x - this->mouseCoordinates.x, 2) +
                        pow(center.y - this->mouseCoordinates.y, 2));

    // Draw the circle
    cv::circle(result, center, radius, color, size);
    return result;
}

Mat Circle::applyManipulation() {
    return drawCircle(this->imageSavedInMemory, this->center, this->mouseCoordinates, this->brushSize,
                      Scalar(this->blue, this->green, this->red));
};
