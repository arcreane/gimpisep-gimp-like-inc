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
    this->blurKernelSize = 0;
    this->sobelKernelSize = 3;

    QWidget *thresholdSliders = new QWidget();
    thresholdSliders->setLayout(new QHBoxLayout());

    Slider *sliderThreshold1 = new Slider("Threshold 1", Qt::Vertical, 0, 500, this->threshold1);
    connect(sliderThreshold1->getSlider(), &QSlider::valueChanged, this, [this, sliderThreshold1](int val) {
        this->threshold1 = val;
        sliderThreshold1->setCurrentValue(this->threshold1);
        updateImageDisplay();
    });
    thresholdSliders->layout()->addWidget(sliderThreshold1);

    Slider *sliderThreshold2 = new Slider("Threshold 2", Qt::Vertical, 0, 500, this->threshold2);
    connect(sliderThreshold2->getSlider(), &QSlider::valueChanged, this, [this, sliderThreshold2](int val) {
        this->threshold2 = val;
        sliderThreshold2->setCurrentValue(this->threshold2);
        updateImageDisplay();
    });
    thresholdSliders->layout()->addWidget(sliderThreshold2);

    this->options->layout()->addWidget(thresholdSliders);

    Slider *sliderBlurKernelSize = new Slider("Blur Kernel Size", Qt::Horizontal, -1, 10, this->blurKernelSize, -1);
    connect(sliderBlurKernelSize->getSlider(), &QSlider::valueChanged, this, [this, sliderBlurKernelSize](int val) {
        val = val < 0 ? 0 : val * 2 + 1;
        this->blurKernelSize = val;
        sliderBlurKernelSize->setCurrentValue(this->blurKernelSize);
        updateImageDisplay();
    });
    this->options->layout()->addWidget(sliderBlurKernelSize);

    Slider *sliderSobelKernelSize = new Slider("Sobel Kernel Size", Qt::Horizontal, 1, 3, 3, -2);
    connect(sliderSobelKernelSize->getSlider(), &QSlider::valueChanged, this, [this, sliderSobelKernelSize](int val) {
        val = val * 2 + 1;
        this->sobelKernelSize = val;
        sliderSobelKernelSize->setCurrentValue(this->sobelKernelSize);
        updateImageDisplay();
    });
    this->options->layout()->addWidget(sliderSobelKernelSize);
}

Mat CannyEdge::applyManipulation() {
    Mat result, blur;
    if (blurKernelSize > 0) {
        GaussianBlur(this->imageSavedInMemory, blur, Size(this->blurKernelSize, this->blurKernelSize), 0);
    } else {
        blur = this->imageSavedInMemory;
    }
    Canny(blur, result, this->threshold1, this->threshold2, this->sobelKernelSize);
    return result;
};