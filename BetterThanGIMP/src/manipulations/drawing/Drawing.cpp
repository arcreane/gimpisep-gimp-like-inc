//
// Created by Hugues Baratgin on 17/06/2021.
//

#include <QVBoxLayout>

#include "Drawing.h"
#include "../../component/Slider/Slider.h"

Drawing::Drawing(Workspace &w) : Manipulation(w) {
    this->options->setLayout(new QVBoxLayout);

    connect(&this->workspace, &Workspace::mousePressed, this, [this](Point) {
        this->imageModified.copyTo(this->imageBeforeNextDrawing);
    });

    connect(&this->workspace, &Workspace::mouseMoved, this, [this](Point coordinates) {
        this->mouseCoordinates = coordinates;
        this->updateImageDisplay();
    });

    connect(&this->workspace, &Workspace::mouseReleased, this, [this]() {
        this->imageBeforeNextDrawing = applyManipulation();
    });

    this->brushSize = 10;
    this->blue = 0;
    this->green = 0;
    this->red = 0;


    Slider *brushSizeSlider = new Slider("Brush size", Qt::Horizontal, 5, 100, this->brushSize);
    connect(brushSizeSlider->getSlider(), &QSlider::valueChanged, this, [this, brushSizeSlider](int val) {
        this->brushSize = val;
        brushSizeSlider->setCurrentValue(this->brushSize);
    });

    QWidget *colorSelection = new QWidget();
    colorSelection->setLayout(new QHBoxLayout());

    Slider *blueSlider = new Slider("Blue", Qt::Vertical, 0, 255, 0);
    connect(blueSlider->getSlider(), &QSlider::valueChanged, this, [this, blueSlider](int val) {
        this->blue = val;
        blueSlider->setCurrentValue(this->blue);
    });
    colorSelection->layout()->addWidget(blueSlider);

    Slider *greenSlider = new Slider("Green", Qt::Vertical, 0, 255, 0);
    connect(greenSlider->getSlider(), &QSlider::valueChanged, this, [this, greenSlider](int val) {
        this->green = val;
        greenSlider->setCurrentValue(this->green);
    });
    colorSelection->layout()->addWidget(greenSlider);

    Slider *redSlider = new Slider("Red", Qt::Vertical, 0, 255, 0);
    connect(redSlider->getSlider(), &QSlider::valueChanged, this, [this, redSlider](int val) {
        this->red = val;
        redSlider->setCurrentValue(this->red);
    });
    colorSelection->layout()->addWidget(redSlider);

    this->options->layout()->addWidget(brushSizeSlider);
    this->options->layout()->addWidget(colorSelection);
}