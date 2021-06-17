//
// Created by yakiimo on 6/17/21.
//

#include <opencv2/opencv.hpp>
#include <QHBoxLayout>
#include <QComboBox>

#include "Dilatation.h"
#include "../../component/Slider/Slider.h"


using namespace cv;

Dilatation::Dilatation(Workspace &w) : Manipulation(w) {
    this->name = "Dilatation";
    this->options->setLayout(new QVBoxLayout());


    this->inputSize = 1;

    this->inputKernel = MORPH_RECT;

    QComboBox *chooseKernel = new QComboBox();
    chooseKernel->addItem("RECT");
    chooseKernel->addItem("CROSS");
    chooseKernel->addItem("ELLIPSE");
    connect(chooseKernel, &QComboBox::currentTextChanged, this, [this, chooseKernel]() {
        this->inputKernel = chooseKernel->currentIndex();
        updateImageDisplay();
    });

    this->options->layout()->addWidget(chooseKernel);


    Slider *sliderDilatationInput = new Slider("Dilatation Size ", Qt::Vertical, 1, 50, this->inputSize);
    connect(sliderDilatationInput->getSlider(), &QSlider::valueChanged, this, [this, sliderDilatationInput](int val) {
        this->inputSize = val;
        sliderDilatationInput->setCurrentValue(this->inputSize);
        updateImageDisplay();
    });
    this->options->layout()->addWidget(sliderDilatationInput);
}


Mat Dilatation::applyManipulation() {
    
    Size dilatationSize = Size(this->inputSize,this->inputSize);
    Mat imageDestination;
    Mat dilatationKernel = getStructuringElement(this->inputKernel, dilatationSize);
    dilate(this->imageSavedInMemory,imageDestination, dilatationKernel);
    
    return imageDestination;

};