//
// Created by yakiimo on 6/17/21.
//


#include <opencv2/opencv.hpp>
#include <QHBoxLayout>

#include "Contrast.h"
#include "../../component/Slider/Slider.h"

using namespace cv;

Contrast::Contrast(Workspace &w) : Manipulation(w) {
    this->name = "Contrast";
    this->options->setLayout(new QHBoxLayout());

    //We initialize our parameters
    this->percentChange = 0;


    Slider *sliderContrast = new Slider("Contrast level", Qt::Vertical, 0, 1000, this->percentChange);
    connect(sliderContrast->getSlider(), &QSlider::valueChanged, this, [this, sliderContrast](int val) {
        this->percentChange = val;
        sliderContrast->setCurrentValue(this->percentChange);
        updateImageDisplay();
    });
    this->options->layout()->addWidget(sliderContrast);

}

Mat Contrast::applyManipulation() {
    double percentChange = (this->percentChange / 100);
    Mat new_image;
    this->imageSavedInMemory.convertTo(new_image, -1, percentChange);
    return new_image;
};