//
// Created by yakiimo on 5/10/21.
//

#include <QSlider>
#include <iostream>
#include <QLayoutItem>
#include <QLabel>
#include "OptionsMenu.h"

OptionsMenu::OptionsMenu() {
    layout = new QVBoxLayout(this);
    this->currentOptions = new QWidget();

    this->title = new QLabel("There is no manipulation for the moment...");
    this->title->setAlignment(Qt::AlignCenter);

    this->layout->addWidget(this->title);
    this->layout->addWidget(currentOptions);
    this->layout->addStretch();

    this->setStyleSheet("QWidget{background-color: orange;}");
}

void OptionsMenu::setOptions(QWidget *options, QString manipulationName) {
    this->title->setText("Options for the manipulation " + manipulationName);
    removeOptions();
    this->currentOptions = options;
    this->layout->addWidget(currentOptions);
}

void OptionsMenu::removeOptions(){
    this->layout->removeWidget(currentOptions);
    delete this->currentOptions;
}