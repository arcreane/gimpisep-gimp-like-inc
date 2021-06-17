//
// Created by Louis Felli on 17/06/2021.
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>

#include "Resizing.h"
#include "../../component/Slider/Slider.h"
#include "../../component/Input/Input.h"

using namespace cv;
using namespace std;

Resizing::Resizing(Workspace &w) : Manipulation(w) {
    this->name = "Resizing";
    this->options->setLayout(new QVBoxLayout());
    this->parametersToDisplay = new QWidget();

    //We initialize our parameters
    this->scaleX = 0;
    this->scaleY = 0;
    this->factor = false;

    QCheckBox *useFactor = new QCheckBox("Use factor");
    connect(useFactor, &QCheckBox::stateChanged, this, [this](bool val) {
        this->factor = val;
        updateParametersToDisplay();
    });
    this->options->layout()->addWidget(useFactor);
    this->options->layout()->setAlignment(useFactor, Qt::AlignHCenter);

    updateParametersToDisplay();
}

Mat Resizing::applyManipulation() {
    Mat output;
    double input_height = this->imageSavedInMemory.size().height;
    double input_width = this->imageSavedInMemory.size().width;
    if (!this->factor) {
        /* Resize down*/
        if (input_height * input_width < this->scaleX * this->scaleY) {
            cv::resize(this->imageSavedInMemory, output, Size(this->scaleX, this->scaleY), INTER_AREA);
        }
            /* Resize up*/
        else if (input_height * input_width > this->scaleX * this->scaleY) {
            cv::resize(this->imageSavedInMemory, output, Size(this->scaleX, this->scaleY), INTER_CUBIC);
        }
            /* Same size*/
        else {
            cv::resize(this->imageSavedInMemory, output, Size(this->scaleX, this->scaleY), INTER_LINEAR);
        }
    } else {
        /* Rescale down*/
        if (this->scaleX < 1) {
            cv::resize(this->imageSavedInMemory, output, Size(0, 0), this->scaleX, this->scaleY, INTER_AREA);
        }
            /* Rescale up*/
        else if (this->scaleX > 1) {
            cv::resize(this->imageSavedInMemory, output, Size(0, 0), this->scaleX, this->scaleY, INTER_CUBIC);
        }
            /* Same size*/
        else {
            cv::resize(this->imageSavedInMemory, output, Size(0, 0), this->scaleX, this->scaleY, INTER_LINEAR);
        }
    }

    return output;
}

void Resizing::updateParametersToDisplay() {
    delete this->parametersToDisplay;
    this->scaleX = 0;
    this->scaleY = 0;
    this->parametersToDisplay = new QWidget();
    this->parametersToDisplay->setLayout(new QVBoxLayout());

    if (this->factor) {
        Input *inputFactor = new Input("Factor");
        connect(inputFactor->getInput(), &QLineEdit::textChanged, this, [this](QString val) {
            bool isOk;
            double temp = val.toDouble(&isOk);
            if (isOk) {
                if (temp > 0.001 && temp <= 10) {
                    this->scaleX = temp;
                    this->scaleY = temp;
                    updateImageDisplay();
                }
            }
        });
        this->parametersToDisplay->layout()->addWidget(inputFactor);
    } else {

        Input *inputScaleX = new Input("Height");
        connect(inputScaleX->getInput(), &QLineEdit::textChanged, this, [this](QString val) {
            bool isOk;
            int temp = val.toInt(&isOk, 10);
            if (isOk) {
                this->scaleX = temp;
            }
        });
        this->parametersToDisplay->layout()->addWidget(inputScaleX);

        Input *inputScaleY = new Input("Width");
        connect(inputScaleY->getInput(), &QLineEdit::textChanged, this, [this](QString val) {
            bool isOk;
            int temp = val.toInt(&isOk, 10);
            if (isOk) {
                this->scaleY = temp;
            }
        });
        this->parametersToDisplay->layout()->addWidget(inputScaleY);

        QPushButton *resizeImage = new QPushButton("Resize");
        connect(resizeImage, &QPushButton::pressed, this, [this]() {
            if (this->scaleX > 0 && this->scaleY > 0) {
                updateImageDisplay();
            }
        });
        this->parametersToDisplay->layout()->addWidget(resizeImage);
    }
    this->options->layout()->addWidget(this->parametersToDisplay);
}

