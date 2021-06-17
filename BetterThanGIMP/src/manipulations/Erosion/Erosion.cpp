//
// Created by yakiimo on 6/17/21.
//

#include "Erosion.h"
#include <QSlider>
#include <QHBoxLayout>
#include <QComboBox>
#include <iostream>
#include "../../component/Slider/Slider.h"
#include <opencv2/opencv.hpp>

using namespace cv;

Erosion::Erosion(Workspace &w) : Manipulation(w){
    this->name = "Erosion";
    this->options->setLayout(new QHBoxLayout());


    this->inputSize = 1;

    this->inputKernel = MORPH_RECT;

    QComboBox *chooseKernel = new QComboBox();
    chooseKernel->addItem("RECT");
    chooseKernel->addItem("CROSS");
    chooseKernel->addItem("ELLIPSE");
    connect(chooseKernel, &QComboBox::currentTextChanged, this, [this, chooseKernel]() {
        this->inputKernel = chooseKernel->currentIndex();
        std::cout << chooseKernel->currentIndex() << std::endl;
        updateImageDisplay();
    });

    this->options->layout()->addWidget(chooseKernel);


    Slider *sliderErosionInput = new Slider("Erosion Size ", Qt::Vertical, 1, 50, this->inputSize);
    connect(sliderErosionInput->getSlider(), &QSlider::valueChanged, this, [this, sliderErosionInput](int val) {
        this->inputSize = val;
        sliderErosionInput->setCurrentValue(this->inputSize);
        updateImageDisplay();
    });
    this->options->layout()->addWidget(sliderErosionInput);
}

Mat Erosion::erosion(Mat &image, int inputKernel, int inputSize){

    Size erosionSize = Size(inputSize,inputSize);
    Mat imageDestination;
    Mat kernelErosion =  getStructuringElement(inputKernel, erosionSize);
    erode(image,imageDestination,kernelErosion);

    return imageDestination;
}

Mat Erosion::applyManipulation() {
    return erosion(this->imageSavedInMemory, this->inputKernel, this->inputSize);
};