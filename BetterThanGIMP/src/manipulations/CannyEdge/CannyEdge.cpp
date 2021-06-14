//
// Created by Hugues Baratgin on 12/06/2021.
//

#include <opencv2/opencv.hpp>
#include <QSlider>
#include <QGridLayout>
#include <QPushButton>
#include "CannyEdge.h"

using namespace cv;

CannyEdge::CannyEdge(Workspace &w) : Manipulation(w) {
    this->name = "Canny edge";
    this->options->setLayout(new QHBoxLayout());

    this->threshold1 = 0;
    this->threshold2 = 0;
    this->kernelSize = 1;

    QSlider *sliderThreshold1 = new QSlider(Qt::Vertical, this->options);
    QObject::connect(sliderThreshold1, &QSlider::valueChanged, this, [this](int val) {
        this->threshold1 = val;
        updateImageDisplay();
    });
    sliderThreshold1->setRange(0, 1000);
    this->options->layout()->addWidget(sliderThreshold1);

    QSlider *sliderThreshold2 = new QSlider(Qt::Vertical, this->options);
    QObject::connect(sliderThreshold2, &QSlider::valueChanged, this, [this](int val) {
        this->threshold2 = val;
        updateImageDisplay();
    });
    sliderThreshold1->setRange(0, 1000);
    this->options->layout()->addWidget(sliderThreshold2);

    QSlider *sliderKernelSize = new QSlider(Qt::Vertical, this->options);
    QObject::connect(sliderKernelSize, &QSlider::valueChanged, this, [this](int val) {
        val = val * 2 + 1;
        this->kernelSize = val;
        updateImageDisplay();
    });
    sliderKernelSize->setRange(0, 10);
    this->options->layout()->addWidget(sliderKernelSize);


    this->options->setStyleSheet("QWidget{background-color: green;}");
}

Mat CannyEdge::cannyEdge(Mat &image, int threshold1, int threshold2, int kernelSize) {
    Mat result, grey, blur;
    cvtColor(image, grey, COLOR_BGR2GRAY);
    GaussianBlur(grey, blur, Size(kernelSize, kernelSize), 0);
    Canny(blur, result, threshold1, threshold2);
    return result;
}

Mat CannyEdge::applyManipulation() {
    return cannyEdge(this->currentImage, this->threshold1, this->threshold2, this->kernelSize);
};