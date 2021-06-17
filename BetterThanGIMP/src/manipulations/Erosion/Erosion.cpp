//
// Created by yakiimo on 6/17/21.
//

#include "Erosion.h"
#include <QSlider>
#include <QHBoxLayout>
#include "../../component/Slider/Slider.h"
#include <opencv2/opencv.hpp>

using namespace cv;

Erosion::Erosion(Workspace &w) : Manipulation(w){
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

Mat Erosion::erosion(Mat &image, int inputSize){

    Mat imageDestination;
    Size erosionSize = Size(inputSize,inputSize);
    Mat kernel = getStructuringElement(MORPH_ERODE,erosionSize);
    erode(image,imageDestination,kernel);

    return imageDestination;
}

Mat Erosion::applyManipulation() {
    return erosion(this->imageSavedInMemory, this->inputSize);
};