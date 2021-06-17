//
// Created by yakiimo on 6/17/21.
//

#include <opencv2/opencv.hpp>
#include <QHBoxLayout>

#include "Blur.h"
#include "../../component/Slider/Slider.h"

using namespace cv;

Blur::Blur(Workspace &w) : Manipulation(w) {
    this->name = "Gaussian Blur";
    this->options->setLayout(new QHBoxLayout());

    this->blurKernelSize = 0;

    Slider *sliderBlurKernelSize = new Slider("Blur Kernel Size", Qt::Vertical, -1, 20, this->blurKernelSize, -1);
    connect(sliderBlurKernelSize->getSlider(), &QSlider::valueChanged, this, [this, sliderBlurKernelSize](int val) {
        val = val < 0 ? 0 : val * 2 + 1;
        this->blurKernelSize = val;
        sliderBlurKernelSize->setCurrentValue(this->blurKernelSize);
        updateImageDisplay();
    });
    this->options->layout()->addWidget(sliderBlurKernelSize);
}

Mat Blur::applyManipulation() {
    if (this->blurKernelSize > 0) {
        Mat result;
        GaussianBlur(this->imageSavedInMemory, result, Size(this->blurKernelSize, this->blurKernelSize), 0,
                     BORDER_DEFAULT);
        return result;
    }
    return this->imageSavedInMemory;
};
