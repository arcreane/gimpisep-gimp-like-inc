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
    this->title->setMaximumHeight(20);


    this->layout->addWidget(this->title);
    this->layout->addWidget(currentOptions);

    this->setStyleSheet("QWidget{background-color: orange;}");
}

void OptionsMenu::setOptions(QWidget *options, QString manipulationName) {
    delete this->currentOptions;
    this->title->setText("Options for the manipulation " + manipulationName);
    this->currentOptions = options;
    this->layout->addWidget(currentOptions);
}

void OptionsMenu::removeOptions() {
    this->title->setText("There is no manipulation for the moment...");
    delete this->currentOptions;
    this->currentOptions = nullptr;
}

