#include "Brightness.h"

#include <opencv2/opencv.hpp>
#include <QSlider>
#include <QHBoxLayout>
#include "CannyEdge.h"
#include "../../component/Slider/Slider.h"

using namespace cv;

Brightness::Brightness(Workspace &w) : Manipulation(w) {
    this->name = "Brightness";
    this->options->setLayout(new QHBoxLayout());

    //We initialize our parameters
    this->percentChange = 0;


    Slider *sliderBrightness = new Slider("Brightness level", Qt::Vertical, 0, 1000, this->percentChange);
    connect(sliderBrightness->getSlider(), &QSlider::valueChanged, this, [this, sliderBrightness](int val) {
        this->percentChange = val;
        sliderBrightness->setCurrentValue(this->percentChange);
        updateImageDisplay();
    });
    this->options->layout()->addWidget(sliderBrightness);

}

Mat Brightness::brightness(Mat &image, int percentChange) {
    percentChange = (percentChange/100)*260; // On converti le pourcentage en valeur scalaire (260 blanc et -260 noir)
    Mat new_image;
    new_image = image + Scalar(percentChange,percentChange,percentChange);
    return new_image;
}

Mat Brightness::applyManipulation() {
    return Brightness(this->imageSavedInMemory, this->percentChange);

};