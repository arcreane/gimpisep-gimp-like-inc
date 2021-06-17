//
// Created by Hugues Baratgin on 12/06/2021.
//

#include <opencv2/opencv.hpp>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include "Monochrome.h"

using namespace cv;

Monochrome::Monochrome(Workspace &w) : Manipulation(w)
{
    this->name = "Monochrome";
    this->options->setLayout(new QVBoxLayout());

    QPushButton *convertToGrey = new QPushButton(tr("Grey"));
    connect(convertToGrey, &QPushButton::released, this, [this]()
            {
                this->transform = COLOR_BGR2GRAY;
                updateImageDisplay();
            });
    this->options->layout()->addWidget(convertToGrey);

    QPushButton *switchBlueAndRed = new QPushButton(tr("Switch blue and red"));
    connect(switchBlueAndRed, &QPushButton::pressed, this, [this]()
            {
                this->transform = COLOR_BGR2RGB;
                updateImageDisplay();
            });
    this->options->layout()->addWidget(switchBlueAndRed);
}

Mat Monochrome::applyManipulation()
{
    if (this->imageSavedInMemory.channels() < 3 && this->transform == COLOR_BGR2GRAY)
    {
        return this->imageSavedInMemory;
    }

    Mat result;
    cvtColor(this->imageSavedInMemory, result, this->transform);
    return result;
}
