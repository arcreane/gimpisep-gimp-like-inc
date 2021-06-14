//
// Created by Hugues Baratgin on 12/06/2021.
//

#include <QHBoxLayout>
#include "Manipulation.h"

Manipulation::Manipulation(Workspace &w) : workspace(w) {
    this->options = new QWidget();
}

QWidget *Manipulation::getOptions() {
    return this->options;
}

std::string Manipulation::getName() {
    return this->name;
}

Mat Manipulation::applyManipulation() {
    std::cout << "Default applyManipulation, must be override" << std::endl;
    exit(-1);
}

void Manipulation::updateImageDisplay() {
    this->workspace.updateImageDisplay(applyManipulation());
}

void Manipulation::setCurrentImage(Mat currentImage) {
    this->currentImage = currentImage;
}