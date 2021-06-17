//
// Created by yakiimo on 6/17/21.
//

#include <opencv2/opencv.hpp>
#include <QHBoxLayout>
#include <QComboBox>

#include "Erosion.h"
#include "../../component/Slider/Slider.h"

using namespace cv;

Erosion::Erosion(Workspace &w) : Manipulation(w) {
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

Mat Erosion::applyManipulation() {
    Mat imageDestination;
    Size erosionSize = Size(this->inputSize, this->inputSize);
    Mat erosionKernel = getStructuringElement(this->inputKernel, erosionSize);
    erode(this->imageSavedInMemory, imageDestination, erosionKernel);

    return imageDestination;
};