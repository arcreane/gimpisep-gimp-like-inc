//
// Created by yakiimo on 6/17/21.
//

#include <opencv2/opencv.hpp>
#include <QHBoxLayout>

#include "../../component/Slider/Slider.h"
#include "Dilatation.h"

using namespace cv;

Dilatation::Dilatation(Workspace &w) : Manipulation(w) {
    this->name = "Dilatation";
    this->options->setLayout(new QHBoxLayout());


    this->inputSize = 0;


    Slider *sliderDilatationInput = new Slider("Dilatation Size ", Qt::Vertical, 1, 20, this->inputSize);
    connect(sliderDilatationInput->getSlider(), &QSlider::valueChanged, this, [this, sliderDilatationInput](int val) {
        this->inputSize = val;
        sliderDilatationInput->setCurrentValue(this->inputSize);
        updateImageDisplay();
    });
    this->options->layout()->addWidget(sliderDilatationInput);
}

Mat Dilatation::applyManipulation() {
    Mat imageDestination;
    Size dilatationSize = Size(this->inputSize, this->inputSize);
    Mat kernel = getStructuringElement(MORPH_DILATE, dilatationSize);
    dilate(this->imageSavedInMemory, imageDestination, kernel);

    return imageDestination;
};
