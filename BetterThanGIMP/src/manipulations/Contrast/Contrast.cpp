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
    this->percentChange = 1;

    int RANGE = 200;
    Slider *sliderContrast = new Slider("Contrast level", Qt::Vertical, -RANGE, RANGE, this->percentChange, -1);
    connect(sliderContrast->getSlider(), &QSlider::valueChanged, this, [this, sliderContrast, RANGE](int val) {
        double value = val;
        if (val > 0) {
            value = 1 + value / 100;
        } else if (val < 0) {
            value = (RANGE + value) / RANGE;
        } else {
            value = 1;
        }
        this->percentChange = value;
        sliderContrast->setCurrentValue(this->percentChange);
        updateImageDisplay();
    });
    this->options->layout()->addWidget(sliderContrast);

}

Mat Contrast::applyManipulation() {
    Mat new_image;
    this->imageSavedInMemory.convertTo(new_image, -1, this->percentChange);
    return new_image;
};