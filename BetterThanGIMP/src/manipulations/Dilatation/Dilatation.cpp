//
// Created by yakiimo on 6/17/21.
//

#include "Dilatation.h"
#include <QSlider>
#include <QHBoxLayout>
#include "../../component/Slider/Slider.h"
#include <opencv2/opencv.hpp>

using namespace cv;

Dilatation::Dilatation(Workspace &w) : Manipulation(w){
    this->name = "Erosion";
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

Mat Dilatation::dilatation(Mat &image, int inputSize){

    Mat imageDestination;
    Size dilatationSize = Size(inputSize,inputSize);
    Mat kernel = getStructuringElement(MORPH_DILATE,dilatationSize);
    dilate(image,imageDestination,kernel);

    return imageDestination;
}

Mat Dilatation::applyManipulation() {
    return dilatation(this->imageSavedInMemory, this->inputSize);
};
