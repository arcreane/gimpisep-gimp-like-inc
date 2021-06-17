//
// Created by yakiimo on 6/17/21.
//

#include <opencv2/opencv.hpp>
#include <QHBoxLayout>

#include "Erosion.h"
#include "../../component/Slider/Slider.h"

using namespace cv;

Erosion::Erosion(Workspace &w) : Manipulation(w) {
    this->name = "Erosion";
    this->options->setLayout(new QHBoxLayout());


    this->inputSize = 0;


    Slider *sliderErosionInput = new Slider("Erosion Size ", Qt::Vertical, 1, 20, this->inputSize);
    connect(sliderErosionInput->getSlider(), &QSlider::valueChanged, this, [this, sliderErosionInput](int val) {
        this->inputSize = val;
        sliderErosionInput->setCurrentValue(this->inputSize);
        updateImageDisplay();
    });
    this->options->layout()->addWidget(sliderErosionInput);
}

Mat Erosion::applyManipulation() {
    Mat imageDestination;
    Size erosionSize = Size(this->inputSize, this->inputSize);
    Mat kernel = getStructuringElement(MORPH_ERODE, erosionSize);
    erode(this->imageSavedInMemory, imageDestination, kernel);

    return imageDestination;
};