//
// Created by Remi Genin on 17/06/2021.
//


#include <opencv2/opencv.hpp>
#include <QHBoxLayout>

#include "Brightness.h"
#include "../../component/Slider/Slider.h"

using namespace cv;

Brightness::Brightness(Workspace &w) : Manipulation(w) {
    this->name = "Brightness";
    this->options->setLayout(new QHBoxLayout());

    //We initialize our parameters
    this->percentChange = 0;


    Slider *sliderBrightness = new Slider("Brightness level", Qt::Vertical, -100, 100, this->percentChange);
    connect(sliderBrightness->getSlider(), &QSlider::valueChanged, this, [this, sliderBrightness](int val) {
        this->percentChange = val;
        sliderBrightness->setCurrentValue(this->percentChange);
        updateImageDisplay();
    });
    this->options->layout()->addWidget(sliderBrightness);

}

Mat Brightness::applyManipulation() {
    // On convertit le pourcentage en valeur scalaire (255 blanc et -255 noir)
    double percentChange = (this->percentChange / 100) * 255;
    Mat new_image;
    this->imageSavedInMemory.copyTo(new_image);
    new_image += Scalar(percentChange, percentChange, percentChange);
    return new_image;
};
