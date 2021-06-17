//
// Created by yakiimo on 6/17/21.
//

#include "Dilatation.h"
#include <QSlider>
#include <QHBoxLayout>
#include <QComboBox>
#include "../../component/Slider/Slider.h"
#include <opencv2/opencv.hpp>

using namespace cv;

Dilatation::Dilatation(Workspace &w) : Manipulation(w){
    this->name = "Dilatation";
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


    Slider *sliderDilatationInput = new Slider("Dilatation Size ", Qt::Vertical, 1, 20, this->inputSize);
    connect(sliderDilatationInput->getSlider(), &QSlider::valueChanged, this, [this, sliderDilatationInput](int val) {
        this->inputSize = val;
        sliderDilatationInput->setCurrentValue(this->inputSize);
        updateImageDisplay();
    });
    this->options->layout()->addWidget(sliderDilatationInput);
}

Mat Dilatation::dilatation(Mat &image, int inputKernel, int inputSize){

    Size dilatationSize = Size(inputSize,inputSize);
    Mat imageDestination;
    Mat kernelDilatation = getStructuringElement(inputKernel, dilatationSize);
    dilate(image,imageDestination,kernelDilatation);

    return imageDestination;
}

Mat Dilatation::applyManipulation() {
    return dilatation(this->imageSavedInMemory, this->inputKernel, this->inputSize);
};
