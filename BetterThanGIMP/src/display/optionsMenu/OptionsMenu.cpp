//
// Created by yakiimo on 5/10/21.
//

#include <QSlider>
#include <iostream>
#include <QLayoutItem>
#include <QLabel>
#include "OptionsMenu.h"

OptionsMenu::OptionsMenu() {
    layout = new QGridLayout(this);
    this->currentOptions = new QWidget();
    this->setStyleSheet("QWidget{background-color: orange;}");
    this->layout->addWidget(new QLabel("Some useful options:"));
    this->layout->addWidget(currentOptions);
}

void OptionsMenu::setOptions(QWidget *options) {
    this->layout->removeWidget(currentOptions);
    delete this->currentOptions;
    this->currentOptions = options;
    this->layout->addWidget(currentOptions);
}