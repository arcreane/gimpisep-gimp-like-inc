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

void Manipulation::onResize(){}

void Manipulation::updateImageDisplay() {
    this->imageModified = applyManipulation();
    this->updateImageDisplayOnWorkspace();
}

void Manipulation::updateImageDisplayOnWorkspace() {
    this->workspace.updateImageDisplay(this->imageModified);
}

Mat Manipulation::getImageModified() {
    return this->imageModified;
}

void Manipulation::setImageSavedInMemory(Mat currentImage) {
    this->imageSavedInMemory = currentImage;
    currentImage.copyTo(this->imageModified);
}

