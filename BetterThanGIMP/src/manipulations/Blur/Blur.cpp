//
// Created by yakiimo on 6/17/21.
//

#include "Blur.h"
#include <QSlider>
#include <QHBoxLayout>
#include "../../component/Slider/Slider.h"
#include <opencv2/opencv.hpp>

using namespace cv;

Blur::Blur(Workspace &w) : Manipulation(w){
    this->name = "Gaussian Blur";
    this->options->setLayout(new QHBoxLayout());
    this->blurKernelSize = 0;

    Slider *sliderBlurKernelSize = new Slider("Blur Kernel Size", Qt::Vertical, 0, 20, this->blurKernelSize);
    connect(sliderBlurKernelSize->getSlider(), &QSlider::valueChanged, this, [this, sliderBlurKernelSize](int val) {
        val = val < 0 ? 0 : val * 2 + 1;
        this->blurKernelSize = val;
        sliderBlurKernelSize->setCurrentValue(this->blurKernelSize);
        updateImageDisplay();
    });
    this->options->layout()->addWidget(sliderBlurKernelSize);


    this->options->setStyleSheet("QWidget{background-color: green;}");
}

Mat Blur::blur(Mat &image, int kernelSize) {
    Mat result;
    cv::GaussianBlur(image, result, Size(kernelSize,kernelSize), 0, BORDER_DEFAULT);
    return result;
}

Mat Blur::applyManipulation() {
    return blur(this->imageSavedInMemory, this->blurKernelSize);
};
