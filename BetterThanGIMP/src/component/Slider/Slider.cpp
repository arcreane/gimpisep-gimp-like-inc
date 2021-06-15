//
// Created by Hugues Baratgin on 15/06/2021.
//

#include <QVBoxLayout>
#include <QLabel>
#include "Slider.h"

Slider::Slider(QString name, int min, int max, int defaultValue, int defaultOffset) {
    this->slider = new QSlider(Qt::Vertical);
    this->slider->setRange(min, max);
    this->slider->setValue(defaultValue + defaultOffset);

    this->currentValue = new QLabel("Value: " + QString::number(defaultValue));

    this->setLayout(new QVBoxLayout());

    this->layout()->addWidget(new QLabel(name));
    this->layout()->addWidget(this->slider);
    this->layout()->addWidget(this->currentValue);

    this->layout()->setAlignment(Qt::AlignHCenter);
}

QSlider *Slider::getSlider() {
    return this->slider;
}

void Slider::setCurrentValue(int newValue) {
    this->currentValue->setText("Value: " + QString::number(newValue));
}