//
// Created by Hugues Baratgin on 16/06/2021.
//


#include <opencv2/opencv.hpp>
#include <QHBoxLayout>
#include "Brush.h"
#include "../../component/Slider/Slider.h"

using namespace cv;

Brush::Brush(Workspace &w) : Manipulation(w) {
    this->name = "Brush";
    this->options->setLayout(new QVBoxLayout);

    this->brushSize = 10;
    this->blue = 0;
    this->green = 0;
    this->red = 0;

    connect(&this->workspace, &Workspace::mouseMoved, this, [this](Point coordinates) {
        this->coordinates = coordinates;
        this->updateImageDisplay();
    });

    QSlider *brushSizeSlider = new QSlider(Qt::Horizontal);
    brushSizeSlider->setRange(5, 100);
    brushSizeSlider->setValue(this->brushSize);
    connect(brushSizeSlider, &QSlider::valueChanged, this, [this](int val) {
        this->brushSize = val;
    });

    QWidget *colorSelection = new QWidget();
    colorSelection->setLayout(new QHBoxLayout());

    Slider *blueSlider = new Slider("Blue", 0, 255, 0);
    connect(blueSlider->getSlider(), &QSlider::valueChanged, this, [this, blueSlider](int val) {
        this->blue = val;
        blueSlider->setCurrentValue(this->blue);
    });
    colorSelection->layout()->addWidget(blueSlider);

    Slider *greenSlider = new Slider("Green", 0, 255, 0);
    connect(greenSlider->getSlider(), &QSlider::valueChanged, this, [this, greenSlider](int val) {
        this->green = val;
        greenSlider->setCurrentValue(this->green);
    });
    colorSelection->layout()->addWidget(greenSlider);

    Slider *redSlider = new Slider("Red", 0, 255, 0);
    connect(redSlider->getSlider(), &QSlider::valueChanged, this, [this, redSlider](int val) {
        this->red = val;
        redSlider->setCurrentValue(this->red);
    });
    colorSelection->layout()->addWidget(redSlider);


    this->options->layout()->addWidget(new QLabel("Brush size:"));
    this->options->layout()->addWidget(brushSizeSlider);
    this->options->layout()->addWidget(colorSelection);
}

Mat Brush::draw(Mat &image, Point coord, int size, Scalar color) {
    Mat result;
    image.copyTo(result);
    circle(result, coord, size, color, FILLED);
    return result;
}

Mat Brush::applyManipulation() {
    return draw(this->imageModified, this->coordinates, this->brushSize,
                Scalar(this->blue, this->green, this->red));
};
