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

Monochrome::Monochrome(Workspace &w) : Manipulation(w) {
    this->name = "Monochrome";
    this->options->setLayout(new QVBoxLayout());

    QPushButton *convertToGrey = new QPushButton(tr("Grey"));
    connect(convertToGrey, &QPushButton::pressed, this, [this]() {
        this->transform = COLOR_BGR2GRAY;
        if (this->currentImage.channels() < 3) {
            std::cout << "Error loading image" << std::endl;
            QMessageBox error;
            error.setText("Can't perform requested manipulation on the current image!");
            error.exec();
        } else {
            updateImageDisplay();
        }

    });
//    convertToGrey->setEnabled(this->currentImage.channels() == 3);
    this->options->layout()->addWidget(convertToGrey);

    QPushButton *switchBlueAndRed = new QPushButton(tr("Switch blue and red"));
    connect(switchBlueAndRed, &QPushButton::pressed, this, [this]() {
        this->transform = COLOR_BGR2RGB;
        updateImageDisplay();
    });
    this->options->layout()->addWidget(switchBlueAndRed);

    //TEMP
    this->options->setStyleSheet("QWidget{background-color: green;}");

}


Mat Monochrome::applyManipulation() {
    Mat result;
    std::cout << this->currentImage.channels() << std::endl;
    cvtColor(this->currentImage, result, this->transform);
    return result;
}
