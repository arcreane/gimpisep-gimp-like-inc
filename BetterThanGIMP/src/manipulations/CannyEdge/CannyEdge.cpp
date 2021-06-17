//
// Created by Hugues Baratgin on 12/06/2021.
//

#include <opencv2/opencv.hpp>
#include <QHBoxLayout>

#include "CannyEdge.h"
#include "../../component/Slider/Slider.h"

using namespace cv;

CannyEdge::CannyEdge(Workspace &w) : Manipulation(w) {
    this->name = "Canny edge";
    this->options->setLayout(new QVBoxLayout());

    //We initialize our parameters
    this->threshold1 = 0;
    this->threshold2 = 0;
    this->kernelSize = 0;

    QWidget *thresholdSliders = new QWidget();
    thresholdSliders->setLayout(new QHBoxLayout());

    Slider *sliderThreshold1 = new Slider("Threshold 1", Qt::Vertical, 0, 1000, this->threshold1);
    connect(sliderThreshold1->getSlider(), &QSlider::valueChanged, this, [this, sliderThreshold1](int val) {
        this->threshold1 = val;
        sliderThreshold1->setCurrentValue(this->threshold1);
        updateImageDisplay();
    });
    thresholdSliders->layout()->addWidget(sliderThreshold1);

    Slider *sliderThreshold2 = new Slider("Threshold 2", Qt::Vertical, 0, 1000, this->threshold2);
    connect(sliderThreshold2->getSlider(), &QSlider::valueChanged, this, [this, sliderThreshold2](int val) {
        this->threshold2 = val;
        sliderThreshold2->setCurrentValue(this->threshold2);
        updateImageDisplay();
    });
    thresholdSliders->layout()->addWidget(sliderThreshold2);

    this->options->layout()->addWidget(thresholdSliders);

    Slider *sliderKernelSize = new Slider("Blur Kernel Size", Qt::Horizontal, -1, 10, this->kernelSize, -1);
    connect(sliderKernelSize->getSlider(), &QSlider::valueChanged, this, [this, sliderKernelSize](int val) {
        val = val < 0 ? 0 : val * 2 + 1;
        this->kernelSize = val;
        sliderKernelSize->setCurrentValue(this->kernelSize);
        updateImageDisplay();
    });
    this->options->layout()->addWidget(sliderKernelSize);
}

Mat CannyEdge::applyManipulation() {
    Mat result, blur;
    if (kernelSize > 0) {
        GaussianBlur(this->imageSavedInMemory, blur, Size(this->kernelSize, this->kernelSize), 0);
    } else {
        blur = this->imageSavedInMemory;
    }
    Canny(blur, result, this->threshold1, this->threshold2);
    return result;
};