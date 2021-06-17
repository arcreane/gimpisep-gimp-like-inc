//
// Created by louis on 17/06/2021.
//

#include "Resizing.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <QSlider>
#include <QHBoxLayout>
#include "../../component/Slider/Slider.h"
using namespace cv;
using namespace std;

Resizing::Resizing(Workspace &w) : Manipulation(w) {
    this->name = "Resizing";
    this->options->setLayout(new QHBoxLayout());

    //We initialize our parameters
    this->scaleX = 0;
    this->scaleY = 0;
    this->factor = false;

    QCheckBox *useFactor = new QCheckBox("Use factor");
    connect(useFactor, &QCheckBox::stateChanged, this, [this](bool val) {
        this->factor = val;
        update();
    });
    this->options->layout()->addWidget(useFactor);
}

Mat Resizing::resizing(Mat &image, double scaleX, double scaleY, bool option) {
    Mat output;
    double input_height = image.size().height;
    double input_width = image.size().width;
    if (!option) {
        /* Resize down*/
        if (input_height * input_width < scaleX * scaleY) {
            resize(image, output, Size(scaleX, scaleY), INTER_AREA);
        }
            /* Resize up*/
        else if (input_height * input_width > scaleX * scaleY) {
            resize(image, output, Size(scaleX, scaleY), INTER_CUBIC);
        }
            /* Same size*/
        else {
            resize(image, output, Size(scaleX, scaleY), INTER_LINEAR);
        }
    }
    else {
        /* Rescale down*/
        if (scaleX< 1) {
            resize(image, output, Size(0, 0), scaleX, scaleY, INTER_AREA);
        }
            /* Rescale up*/
        else if (scaleX > 1) {
            resize(image, output, Size(0, 0), scaleX, scaleY, INTER_CUBIC);
        }
            /* Same size*/
        else {
            resize(image, output, Size(0, 0), scaleX, scaleY, INTER_LINEAR);
        }
    }

    return output;
}

Mat Resizing::applyManipulation() {
    return resizing(this->imageSavedInMemory, this->scaleX, this->scaleY,this->factor);
};
void update(){
    if(this->factor){
        QLineEdit *inputFactor = new QLineEdit();
        connect(inputFactor, &QLineEdit::textChanged, this, [this, inputFactor](QString val) {
            bool isOk;
            double temp;
            temp = val.toDouble(&isOk,10);
            if (isOk){
                if (0<temp && temp<=10){
                    this->scaleX = temp;
                    this->scaleY = temp;
                    inputFactor->setCurrentValue(this->scaleX);
                    updateImageDisplay();
                }
            }
        });
        this->options->layout()->addWidget(inputFactor);
    }
    else{
        QLineEdit *inputScaleX = new QLineEdit();
        connect(inputScaleX, &QLineEdit::textChanged, this, [this, inputScaleX](QString val) {
            bool isOk;
            int temp;
            temp = val.toInt(&isOk,10);
            if (isOk){
                this->scaleX = temp;
                inputScaleX->setCurrentValue(this->scaleX);
                updateImageDisplay();
            }
        });
        QLineEdit *inputScaleY = new QLineEdit();
        connect(inputScaleY, &QLineEdit::textChanged, this, [this, inputScaleY](QString val) {
            bool isOk;
            int temp;
            temp = val.toInt(&isOk,10);
            if (isOk){
                this->scaleY = temp;
                inputScaleY->setCurrentValue(this->scaleY);
                updateImageDisplay();
            }
        });
        this->options->layout()->addWidget(inputScaleX);
        this->options->layout()->addWidget(inputScaleY);
    }
}
